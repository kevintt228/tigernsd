/*
 * query.c -- nsd(8) the resolver.
 *
 * Copyright (c) 2001-2006, NLnet Labs. All rights reserved.
 *
 * See LICENSE for the license.
 *
 */

#include "config.h"

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <assert.h>
#include <ctype.h>
#include <errno.h>
#include <limits.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <netdb.h>

#include "answer.h"
#include "axfr.h"
#include "dns.h"
#include "dname.h"
#include "nsd.h"
#include "namedb.h"
#include "query.h"
#include "util.h"
#include "options.h"
#include "nsec3.h"
#include "tsig.h"

/* [Bug #253] Adding unnecessary NS RRset may lead to undesired truncation.
 * This function determines if the final response packet needs the NS RRset
 * included. Currently, it will only return negative if QTYPE == DNSKEY|DS.
 * This way, resolvers won't fallback to TCP unnecessarily when priming
 * trust anchors.
 */
static int answer_needs_ns(struct query  *query);

static int add_rrset(struct query  *query,
		     answer_type    *answer,
		     rr_section_type section,
		     domain_type    *owner,
		     rrset_type     *rrset);

static void answer_authoritative(struct nsd	  *nsd,
				 struct query     *q,
				 answer_type      *answer,
				 size_t            domain_number,
				 int               exact,
				 domain_type      *closest_match,
				 domain_type      *closest_encloser,
				 const dname_type *qname);

static void answer_lookup_zone(struct nsd *nsd, struct query *q,
			       answer_type *answer, size_t domain_number,
			       int exact, domain_type *closest_match,
			       domain_type *closest_encloser,
			       const dname_type *qname);

void
query_put_dname_offset(struct query *q, domain_type *domain, uint16_t offset)
{
	assert(q);
	assert(domain);
	assert(domain->number > 0);

	if (offset > MAX_COMPRESSION_OFFSET)
		return;
	if (q->compressed_dname_count >= MAX_COMPRESSED_DNAMES)
		return;

	q->compressed_dname_offsets[domain->number] = offset;
	q->compressed_dnames[q->compressed_dname_count] = domain;
	++q->compressed_dname_count;
}

void
query_clear_dname_offsets(struct query *q, size_t max_offset)
{
	while (q->compressed_dname_count > 0
	       && (q->compressed_dname_offsets[q->compressed_dnames[q->compressed_dname_count - 1]->number]
		   >= max_offset))
	{
		q->compressed_dname_offsets[q->compressed_dnames[q->compressed_dname_count - 1]->number] = 0;
		--q->compressed_dname_count;
	}
}

void
query_clear_compression_tables(struct query *q)
{
	uint16_t i;

	for (i = 0; i < q->compressed_dname_count; ++i) {
		assert(q->compressed_dnames);
		q->compressed_dname_offsets[q->compressed_dnames[i]->number] = 0;
	}
	q->compressed_dname_count = 0;
}

void
query_add_compression_domain(struct query *q, domain_type *domain, uint16_t offset)
{
	while (domain->parent) {
		DEBUG(DEBUG_NAME_COMPRESSION, 2,
		      (LOG_INFO, "query dname: %s, number: %lu, offset: %u\n",
		       domain_to_string(domain),
		       (unsigned long) domain->number,
		       offset));
		query_put_dname_offset(q, domain, offset);
		offset += label_length(dname_name(domain_dname(domain))) + 1;
		domain = domain->parent;
	}
}

/*
 * Generate an error response with the specified RCODE.
 */
query_state_type
query_error (struct query *q, nsd_rc_type rcode)
{
	if (rcode == NSD_RC_DISCARD) {
		return QUERY_DISCARDED;
	}

	buffer_clear(q->packet);

	QR_SET(q->packet);	   /* This is an answer.  */
	RCODE_SET(q->packet, (int) rcode); /* Error code.  */

	/* Truncate the question as well... */
	QDCOUNT_SET(q->packet, 0);
	ANCOUNT_SET(q->packet, 0);
	NSCOUNT_SET(q->packet, 0);
	ARCOUNT_SET(q->packet, 0);
	buffer_set_position(q->packet, QHEADERSZ);
	return QUERY_PROCESSED;
}

static query_state_type
query_formerr (struct query *query)
{
	int opcode = OPCODE(query->packet);
	FLAGS_SET(query->packet, FLAGS(query->packet) & 0x0100U);
			/* Preserve the RD flag. Clear the rest. */
	OPCODE_SET(query->packet, opcode);
	return query_error(query, NSD_RC_FORMAT);
}

static void
query_cleanup(void *data)
{
	query_type *query = (query_type *) data;
	region_destroy(query->region);
}

query_type *
query_create(region_type *region, uint16_t *compressed_dname_offsets,
	size_t compressed_dname_size)
{
	query_type *query
		= (query_type *) region_alloc_zero(region, sizeof(query_type));
	/* create region with large block size, because the initial chunk
	   saves many mallocs in the server */
	query->region = region_create_custom(xalloc, free, 16384, 16384/8, 32, 0);
	query->compressed_dname_offsets = compressed_dname_offsets;
	query->packet = buffer_create(region, QIOBUFSZ);
	region_add_cleanup(region, query_cleanup, query);
	query->compressed_dname_offsets_size = compressed_dname_size;
	tsig_create_record(&query->tsig, region);
	query->tsig_prepare_it = 1;
	query->tsig_update_it = 1;
	query->tsig_sign_it = 1;
	return query;
}

void
query_reset(query_type *q, size_t maxlen, int is_tcp)
{
	/*
	 * As long as less than 4Kb (region block size) has been used,
	 * this call to free_all is free, the block is saved for re-use,
	 * so no malloc() or free() calls are done.
	 * at present use of the region is for:
	 *   o query qname dname_type (255 max).
	 *   o wildcard expansion domain_type (7*ptr+u32+2bytes)+(5*ptr nsec3)
	 *   o wildcard expansion for additional section domain_type.
	 *   o nsec3 hashed name(s) (3 dnames for a nonexist_proof,
	 *     one proof per wildcard and for nx domain).
	 */
	region_free_all(q->region);
	q->addrlen = sizeof(q->addr);
	q->maxlen = maxlen;
	q->reserved_space = 0;
	buffer_clear(q->packet);
	edns_init_record(&q->edns);
	tsig_init_record(&q->tsig, NULL, NULL);
	q->tsig_prepare_it = 1;
	q->tsig_update_it = 1;
	q->tsig_sign_it = 1;
	q->tcp = is_tcp;
	q->qname = NULL;
	q->qtype = 0;
	q->qclass = 0;
	q->zone = NULL;
	q->opcode = 0;
	q->cname_count = 0;
	q->delegation_domain = NULL;
	q->delegation_rrset = NULL;
	q->compressed_dname_count = 0;
	q->number_temporary_domains = 0;

	q->axfr_is_done = 0;
	q->axfr_zone = NULL;
	q->axfr_current_domain = NULL;
	q->axfr_current_rrset = NULL;
	q->axfr_current_rr = 0;

#ifdef RATELIMIT
	q->wildcard_domain = NULL;
#endif
}

