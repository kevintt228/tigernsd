
#include "config.h"
#ifdef DNSX_GSLB
#include "options.h"
#include "nsd.h"
#include "util.h"
#include "rrl.h"
#include "query.h"
#include "dnsx_list.h"
#include "dnsx_hash.h"
#include "geo_core.h"
#include "jhash.h"

#define SVC_IPV4_HASH_SIZE (1 << 16)
#define NON_ISP_INDEX (31)

static hash_t *g_svc_ipv4_hash = NULL;
static region_type *g_svc_ipv4_region = NULL;
static geo_radix_tree_t *g_geo_ipv4_tree = NULL;

static int svc_ipv4_data_hash_func(const void *key)   
{
	const u8 *ipaddr = key;                          
	return jhash(ipaddr, 4, 0) % SVC_IPV4_HASH_SIZE;    
}

static void *svc_ipv4_data_l2k_func(struct list_head *link)
{
	svc_ipv4_hash_item_t *h = container_of(link, svc_ipv4_hash_item_t, link);
	return &h->ipaddr;                                
}

static int svc_ipv4_data_comp_func(struct list_head *link, const void *key)
{
	const u32 *ipaddr = key;
	u32 *item_key = svc_ipv4_data_l2k_func(link);
	return (*item_key != *ipaddr);                    
}

int dnsx_svc_ip_init()
{
	g_svc_ipv4_hash =  hash_create(SVC_IPV4_HASH_SIZE,
									svc_ipv4_data_hash_func,
									svc_ipv4_data_comp_func,
									svc_ipv4_data_l2k_func);
	g_svc_ipv4_region = region_create(xalloc_zero, free);
	if (!g_svc_ipv4_hash) {
		log_msg(LOG_ERR, "fail to create region for service IPv4 hash");
		return -1;
	}

	return 0;
}

static inline int dnsx_ipv4_cache_item_init(svc_ipv4_hash_item_t *h, u32 ipaddr, 
	geo_radix_node_rr_t *ret)
{
	h->ipaddr = ipaddr;
	if (ret) {
		h->isp_idx = ret->isp_idx;
		memcpy(h->isp_province, ret->isp_province, sizeof(h->isp_province));
	} else {
		h->isp_idx = NON_ISP_INDEX;
	}
	INIT_LIST_HEAD(&h->link);
	INIT_LIST_HEAD(&h->child_rrs);

	return 0;
}

inline void dnsx_attach_rr_to_cache(svc_ipv4_hash_item_t *hash_item, rr_type *rr)
{
	list_add_rcu(&rr->cache_link, &hash_item->child_rrs);
	rr->cache_item = hash_item;
}

inline void dnsx_dettach_rr_from_cache(rr_type *rr)
{
	list_del_rcu(&rr->cache_link);
	rr->cache_item = NULL;
}

#if 0
static inline void dnsx_debug_rr(rr_type *rr)
{
	svc_ipv4_hash_item_t *hash_item;
	u32 ip = *(u32 *)(rr->rdatas[0].data + 1);
	ip = ntohl(ip);
	log_msg(LOG_INFO, "\ndebug service ip %u.%u.%u.%u in hash list", ((u8 *)(&ip))[3],
					((u8 *)(&ip))[2],((u8 *)(&ip))[1], ((u8 *)(&ip))[0]);
	hash_item = (typeof(hash_item))rr->cache_item;
	if (hash_item) {
		log_msg(LOG_INFO, "===>debug service ip, cache_item=%p isp_index=%hhu area=%c%c\n",hash_item, hash_item->isp_idx,
						hash_item->isp_province[0], hash_item->isp_province[1]);
	} else {
		log_msg(LOG_INFO, "===>debug service ip, not attached to service ip hash list\n\n");
	}

}
#else
static inline void dnsx_debug_rr(rr_type *rr)
{
}
#endif
int dnsx_get_best_rr_from_rrset(query_type *q ,rrset_type *rrset)
{
	uint16_t i;
	int best = DNSX_GSLB_SKIP;
	rr_type *rr;
	geo_radix_node_rr_t *client_isp;
	svc_ipv4_hash_item_t *cache_item;

	client_isp = dnsx_search_ip_from_geodb(q);
	if (client_isp == (typeof(client_isp))GEO_RADIX_NO_VALUE) {
		return best;
	}

	for (i = 0; i < rrset->rr_count; i++) {
		rr = &rrset->rrs[i];
		if (rr->type != TYPE_A) {
			return DNSX_GSLB_SKIP;
		}
		dnsx_debug_rr(rr);
		cache_item = (typeof(cache_item))rr->cache_item;
		if (cache_item && cache_item->isp_idx == client_isp->isp_idx) {
			return i;
		}
	}

	return best;
}

