#include <string.h>
#include <dnsx_hash.h>
#include <stdlib.h>

hash_t *hash_create(int hash_size,
                    hash_hash_func_t hash_func,
                    hash_comp_func_t comp_func,
                    hash_l2k_func_t l2k_func)
{
    hash_t *hash;
    int mem_size = sizeof(*hash) + sizeof(*hash->lists) * hash_size;
    int i;

    if ((hash = dnsx_malloc(mem_size)) == NULL) {
        return NULL;
    }

    memset(hash, 0, mem_size);
    hash->lists = (struct list_head *)(hash + 1);

    for (i = 0; i < hash_size; i ++) {
        INIT_LIST_HEAD(&hash->lists[i]);
    }

    hash->size = hash_size;
    atomic_set(&hash->num_data, 0);
    hash->hash_func = hash_func;
    hash->comp_func = comp_func;
    hash->l2k_func = l2k_func;
    return hash;
}

inline void hash_destroy(hash_t *hash)
{
    dnsx_free(hash);
}

inline int hash_count(hash_t *hash)
{
    return atomic_read(&hash->num_data);
}

void hash_foreach(hash_t *hash, hash_foreach_func_t foreach, void *param)
{
    struct list_head *ptr, *next;
    int i;

    for (i = 0; i < hash->size; i ++) {
        list_for_each_safe(ptr, next, &hash->lists[i]) {
            if (foreach(ptr, param)) {
                return;
            }
        }
    }
}

inline void hash_insert(hash_t *hash, struct list_head *link)
{
    int h = hash->hash_func(hash->l2k_func(link));
    list_add_rcu(link, &hash->lists[h]);
    atomic_inc(&hash->num_data);
}

inline void hash_remove(hash_t *hash, struct list_head *link)
{
    list_del_rcu(link);
    atomic_dec(&hash->num_data);
}

void *hash_lookup(hash_t *hash, void *key)
{
    struct list_head *ptr, *next;
    int h;

    if (hash_count(hash) == 0) {
        return NULL;
    }

    h = hash->hash_func(key);
    list_for_each_safe(ptr, next, &hash->lists[h]) {
        if (hash->comp_func(ptr, key) == 0) {
            return ptr;
        }
    }
    return NULL;
}