/* get a temporary domain number (or 0=failure) */
static domain_type*
query_get_tempdomain(struct query *q)
{
	static domain_type d[EXTRA_DOMAIN_NUMBERS];
	if(q->number_temporary_domains >= EXTRA_DOMAIN_NUMBERS)
		return 0;
	q->number_temporary_domains ++;
	memset(&d[q->number_temporary_domains-1], 0, sizeof(domain_type));
	d[q->number_temporary_domains-1].number = q->compressed_dname_offsets_size +
		q->number_temporary_domains - 1;
	return &d[q->number_temporary_domains-1];
}

static void
query_addtxt(struct query  *q,
	     const uint8_t *dname,
	     uint16_t       klass,
	     uint32_t       ttl,
	     const char    *txt)
{
	size_t txt_length = strlen(txt);
	uint8_t len = (uint8_t) txt_length;

	assert(txt_length <= UCHAR_MAX);

	/* Add the dname */
	if (dname >= buffer_begin(q->packet)
	    && dname <= buffer_current(q->packet))
	{
		buffer_write_u16(q->packet,
				 0xc000 | (dname - buffer_begin(q->packet)));
	} else {
		buffer_write(q->packet, dname + 1, *dname);
	}

	buffer_write_u16(q->packet, TYPE_TXT);
	buffer_write_u16(q->packet, klass);
	buffer_write_u32(q->packet, ttl);
	buffer_write_u16(q->packet, len + 1);
	buffer_write_u8(q->packet, len);
	buffer_write(q->packet, txt, len);
}

/*
 * Parse the question section of a query.  The normalized query name
 * is stored in QUERY->name, the class in QUERY->klass, and the type
 * in QUERY->type.
 */
static int
process_query_section(query_type *query)
{
	uint8_t qnamebuf[MAXDOMAINLEN];

	buffer_set_position(query->packet, QHEADERSZ);
	/* Lets parse the query name and convert it to lower case.  */
	if(!packet_read_query_section(query->packet, qnamebuf,
		&query->qtype, &query->qclass))
		return 0;
	query->qname = dname_make(query->region, qnamebuf, 1);
	query->opcode = OPCODE(query->packet);
	return 1;
}


/*
 * Process an optional EDNS OPT record.  Sets QUERY->EDNS to 0 if
 * there was no EDNS record, to -1 if there was an invalid or
 * unsupported EDNS record, and to 1 otherwise.  Updates QUERY->MAXLEN
 * if the EDNS record specifies a maximum supported response length.
 *
 * Return NSD_RC_FORMAT on failure, NSD_RC_OK on success.
 */
static nsd_rc_type
process_edns(nsd_type* nsd, struct query *q)
{
	if (q->edns.status == EDNS_ERROR) {
		/* The only error is VERSION not implemented */
		return NSD_RC_FORMAT;
	}

	if (q->edns.status == EDNS_OK) {
		/* Only care about UDP size larger than normal... */
		if (!q->tcp && q->edns.maxlen > UDP_MAX_MESSAGE_LEN) {
			size_t edns_size;
#if defined(INET6)
			if (q->addr.ss_family == AF_INET6) {
				edns_size = nsd->ipv6_edns_size;
			} else
#endif
			edns_size = nsd->ipv4_edns_size;

			if (q->edns.maxlen < edns_size) {
				q->maxlen = q->edns.maxlen;
			} else {
				q->maxlen = edns_size;
			}

#if defined(INET6) && !defined(IPV6_USE_MIN_MTU) && !defined(IPV6_MTU)
			/*
			 * Use IPv6 minimum MTU to avoid sending
			 * packets that are too large for some links.
			 * IPv6 will not automatically fragment in
			 * this case (unlike IPv4).
			 */
			if (q->addr.ss_family == AF_INET6
			    && q->maxlen > IPV6_MIN_MTU)
			{
				q->maxlen = IPV6_MIN_MTU;
			}
#endif
		}

		/* Strip the OPT resource record off... */
		buffer_set_position(q->packet, q->edns.position);
		buffer_set_limit(q->packet, q->edns.position);
		ARCOUNT_SET(q->packet, ARCOUNT(q->packet) - 1);
	}
	return NSD_RC_OK;
}

/*
 * Processes TSIG.
 * Sets error when tsig does not verify on the query.
 */
static nsd_rc_type
process_tsig(struct query* q)
{
	if(q->tsig.status == TSIG_ERROR)
		return NSD_RC_FORMAT;
	if(q->tsig.status == TSIG_OK) {
		if(!tsig_from_query(&q->tsig)) {
			char a[128];
			addr2str(&q->addr, a, sizeof(a));
			log_msg(LOG_ERR, "query: bad tsig (%s) for key %s from %s",
				tsig_error(q->tsig.error_code),
				dname_to_string(q->tsig.key_name, NULL), a);
			return NSD_RC_NOTAUTH;
		}
		buffer_set_limit(q->packet, q->tsig.position);
		ARCOUNT_SET(q->packet, ARCOUNT(q->packet) - 1);
		tsig_prepare(&q->tsig);
		tsig_update(&q->tsig, q->packet, buffer_limit(q->packet));
		if(!tsig_verify(&q->tsig)) {
			char a[128];
			addr2str(&q->addr, a, sizeof(a));
			log_msg(LOG_ERR, "query: bad tsig signature for key %s from %s",
				dname_to_string(q->tsig.key->name, NULL), a);
			return NSD_RC_NOTAUTH;
		}
		DEBUG(DEBUG_XFRD,1, (LOG_INFO, "query good tsig signature for %s",
			dname_to_string(q->tsig.key->name, NULL)));
	}
	return NSD_RC_OK;
}

