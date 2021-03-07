#ifndef DNSX_CORE_H
#define DNSX_CORE_H
#include "dnsx_list.h"
#include "query.h"
#include "namedb.h"

#define DNSX_GSLB_SKIP (-1)
typedef struct svc_ipv4_hash_item_type {
	struct list_head link;
	struct list_head child_rrs;
	u32 ipaddr;
	u16 isp_idx:5;
	u16 unused:11;
	u8  isp_province[2];
} svc_ipv4_hash_item_t;


int dnsx_get_best_rr_from_rrset(query_type *q ,rrset_type *rrset);
geo_radix_node_rr_t *dnsx_search_ip_from_geodb(struct query *q);
inline void dnsx_attach_rr_to_cache(svc_ipv4_hash_item_t *hash_item, rr_type *rr);
inline void dnsx_dettach_rr_from_cache(rr_type *rr);
#endif