int dnsx_add_ip_rr_to_cache(rr_type *rr)
{
	geo_radix_node_rr_t *ret;		
		
	assert(rr);
	assert(rr->rdata_count > 0);
	if (!g_geo_ipv4_tree) {
		return 0;
	}

	if (rr->type == TYPE_A) {
		svc_ipv4_hash_item_t *hash_item;
		u32 ip = *(u32 *)(rr->rdatas[0].data + 1);
		ip = ntohl(ip);
		if ((hash_item = hash_lookup(g_svc_ipv4_hash, &ip)) != NULL) {
			log_msg(LOG_INFO, "Already added service ip %u.%u.%u.%u in hash list", ((u8 *)(&ip))[3],
						((u8 *)(&ip))[2],((u8 *)(&ip))[1], ((u8 *)(&ip))[0]);
			dnsx_attach_rr_to_cache(hash_item, rr);
			dnsx_debug_rr(rr);
			return 0;
		} else {
			log_msg(LOG_INFO, "First time to add service ip %u.%u.%u.%u in hash list", ((u8 *)(&ip))[3],
						((u8 *)(&ip))[2],((u8 *)(&ip))[1], ((u8 *)(&ip))[0]);
		}

		log_msg(LOG_INFO, "===>try to search service ip %u.%u.%u.%u in Geo DB", ((u8 *)(&ip))[3],
						((u8 *)(&ip))[2],((u8 *)(&ip))[1], ((u8 *)(&ip))[0]);
		if (dnsx_search_ip4_from_geodb(g_geo_ipv4_tree, ip, &ret)) {
			log_msg(LOG_INFO, "========>found service ip entry %u %s", ret->isp_idx, ret->isp_province);
		} else {
			log_msg(LOG_INFO, "=====>Not found entry for service ip");
		}
		hash_item = region_alloc(g_svc_ipv4_region, sizeof(*hash_item));
		dnsx_ipv4_cache_item_init(hash_item, ip, ret);
		hash_insert(g_svc_ipv4_hash, &hash_item->link);
		dnsx_attach_rr_to_cache(hash_item, rr);
		dnsx_debug_rr(rr);
	}

	return 0;
}