/*
 * Check notify acl and forward to xfrd (or return an error).
 */
static query_state_type
answer_notify(struct nsd* nsd, struct query *query)
{
	int acl_num, acl_num_xfr;
	acl_options_t *why;
	nsd_rc_type rc;

	zone_options_t* zone_opt;
	DEBUG(DEBUG_XFRD,1, (LOG_INFO, "got notify %s processing acl",
		dname_to_string(query->qname, NULL)));

	zone_opt = zone_options_find(nsd->options, query->qname);
	if(!zone_opt)
		return query_error(query, NSD_RC_NXDOMAIN);

	if(!nsd->this_child) /* we are in debug mode or something */
		return query_error(query, NSD_RC_SERVFAIL);

	if(!tsig_find_rr(&query->tsig, query->packet)) {
		DEBUG(DEBUG_XFRD,2, (LOG_ERR, "bad tsig RR format"));
		return query_error(query, NSD_RC_FORMAT);
	}
	rc = process_tsig(query);
	if(rc != NSD_RC_OK)
		return query_error(query, rc);

	/* check if it passes acl */
	if((acl_num = acl_check_incoming(zone_opt->pattern->allow_notify, query,
		&why)) != -1)
	{
		sig_atomic_t mode = NSD_PASS_TO_XFRD;
		int s = nsd->this_child->parent_fd;
		uint16_t sz;
		uint32_t acl_send = htonl(acl_num);
		uint32_t acl_xfr;
		size_t pos;

		/* Find priority candidate for request XFR. -1 if no match */
		acl_num_xfr = acl_check_incoming(
			zone_opt->pattern->request_xfr, query, NULL);

		acl_xfr = htonl(acl_num_xfr);

		assert(why);
		DEBUG(DEBUG_XFRD,1, (LOG_INFO, "got notify %s passed acl %s %s",
			dname_to_string(query->qname, NULL),
			why->ip_address_spec,
			why->nokey?"NOKEY":
			(why->blocked?"BLOCKED":why->key_name)));
		sz = buffer_limit(query->packet);
		if(buffer_limit(query->packet) > MAX_PACKET_SIZE)
			return query_error(query, NSD_RC_SERVFAIL);
		/* forward to xfrd for processing
		   Note. Blocking IPC I/O, but acl is OK. */
		sz = htons(sz);
		if(!write_socket(s, &mode, sizeof(mode)) ||
			!write_socket(s, &sz, sizeof(sz)) ||
			!write_socket(s, buffer_begin(query->packet),
				buffer_limit(query->packet)) ||
			!write_socket(s, &acl_send, sizeof(acl_send)) ||
			!write_socket(s, &acl_xfr, sizeof(acl_xfr))) {
			log_msg(LOG_ERR, "error in IPC notify server2main, %s",
				strerror(errno));
			return query_error(query, NSD_RC_SERVFAIL);
		}

		/* create notify reply - keep same query contents */
		QR_SET(query->packet);         /* This is an answer.  */
		AA_SET(query->packet);	   /* we are authoritative. */
		ANCOUNT_SET(query->packet, 0);
		NSCOUNT_SET(query->packet, 0);
		ARCOUNT_SET(query->packet, 0);
		RCODE_SET(query->packet, RCODE_OK); /* Error code.  */
		/* position is right after the query */
		pos = buffer_position(query->packet);
		buffer_clear(query->packet);
		buffer_set_position(query->packet, pos);
		if(verbosity >= 1) {
			char address[128];
			addr2str(&query->addr, address, sizeof(address));
			VERBOSITY(2, (LOG_INFO, "notify for %s from %s",
				dname_to_string(query->qname, NULL), address));
		}
		/* tsig is added in add_additional later (if needed) */
		return QUERY_PROCESSED;
	}

	if (verbosity >= 1) {
		char address[128];
		addr2str(&query->addr, address, sizeof(address));
		VERBOSITY(1, (LOG_INFO, "notify for zone %s from client %s refused, %s%s",
			dname_to_string(query->qname, NULL),
			address,
			why?why->key_name:"no acl matches",
			why?why->ip_address_spec:"."));
	}

	return query_error(query, NSD_RC_REFUSE);
}


/*
 * Answer a query in the CHAOS class.
 */
static query_state_type
answer_chaos(struct nsd *nsd, query_type *q)
{
	AA_CLR(q->packet);
	switch (q->qtype) {
	case TYPE_ANY:
	case TYPE_TXT:
		if ((q->qname->name_size == 11
		     && memcmp(dname_name(q->qname), "\002id\006server", 11) == 0) ||
		    (q->qname->name_size ==  15
		     && memcmp(dname_name(q->qname), "\010hostname\004bind", 15) == 0))
		{
			/* Add ID */
			query_addtxt(q,
				     buffer_begin(q->packet) + QHEADERSZ,
				     CLASS_CH,
				     0,
				     nsd->identity);
			ANCOUNT_SET(q->packet, ANCOUNT(q->packet) + 1);
		} else if ((q->qname->name_size == 16
			    && memcmp(dname_name(q->qname), "\007version\006server", 16) == 0) ||
			   (q->qname->name_size == 14
			    && memcmp(dname_name(q->qname), "\007version\004bind", 14) == 0))
		{
			if(!nsd->options->hide_version) {
				/* Add version */
				query_addtxt(q,
				     buffer_begin(q->packet) + QHEADERSZ,
				     CLASS_CH,
				     0,
				     nsd->version);
				ANCOUNT_SET(q->packet, ANCOUNT(q->packet) + 1);
			} else {
				RCODE_SET(q->packet, RCODE_REFUSE);
			}
		}
		break;
	default:
		RCODE_SET(q->packet, RCODE_REFUSE);
		break;
	}

	return QUERY_PROCESSED;
}


/*
 * Find the covering NSEC for a non-existent domain name.  Normally
 * the NSEC will be located at CLOSEST_MATCH, except when it is an
 * empty non-terminal.  In this case the NSEC may be located at the
 * previous domain name (in canonical ordering).
 */
static domain_type *
find_covering_nsec(domain_type *closest_match,
		   zone_type   *zone,
		   rrset_type **nsec_rrset)
{
	assert(closest_match);
	assert(nsec_rrset);

	/* loop away temporary created domains. For real ones it is &RBTREE_NULL */
	while (closest_match->rnode == NULL)
		closest_match = closest_match->parent;
	while (closest_match) {
		*nsec_rrset = domain_find_rrset(closest_match, zone, TYPE_NSEC);
		if (*nsec_rrset) {
			return closest_match;
		}
		if (closest_match == zone->apex) {
			/* Don't look outside the current zone.  */
			return NULL;
		}
		closest_match = domain_previous(closest_match);
	}
	return NULL;
}


