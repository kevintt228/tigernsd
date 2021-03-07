
/*
 * Copyright (C) Igor Sysoev
 * Copyright (C) Nginx, Inc.
 */


#ifndef _GEO_RADIX_TREE_H_INCLUDED_
#define _GEO_RADIX_TREE_H_INCLUDED_

#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/tcp.h>        /* TCP_NODELAY, TCP_CORK */
#include <arpa/inet.h>
#include <netdb.h>
#include <sys/un.h>
#include <nsd_types.h>
#include <region-allocator.h>

#define GEO_RADIX_NO_VALUE   (uintptr_t) -1

typedef struct geo_radix_node_s  geo_radix_node_t;
typedef struct geo_radix_node_rr_s geo_radix_node_rr_t;

typedef struct {
	in_addr_t                 addr;
	in_addr_t                 mask;
} geo_in_cidr_t;

#if (GEO_HAVE_INET6)
typedef struct {
	struct in6_addr           addr;
	struct in6_addr           mask;
} geo_in6_cidr_t;

#endif

typedef struct {
	u32                family;
	union {
		geo_in_cidr_t         in;
#if (GEO_HAVE_INET6)
		geo_in6_cidr_t        in6;
#endif
	} u;
} geo_cidr_t;

/*
0100000000000000 0x4000 -> CHINA DEFAULT
0111111100000000 0x7F00 -> CHINA ISP DEFAULT
1000000000000000 0x8000 -> FOREIGN DEFAULT
1000000111110000 0x81F0 -> FOREIGN CONTINENT DEFAULT
1000000111111111 0x81FF -> FOREIGN COUNTRY DEFAULT
1100000000000000 0xC000 -> SPIDER DEFAULT
*/

struct geo_radix_node_rr_s {
	u16 isp_idx;
	u8 isp_province[3];
};

struct geo_radix_node_s {
    geo_radix_node_t  *right;
    geo_radix_node_t  *left;
    geo_radix_node_t  *parent;
    uintptr_t          value;
};


typedef struct {
    geo_radix_node_t  *root;
    region_type        *region;
    geo_radix_node_t  *free;
    char              *start;
    size_t             size;
} geo_radix_tree_t;


geo_radix_tree_t *geo_radix_tree_create(region_type *region,
    int preallocate);

int geo_radix32tree_insert(geo_radix_tree_t *tree,
    uint32_t key, uint32_t mask, uintptr_t value);
int geo_radix32tree_delete(geo_radix_tree_t *tree,
    uint32_t key, uint32_t mask);
uintptr_t geo_radix32tree_find(geo_radix_tree_t *tree, uint32_t key);

#if (GEO_HAVE_INET6)
int geo_radix128tree_insert(geo_radix_tree_t *tree,
    u_char *key, u_char *mask, uintptr_t value);
int geo_radix128tree_delete(geo_radix_tree_t *tree,
    u_char *key, u_char *mask);
uintptr_t geo_radix128tree_find(geo_radix_tree_t *tree, u_char *key);
#endif


#endif /* _GEO_RADIX_TREE_H_INCLUDED_ */
