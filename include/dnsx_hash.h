
#ifndef _HASH_H
#define _HASH_H

#include <dnsx_list.h>
#include <dnsx_atomic.h>

typedef int (*hash_hash_func_t)(const void *key);
typedef int (*hash_comp_func_t)(struct list_head *link, const void *key);
typedef void *(*hash_l2k_func_t)(struct list_head *link);
typedef int (*hash_foreach_func_t)(struct list_head *link, void *param);

typedef struct hash_ {
    int size;
    atomic_t num_data;
    struct list_head *lists;
    hash_hash_func_t hash_func;
    hash_comp_func_t comp_func;
    hash_l2k_func_t l2k_func;
} hash_t;


extern hash_t *hash_create(int hash_size,
                           hash_hash_func_t hash_func,
                           hash_comp_func_t comp_func,
                           hash_l2k_func_t l2k_func);
extern inline void hash_destroy(hash_t *hash);
extern inline int hash_count(hash_t *hash);
extern void hash_foreach(hash_t *hash, hash_foreach_func_t foreach, void *param);
extern inline void hash_insert(hash_t *hash, struct list_head *link);
extern inline void hash_remove(hash_t *hash, struct list_head *link);
extern void *hash_lookup(hash_t *hash, void *key);

#define dnsx_malloc(x) malloc(x)
#define dnsx_free(x) free(x)

#endif