struct additional_rr_types
{
	uint16_t        rr_type;
	rr_section_type rr_section;
};

struct additional_rr_types default_additional_rr_types[] = {
	{ TYPE_A, ADDITIONAL_A_SECTION },
	{ TYPE_AAAA, ADDITIONAL_AAAA_SECTION },
	{ 0, (rr_section_type) 0 }
};

struct additional_rr_types rt_additional_rr_types[] = {
	{ TYPE_A, ADDITIONAL_A_SECTION },
	{ TYPE_AAAA, ADDITIONAL_AAAA_SECTION },
	{ TYPE_X25, ADDITIONAL_OTHER_SECTION },
	{ TYPE_ISDN, ADDITIONAL_OTHER_SECTION },
	{ 0, (rr_section_type) 0 }
};

static void
add_additional_rrsets(struct query *query, answer_type *answer,
		      rrset_type *master_rrset, size_t rdata_index,
		      int allow_glue, struct additional_rr_types types[])
{
	size_t i;

	assert(query);
	assert(answer);
	assert(master_rrset);
	assert(rdata_atom_is_domain(rrset_rrtype(master_rrset), rdata_index));

	for (i = 0; i < master_rrset->rr_count; ++i) {
		int j;
		domain_type *additional = rdata_atom_domain(master_rrset->rrs[i].rdatas[rdata_index]);
		domain_type *match = additional;

		assert(additional);

		if (!allow_glue && domain_is_glue(match, query->zone))
			continue;

		/*
		 * Check to see if we need to generate the dependent
		 * based on a wildcard domain.
		 */
		while (!match->is_existing) {
			match = match->parent;
		}
		if (additional != match && domain_wildcard_child(match)) {
			domain_type *wildcard_child = domain_wildcard_child(match);
			domain_type *temp = (domain_type *) region_alloc(
				query->region, sizeof(domain_type));
			temp->rnode = NULL;
			temp->dname = additional->dname;
			temp->number = additional->number;
			temp->parent = match;
			temp->wildcard_child_closest_match = temp;
			temp->rrsets = wildcard_child->rrsets;
			temp->is_existing = wildcard_child->is_existing;
			additional = temp;
		}

		for (j = 0; types[j].rr_type != 0; ++j) {
			rrset_type *rrset = domain_find_rrset(
				additional, query->zone, types[j].rr_type);
			if (rrset) {
				answer_add_rrset(answer, types[j].rr_section,
						 additional, rrset);
			}
		}
	}
}

static int
answer_needs_ns(struct query* query)
{
	assert(query);
	/* Currently, only troublesome for DNSKEY and DS,
         * cuz their RRSETs are quite large. */
	return (query->qtype != TYPE_DNSKEY && query->qtype != TYPE_DS);
}

static int
add_rrset(struct query   *query,
	  answer_type    *answer,
	  rr_section_type section,
	  domain_type    *owner,
	  rrset_type     *rrset)
{
	int result;

	assert(query);
	assert(answer);
	assert(owner);
	assert(rrset);
	assert(rrset_rrclass(rrset) == CLASS_IN);

	result = answer_add_rrset(answer, section, owner, rrset);
	switch (rrset_rrtype(rrset)) {
	case TYPE_NS:
		add_additional_rrsets(query, answer, rrset, 0, 1,
				      default_additional_rr_types);
		break;
	case TYPE_MB:
		add_additional_rrsets(query, answer, rrset, 0, 0,
				      default_additional_rr_types);
		break;
	case TYPE_MX:
	case TYPE_KX:
		add_additional_rrsets(query, answer, rrset, 1, 0,
				      default_additional_rr_types);
		break;
	case TYPE_RT:
		add_additional_rrsets(query, answer, rrset, 1, 0,
				      rt_additional_rr_types);
		break;
	default:
		break;
	}

	return result;
}


/* returns 0 on error, or the domain number for to_name.
   from_name is changes to to_name by the DNAME rr.
   DNAME rr is from src to dest.
   closest encloser encloses the to_name. */
static size_t
query_synthesize_cname(struct query* q, struct answer* answer, const dname_type* from_name,
	const dname_type* to_name, domain_type* src, domain_type* to_closest_encloser,
	domain_type** to_closest_match)
{
	/* add temporary domains for from_name and to_name and all
	   their (not allocated yet) parents */
	/* any domains below src are not_existing (because of DNAME at src) */
	int i;
	domain_type* cname_domain;
	domain_type* cname_dest;
	rrset_type* rrset;

	/* allocate source part */
	domain_type* lastparent = src;
	assert(q && answer && from_name && to_name && src && to_closest_encloser);
	assert(to_closest_match);
	for(i=0; i < from_name->label_count - domain_dname(src)->label_count; i++)
	{
		domain_type* newdom = query_get_tempdomain(q);
		if(!newdom)
			return 0;
		newdom->is_existing = 1;
		newdom->parent = lastparent;
		newdom->dname
			= dname_partial_copy(q->region,
			from_name, domain_dname(src)->label_count + i + 1);
		if(dname_compare(domain_dname(newdom), q->qname) == 0) {
			/* 0 good for query name, otherwise new number */
			newdom->number = 0;
		}
		DEBUG(DEBUG_QUERY,2, (LOG_INFO, "created temp domain src %d. %s nr %d", i,
			domain_to_string(newdom), (int)newdom->number));
		lastparent = newdom;
	}
	cname_domain = lastparent;

	/* allocate dest part */
	lastparent = to_closest_encloser;
	for(i=0; i < to_name->label_count - domain_dname(to_closest_encloser)->label_count;
		i++)
	{
		domain_type* newdom = query_get_tempdomain(q);
		if(!newdom)
			return 0;
		newdom->is_existing = 0;
		newdom->parent = lastparent;
		newdom->dname
			= dname_partial_copy(q->region,
			to_name, domain_dname(to_closest_encloser)->label_count + i + 1);
		DEBUG(DEBUG_QUERY,2, (LOG_INFO, "created temp domain dest %d. %s nr %d", i,
			domain_to_string(newdom), (int)newdom->number));
		lastparent = newdom;
	}
	cname_dest = lastparent;
	*to_closest_match = cname_dest;

	/* allocate the CNAME RR */
	rrset = (rrset_type*) region_alloc(q->region, sizeof(rrset_type));
	memset(rrset, 0, sizeof(rrset_type));
	rrset->zone = q->zone;
	rrset->rr_count = 1;
	rrset->rrs = (rr_type*) region_alloc(q->region, sizeof(rr_type));
	memset(rrset->rrs, 0, sizeof(rr_type));
	rrset->rrs->owner = cname_domain;
	rrset->rrs->ttl = 0;
	rrset->rrs->type = TYPE_CNAME;
	rrset->rrs->klass = CLASS_IN;
	rrset->rrs->rdata_count = 1;
	rrset->rrs->rdatas = (rdata_atom_type*)region_alloc(q->region,
		sizeof(rdata_atom_type));
	rrset->rrs->rdatas->domain = cname_dest;

	if(!add_rrset(q, answer, ANSWER_SECTION, cname_domain, rrset)) {
		log_msg(LOG_ERR, "could not add synthesized CNAME rrset to packet");
	}

	return cname_dest->number;
}