int parse_geo_db(struct nsd *ctx)
{
	FILE *file = NULL;
	region_type* geo_region;
	char line[MAX_LINE_LEN];
	geo_cidr_t cidr;
	geo_radix_node_rr_t *geo_rr;
	int ret;

	if (!ctx->options->geo_db_filepath) {
		return 0;
	}

	if ((file = fopen(ctx->options->geo_db_filepath, "r")) == NULL) {
		return -1;
	}
	geo_region = region_create(xalloc, free);
	if (!geo_region) {
		log_msg(LOG_ERR, "fail to create region for Geo module");
		return -1;
	}
	ctx->geo_tree = geo_radix_tree_create(geo_region, -1);
	g_geo_ipv4_tree = ctx->geo_tree;

	while (fgets(line, sizeof(line), file)) {
		char *start, *end;
		int field_num = 0;
		start = line;
		while ((end = index(start, ' '))) {
			*end = '\0';
			switch (field_num) {
			case 0:  /*IP start address*/
				if (inet_pton(AF_INET, start, &cidr.u.in.addr)) {
					cidr.family = AF_INET;
#if (GEO_HAVE_INET6)
				} else if (inet_pton(AF_INET6, start, &cidr.u.in6.addri)) {
					cidr.family = AF_INET6;
#endif
				} else {
					log_msg(LOG_ERR, "The fist field of line %s is not valid ", line);
					return -1;
				}
				
				break;
			case 1:
				if (cidr.family == AF_INET)	{
					cidr.u.in.mask = atoi(start);
					if (cidr.u.in.mask > 32) {
						log_msg(LOG_ERR, "invalid netmask of line %s", line);
						return -1;
					}
				}
#if (GEO_HAVE_INET6)
				else if (cidr.family == AF_INET6) {
					cidr.u.in6.mask = atoi(start);
				}
#endif
				break;
			case 2:
				geo_rr = region_alloc(geo_region, sizeof(*geo_rr));
				if (!geo_rr) {
					log_msg(LOG_ERR, "fail to alloc mem for geo_rr for line %s", line);
					return -1;
				}
				geo_rr->isp_idx = atoi(start);
				break;
			default:
				log_msg(LOG_ERR, "line %s has too many fields ", line);
				return -1;
				break;
			}
			field_num++;
			start = ++end;
		}
		if (end = index(start, '\n')) {
			end = '\0';
		}
		strncpy(geo_rr->isp_province, start, sizeof(geo_rr->isp_province));
		geo_rr->isp_province[sizeof(geo_rr->isp_province) - 1] = '\0';
	
		/*data is ready so insert that into the tree*/
		switch (cidr.family) {
		case AF_INET:
			cidr.u.in.mask = htonl((uint32_t) (0xffffffffu << (32 - cidr.u.in.mask)));
			if (cidr.u.in.addr == (cidr.u.in.addr & cidr.u.in.mask)) {
				cidr.u.in.addr &= cidr.u.in.mask;
			}
			cidr.u.in.mask = ntohl(cidr.u.in.mask);
			cidr.u.in.addr = ntohl(cidr.u.in.addr);
			ret = geo_radix32tree_insert(ctx->geo_tree, cidr.u.in.addr, 
							cidr.u.in.mask, (uintptr_t)geo_rr);
			if (ret != NSD_OK) {
				log_msg(LOG_ERR, "fail to insert line %s into tree ", line);
				return -1;
			} 			
			break;
#if (GEO_HAVE_INET6)
		case AF_INET6:
#endif
		default:
			break;
		}
	}

	dnsx_svc_ip_init();

	return 0;
}

/*return 1 on success and fill the returned node in parameter ret;
 * 0 on failure and fill the parameter ret with NULL*/
int dnsx_search_ip4_from_geodb(geo_radix_tree_t *geo_tree, u32 net_cip, geo_radix_node_rr_t **ret)
{
	geo_radix_node_rr_t *tmp = NULL;
	u32 host_cip = ntohl(net_cip);

	tmp = (typeof(tmp))geo_radix32tree_find(geo_tree, net_cip);
	if (tmp != (typeof(tmp))GEO_RADIX_NO_VALUE) {
		if (ret != NULL) {
			*ret = tmp;
		}
		return 1;
	}

	if (ret) {
		*ret = NULL;
	}

	return 0;
}

geo_radix_node_rr_t *dnsx_search_ip_from_geodb(struct query *q)
{
	u64 client_ip;
	u16 tmp;

	geo_radix_node_rr_t *ret = NULL;

	if (!q->geo_tree) {
		return NULL;
	}

	client_ip = rrl_get_source(q, &tmp);
#ifdef INET6
	if (((struct sockaddr_in*)&q->addr)->sin_family == AF_INET6) {
	} else 
#endif
	{
		u32 cip = ntohl((u32)client_ip);
		log_msg(LOG_INFO, "try to search %u.%u.%u.%u in GEO DB", ((u8 *)(&cip))[3],
						((u8 *)(&cip))[2],((u8 *)(&cip))[1], ((u8 *)(&cip))[0]);
		ret = (typeof(ret))geo_radix32tree_find(q->geo_tree, cip);
		if (ret != (typeof(ret))GEO_RADIX_NO_VALUE) {
			log_msg(LOG_INFO, "===>found entry %u %s", ret->isp_idx, ret->isp_province);
		} else {
			log_msg(LOG_INFO, "===>Not found entry");
		}
	}
	return ret;
}




#endif