/*
 * Answer delegation information.
 *
 * DNSSEC: Include the DS RRset if present.  Otherwise include an NSEC
 * record proving the DS RRset does not exist.
 */
static void
answer_delegation(query_type *query, answer_type *answer)
{
	assert(answer);
	assert(query->delegation_domain);
	assert(query->delegation_rrset);

	if (query->cname_count == 0) {
		AA_CLR(query->packet);
	} else {
		AA_SET(query->packet);
	}

	add_rrset(query,
		  answer,
		  AUTHORITY_SECTION,
		  query->delegation_domain,
		  query->delegation_rrset);
	if (query->edns.dnssec_ok && zone_is_secure(query->zone)) {
		rrset_type *rrset;
		if ((rrset = domain_find_rrset(query->delegation_domain, query->zone, TYPE_DS))) {
			add_rrset(query, answer, AUTHORITY_SECTION,
				  query->delegation_domain, rrset);
#ifdef NSEC3
		} else if (query->zone->nsec3_param) {
			nsec3_answer_delegation(query, answer);
#endif
		} else if ((rrset = domain_find_rrset(query->delegation_domain, query->zone, TYPE_NSEC))) {
			add_rrset(query, answer, AUTHORITY_SECTION,
				  query->delegation_domain, rrset);
		}
	}
}


/*
 * Answer SOA information.
 */
static void
answer_soa(struct query *query, answer_type *answer)
{
	if (query->qclass != CLASS_ANY) {
		add_rrset(query, answer,
			  AUTHORITY_SECTION,
			  query->zone->apex,
			  query->zone->soa_nx_rrset);
	}
}


/*
 * Answer that the domain name exists but there is no RRset with the
 * requested type.
 *
 * DNSSEC: Include the correct NSEC record proving that the type does
 * not exist.  In the wildcard no data (3.1.3.4) case the wildcard IS
 * NOT expanded, so the ORIGINAL parameter must point to the original
 * wildcard entry, not to the generated entry.
 */
static void
answer_nodata(struct query *query, answer_type *answer, domain_type *original)
{
	if (query->cname_count == 0) {
		answer_soa(query, answer);
	}

#ifdef NSEC3
	if (query->edns.dnssec_ok && query->zone->nsec3_param) {
		nsec3_answer_nodata(query, answer, original);
	} else
#endif
	if (query->edns.dnssec_ok && zone_is_secure(query->zone)) {
		domain_type *nsec_domain;
		rrset_type *nsec_rrset;

		nsec_domain = find_covering_nsec(original, query->zone, &nsec_rrset);
		if (nsec_domain) {
			add_rrset(query, answer, AUTHORITY_SECTION, nsec_domain, nsec_rrset);
		}
	}
}

static void
answer_nxdomain(query_type *query, answer_type *answer)
{
	RCODE_SET(query->packet, RCODE_NXDOMAIN);
	answer_soa(query, answer);
}


/*
 * Answer domain information (or SOA if we do not have an RRset for
 * the type specified by the query).
 */
static void
answer_domain(struct nsd* nsd, struct query *q, answer_type *answer,
	      domain_type *domain, domain_type *original)
{
	rrset_type *rrset;

	if (q->qtype == TYPE_ANY) {
		int added = 0;
		for (rrset = domain_find_any_rrset(domain, q->zone); rrset; rrset = rrset->next) {
			if (rrset->zone == q->zone
#ifdef NSEC3
				&& rrset_rrtype(rrset) != TYPE_NSEC3
#endif
			    /*
			     * Don't include the RRSIG RRset when
			     * DNSSEC is used, because it is added
			     * automatically on an per-RRset basis.
			     */
			    && !(q->edns.dnssec_ok
				 && zone_is_secure(q->zone)
				 && rrset_rrtype(rrset) == TYPE_RRSIG))
			{
				add_rrset(q, answer, ANSWER_SECTION, domain, rrset);
				++added;
			}
		}
		if (added == 0) {
			answer_nodata(q, answer, original);
			return;
		}
#ifdef NSEC3
	} else if (q->qtype == TYPE_NSEC3) {
		answer_nodata(q, answer, original);
		return;
#endif
	} else if ((rrset = domain_find_rrset(domain, q->zone, q->qtype))) {
		add_rrset(q, answer, ANSWER_SECTION, domain, rrset);
	} else if ((rrset = domain_find_rrset(domain, q->zone, TYPE_CNAME))) {
		int added;

		/*
		 * If the CNAME is not added it is already in the
		 * answer, so we have a CNAME loop.  Don't follow the
		 * CNAME target in this case.
		 */
		added = add_rrset(q, answer, ANSWER_SECTION, domain, rrset);
		assert(rrset->rr_count > 0);
		if (added) {
			/* only process first CNAME record */
			domain_type *closest_match = rdata_atom_domain(rrset->rrs[0].rdatas[0]);
			domain_type *closest_encloser = closest_match;
			zone_type* origzone = q->zone;
			++q->cname_count;

			while (!closest_encloser->is_existing)
				closest_encloser = closest_encloser->parent;

			answer_lookup_zone(nsd, q, answer, closest_match->number,
					     closest_match == closest_encloser,
					     closest_match, closest_encloser,
					     domain_dname(closest_match));
			q->zone = origzone;
		}
		return;
	} else {
		answer_nodata(q, answer, original);
		return;
	}

	if (q->qclass != CLASS_ANY && q->zone->ns_rrset && answer_needs_ns(q)) {
		add_rrset(q, answer, OPTIONAL_AUTHORITY_SECTION, q->zone->apex,
			  q->zone->ns_rrset);
	}
}


/*
 * Answer with authoritative data.  If a wildcard is matched the owner
 * name will be expanded to the domain name specified by
 * DOMAIN_NUMBER.  DOMAIN_NUMBER 0 (zero) is reserved for the original
 * query name.
 *
 * DNSSEC: Include the necessary NSEC records in case the request
 * domain name does not exist and/or a wildcard match does not exist.
 */
static void
answer_authoritative(struct nsd   *nsd,
		     struct query *q,
		     answer_type  *answer,
		     size_t        domain_number,
		     int           exact,
		     domain_type  *closest_match,
		     domain_type  *closest_encloser,
		     const dname_type *qname)
{
	domain_type *match;
	domain_type *original = closest_match;
	rrset_type *rrset;

#ifdef NSEC3
	if(exact && domain_has_only_NSEC3(closest_match, q->zone)) {
		exact = 0; /* pretend it does not exist */
		if(closest_encloser->parent)
			closest_encloser = closest_encloser->parent;
	}
#endif /* NSEC3 */

	if (exact) {
		match = closest_match;
	} else if ((rrset=domain_find_rrset(closest_encloser, q->zone, TYPE_DNAME))) {
		/* process DNAME */
		const dname_type* name = qname;
		domain_type *dest = rdata_atom_domain(rrset->rrs[0].rdatas[0]);
		int added;
		assert(rrset->rr_count > 0);
		if(domain_number != 0) /* we followed CNAMEs or DNAMEs */
			name = domain_dname(closest_match);
		DEBUG(DEBUG_QUERY,2, (LOG_INFO, "expanding DNAME for q=%s", dname_to_string(name, NULL)));
		DEBUG(DEBUG_QUERY,2, (LOG_INFO, "->src is %s",
			domain_to_string(closest_encloser)));
		DEBUG(DEBUG_QUERY,2, (LOG_INFO, "->dest is %s",
			domain_to_string(dest)));
		/* if the DNAME set is not added we have a loop, do not follow */
		added = add_rrset(q, answer, ANSWER_SECTION, closest_encloser, rrset);
		if(added) {
			domain_type* src = closest_encloser;
			const dname_type* newname = dname_replace(q->region, name,
				domain_dname(src), domain_dname(dest));
			size_t newnum = 0;
			zone_type* origzone = q->zone;
			++q->cname_count;
			if(!newname) { /* newname too long */
				RCODE_SET(q->packet, RCODE_YXDOMAIN);
				return;
			}
			DEBUG(DEBUG_QUERY,2, (LOG_INFO, "->result is %s", dname_to_string(newname, NULL)));
			/* follow the DNAME */
			exact = namedb_lookup(nsd->db, newname, &closest_match, &closest_encloser);
			/* synthesize CNAME record */
			newnum = query_synthesize_cname(q, answer, name, newname,
				src, closest_encloser, &closest_match);
			if(!newnum) {
				/* could not synthesize the CNAME. */
				/* return previous CNAMEs to make resolver recurse for us */
				return;
			}

			while (closest_encloser && !closest_encloser->is_existing)
				closest_encloser = closest_encloser->parent;
			answer_lookup_zone(nsd, q, answer, newnum,
				closest_match == closest_encloser,
				closest_match, closest_encloser, newname);
			q->zone = origzone;
		}
		if(!added)  /* log the error so operator can find looping recursors */
			log_msg(LOG_INFO, "DNAME processing stopped due to loop, qname %s",
				dname_to_string(q->qname, NULL));
		return;
	} else if (domain_wildcard_child(closest_encloser)) {
		/* Generate the domain from the wildcard.  */
		domain_type *wildcard_child = domain_wildcard_child(closest_encloser);
#ifdef RATELIMIT
		q->wildcard_domain = wildcard_child;
#endif

		match = (domain_type *) region_alloc(q->region,
						     sizeof(domain_type));
		match->rnode = NULL;
		match->dname = wildcard_child->dname;
		match->parent = closest_encloser;
		match->wildcard_child_closest_match = match;
		match->number = domain_number;
		match->rrsets = wildcard_child->rrsets;
		match->is_existing = wildcard_child->is_existing;
#ifdef NSEC3
		match->nsec3 = wildcard_child->nsec3;
		/* copy over these entries:
		match->nsec3_is_exact = wildcard_child->nsec3_is_exact;
		match->nsec3_cover = wildcard_child->nsec3_cover;
		match->nsec3_wcard_child_cover = wildcard_child->nsec3_wcard_child_cover;
		match->nsec3_ds_parent_is_exact = wildcard_child->nsec3_ds_parent_is_exact;
		match->nsec3_ds_parent_cover = wildcard_child->nsec3_ds_parent_cover;
		*/

		if (q->edns.dnssec_ok && q->zone->nsec3_param) {
			/* Only add nsec3 wildcard data when do bit is set */
			nsec3_answer_wildcard(q, answer, wildcard_child, qname);
		}
#endif

		/*
		 * Remember the original domain in case a Wildcard No
		 * Data (3.1.3.4) response needs to be generated.  In
		 * this particular case the wildcard IS NOT
		 * expanded.
		 */
		original = wildcard_child;
	} else {
		match = NULL;
	}

	/* Authorative zone.  */
#ifdef NSEC3
	if (q->edns.dnssec_ok && q->zone->nsec3_param) {
		nsec3_answer_authoritative(&match, q, answer,
			closest_encloser, qname);
	} else
#endif
	if (q->edns.dnssec_ok && zone_is_secure(q->zone)) {
		if (match != closest_encloser) {
			domain_type *nsec_domain;
			rrset_type *nsec_rrset;

			/*
			 * No match found or generated from wildcard,
			 * include NSEC record.
			 */
			nsec_domain = find_covering_nsec(closest_match, q->zone, &nsec_rrset);
			if (nsec_domain) {
				add_rrset(q, answer, AUTHORITY_SECTION, nsec_domain, nsec_rrset);
			}
		}
		if (!match) {
			domain_type *nsec_domain;
			rrset_type *nsec_rrset;

			/*
			 * No match and no wildcard.  Include NSEC
			 * proving there is no wildcard.
			 */
			nsec_domain = find_covering_nsec(closest_encloser->wildcard_child_closest_match, q->zone, &nsec_rrset);
			if (nsec_domain) {
				add_rrset(q, answer, AUTHORITY_SECTION, nsec_domain, nsec_rrset);
			}
		}
	}

#ifdef NSEC3
	if (RCODE(q->packet)!=RCODE_OK) {
		return; /* nsec3 collision failure */
	}
#endif
	if (match) {
		answer_domain(nsd, q, answer, match, original);
	} else {
		answer_nxdomain(q, answer);
	}
}

/*
 * qname may be different after CNAMEs have been followed from query->qname.
 */
static void
answer_lookup_zone(struct nsd *nsd, struct query *q, answer_type *answer,
	size_t domain_number, int exact, domain_type *closest_match,
	domain_type *closest_encloser, const dname_type *qname)
{
	q->zone = domain_find_zone(nsd->db, closest_encloser);
	if (!q->zone) {
		/* no zone for this */
		if(q->cname_count == 0)
			RCODE_SET(q->packet, RCODE_REFUSE);
		return;
	}
	if(!q->zone->apex || !q->zone->soa_rrset) {
		/* zone is configured but not loaded */
		if(q->cname_count == 0)
			RCODE_SET(q->packet, RCODE_SERVFAIL);
		return;
	}

	/*
	 * See RFC 4035 (DNSSEC protocol) section 3.1.4.1 Responding
	 * to Queries for DS RRs.
	 */
	if (exact && q->qtype == TYPE_DS && closest_encloser == q->zone->apex) {
		/*
		 * Type DS query at a zone cut, use the responsible
		 * parent zone to generate the answer if we are
		 * authoritative for the parent zone.
		 */
		zone_type *zone = domain_find_parent_zone(q->zone);
		if (zone)
			q->zone = zone;
	}

	/* see if the zone has expired (for secondary zones) */
	if(q->zone && q->zone->opts && q->zone->opts->pattern &&
		q->zone->opts->pattern->request_xfr != 0 && !q->zone->is_ok) {
		if(q->cname_count == 0)
			RCODE_SET(q->packet, RCODE_SERVFAIL);
		return;
	}

	if (exact && q->qtype == TYPE_DS && closest_encloser == q->zone->apex) {
		/*
		 * Type DS query at the zone apex (and the server is
		 * not authoratitive for the parent zone).
		 */
		if (q->qclass == CLASS_ANY) {
			AA_CLR(q->packet);
		} else {
			AA_SET(q->packet);
		}
		answer_nodata(q, answer, closest_encloser);
	} else {
		q->delegation_domain = domain_find_ns_rrsets(
			closest_encloser, q->zone, &q->delegation_rrset);

		if (!q->delegation_domain
		    || (exact && q->qtype == TYPE_DS && closest_encloser == q->delegation_domain))
		{
			if (q->qclass == CLASS_ANY) {
				AA_CLR(q->packet);
			} else {
				AA_SET(q->packet);
			}
			answer_authoritative(nsd, q, answer, domain_number, exact,
					     closest_match, closest_encloser, qname);
		}
		else {
			answer_delegation(q, answer);
		}
	}
}

static void
answer_query(struct nsd *nsd, struct query *q)
{
	domain_type *closest_match;
	domain_type *closest_encloser;
	int exact;
	uint16_t offset;
	answer_type answer;
	
	answer_init(&answer);
	exact = namedb_lookup(nsd->db, q->qname, &closest_match, &closest_encloser);
	if (!closest_encloser->is_existing) {
		exact = 0;
		while (closest_encloser != NULL && !closest_encloser->is_existing)
			closest_encloser = closest_encloser->parent;
	}
	if(!closest_encloser) {
		RCODE_SET(q->packet, RCODE_SERVFAIL);
		return;
	}

	answer_lookup_zone(nsd, q, &answer, 0, exact, closest_match,
		closest_encloser, q->qname);

	offset = dname_label_offsets(q->qname)[domain_dname(closest_encloser)->label_count - 1] + QHEADERSZ;
	query_add_compression_domain(q, closest_encloser, offset);
#ifdef DNSX_GSLB
/*	 log_msg(LOG_INFO, "check isp idx before answer_query");
*/	 q->geo_tree = nsd->geo_tree;
    q->client_isp = dnsx_search_ip_from_geodb(q);
#endif
	encode_answer(q, &answer);
	query_clear_compression_tables(q);
}

void
query_prepare_response(query_type *q)
{
	uint16_t flags;

	/*
	 * Preserve the data up-to the current packet's limit.
	 */
	buffer_set_position(q->packet, buffer_limit(q->packet));
	buffer_set_limit(q->packet, buffer_capacity(q->packet));

	/*
	 * Reserve space for the EDNS records if required.
	 */
	q->reserved_space = edns_reserved_space(&q->edns);
	q->reserved_space += tsig_reserved_space(&q->tsig);

	/* Update the flags.  */
	flags = FLAGS(q->packet);
	flags &= 0x0100U;	/* Preserve the RD flag.  */
				/* CD flag must be cleared for auth answers */
	flags |= 0x8000U;	/* Set the QR flag.  */
	FLAGS_SET(q->packet, flags);
}

/*
 * Processes the query.
 *
 */
query_state_type
query_process(query_type *q, nsd_type *nsd)
{
	/* The query... */
	nsd_rc_type rc;
	query_state_type query_state;
	uint16_t arcount;

	/* Sanity checks */
	if (buffer_limit(q->packet) < QHEADERSZ) {
		/* packet too small to contain DNS header.
		Now packet investigation macros will work without problems. */
		return QUERY_DISCARDED;
	}
	if (QR(q->packet)) {
		/* Not a query? Drop it on the floor. */
		return QUERY_DISCARDED;
	}

	if (RCODE(q->packet) != RCODE_OK || !process_query_section(q)) {
		return query_formerr(q);
	}

	/* Update statistics.  */
	STATUP2(nsd, opcode, q->opcode);
	STATUP2(nsd, qtype, q->qtype);
	STATUP2(nsd, qclass, q->qclass);

	if (q->opcode != OPCODE_QUERY) {
		if (q->opcode == OPCODE_NOTIFY) {
			return answer_notify(nsd, q);
		} else {
			return query_error(q, NSD_RC_IMPL);
		}
	}

	/* Dont bother to answer more than one question at once... */
	if (QDCOUNT(q->packet) != 1) {
		FLAGS_SET(q->packet, 0);
		return query_formerr(q);
	}
	/* Ignore settings of flags */

	/* Dont allow any records in the answer or authority section...
	   except for IXFR queries. */
	if (ANCOUNT(q->packet) != 0 ||
		(q->qtype!=TYPE_IXFR && NSCOUNT(q->packet) != 0)) {
		return query_formerr(q);
	}
	if(q->qtype==TYPE_IXFR && NSCOUNT(q->packet) > 0) {
		int i; /* skip ixfr soa information data here */
		for(i=0; i< NSCOUNT(q->packet); i++)
			if(!packet_skip_rr(q->packet, 0))
				return query_formerr(q);
	}

	arcount = ARCOUNT(q->packet);
	if (arcount > 0) {
		/* According to draft-ietf-dnsext-rfc2671bis-edns0-10:
		 * "The placement flexibility for the OPT RR does not
		 * override the need for the TSIG or SIG(0) RRs to be
		 * the last in the additional section whenever they are
		 * present."
		 * So we should not have to check for TSIG RR before
		 * OPT RR. Keep the code for backwards compatibility.
		 */

		/* see if tsig is before edns record */
		if (!tsig_parse_rr(&q->tsig, q->packet))
			return query_formerr(q);
		if(q->tsig.status != TSIG_NOT_PRESENT)
			--arcount;
	}
	/* See if there is an OPT RR. */
	q->edns.client_subnet_ok = 0;
	if (arcount > 0) {
		if (edns_parse_record(&q->edns, q->packet))
			--arcount;
	}
	/* See if there is a TSIG RR. */
	if (arcount > 0 && q->tsig.status == TSIG_NOT_PRESENT) {
		/* see if tsig is after the edns record */
		if (!tsig_parse_rr(&q->tsig, q->packet))
			return query_formerr(q);
		if(q->tsig.status != TSIG_NOT_PRESENT)
			--arcount;
	}
	/* If more RRs left in Add. Section, FORMERR. */
	if (arcount > 0) {
		return query_formerr(q);
	}

	/* Do we have any trailing garbage? */
#ifdef	STRICT_MESSAGE_PARSE
	if (buffer_remaining(q->packet) > 0) {
		/* If we're strict.... */
		return query_formerr(q);
	}
#endif
	/* Remove trailing garbage.  */
	buffer_set_limit(q->packet, buffer_position(q->packet));

	rc = process_tsig(q);
	if (rc != NSD_RC_OK) {
		return query_error(q, rc);
	}
	rc = process_edns(nsd, q);
	if (rc != NSD_RC_OK) {
		/* We should not return FORMERR, but BADVERS (=16).
		 * BADVERS is created with Ext. RCODE, followed by RCODE.
		 * Ext. RCODE is set to 1, RCODE must be 0 (getting 0x10 = 16).
		 * Thus RCODE = NOERROR = NSD_RC_OK. */
		return query_error(q, NSD_RC_OK);
	}

	query_prepare_response(q);

	if (q->qclass != CLASS_IN && q->qclass != CLASS_ANY) {
		if (q->qclass == CLASS_CH) {
			return answer_chaos(nsd, q);
		} else {
			return query_error(q, NSD_RC_REFUSE);
		}
	}

	query_state = answer_axfr_ixfr(nsd, q);
	if (query_state == QUERY_PROCESSED || query_state == QUERY_IN_AXFR) {
		return query_state;
	}
	answer_query(nsd, q);

	return QUERY_PROCESSED;
}

void
query_add_optional(query_type *q, nsd_type *nsd)
{
	struct edns_data *edns = &nsd->edns_ipv4;
#if defined(INET6)
	if (q->addr.ss_family == AF_INET6) {
		edns = &nsd->edns_ipv6;
	}
#endif
	if (RCODE(q->packet) == RCODE_FORMAT) {
		return;
	}
	switch (q->edns.status) {
	case EDNS_NOT_PRESENT:
		break;
	case EDNS_OK:
		if (q->edns.dnssec_ok)	edns->ok[7] = 0x80;
		else			edns->ok[7] = 0x00;
		buffer_write(q->packet, edns->ok, OPT_LEN);
		if (nsd->nsid_len > 0 && q->edns.nsid == 1 &&
				!query_overflow_nsid(q, nsd->nsid_len)) {
			/* rdata length */
			buffer_write(q->packet, edns->rdata_nsid, OPT_RDATA);
			/* nsid opt header */
			buffer_write(q->packet, edns->nsid, OPT_HDR);
			/* nsid payload */
			buffer_write(q->packet, nsd->nsid, nsd->nsid_len);
		}  else {
			/* fill with NULLs */
			buffer_write(q->packet, edns->rdata_none, OPT_RDATA);
		}
		ARCOUNT_SET(q->packet, ARCOUNT(q->packet) + 1);
		STATUP(nsd, edns);
		break;
	case EDNS_ERROR:
		if (q->edns.dnssec_ok)	edns->error[7] = 0x80;
		else			edns->error[7] = 0x00;
		buffer_write(q->packet, edns->error, OPT_LEN);
		buffer_write(q->packet, edns->rdata_none, OPT_RDATA);
		ARCOUNT_SET(q->packet, ARCOUNT(q->packet) + 1);
		STATUP(nsd, ednserr);
		break;
	}

	if (q->tsig.status != TSIG_NOT_PRESENT) {
		if (q->tsig.status == TSIG_ERROR ||
			q->tsig.error_code != TSIG_ERROR_NOERROR) {
			tsig_error_reply(&q->tsig);
			tsig_append_rr(&q->tsig, q->packet);
			ARCOUNT_SET(q->packet, ARCOUNT(q->packet) + 1);
		} else if(q->tsig.status == TSIG_OK &&
			q->tsig.error_code == TSIG_ERROR_NOERROR)
		{
			if(q->tsig_prepare_it)
				tsig_prepare(&q->tsig);
			if(q->tsig_update_it)
				tsig_update(&q->tsig, q->packet, buffer_position(q->packet));
			if(q->tsig_sign_it) {
				tsig_sign(&q->tsig);
				tsig_append_rr(&q->tsig, q->packet);
				ARCOUNT_SET(q->packet, ARCOUNT(q->packet) + 1);
			}
		}
	}
}
