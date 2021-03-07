/*
 *
 * Copyright (c) 2015, Zuogui Xie. All rights reserved.
 *
 * See LICENSE for the license.
 *
 */

#include <geo_radix_tree.h>

extern  int nsd_pagesize;

static geo_radix_node_t *geo_radix_alloc(geo_radix_tree_t *tree);

geo_radix_tree_t *
geo_radix_tree_create(region_type *region, int preallocate)
{
    uint32_t           key, mask, inc;
    geo_radix_tree_t  *tree;

    tree = region_alloc(region, sizeof(geo_radix_tree_t));
    if (tree == NULL) {
        return NULL;
    }

    tree->region = region;
    tree->free = NULL;
    tree->start = NULL;
    tree->size = 0;

    tree->root = geo_radix_alloc(tree);
    if (tree->root == NULL) {
        return NULL;
    }

    tree->root->right = NULL;
    tree->root->left = NULL;
    tree->root->parent = NULL;
    tree->root->value = GEO_RADIX_NO_VALUE;

    if (preallocate == 0) {
        return tree;
    }

    /*
     * Preallocation of first nodes : 0, 1, 00, 01, 10, 11, 000, 001, etc.
     * increases TLB hits even if for first lookup iterations.
     * On 32-bit platforms the 7 preallocated bits takes continuous 4K,
     * 8 - 8K, 9 - 16K, etc.  On 64-bit platforms the 6 preallocated bits
     * takes continuous 4K, 7 - 8K, 8 - 16K, etc.  There is no sense to
     * to preallocate more than one page, because further preallocation
     * distributes the only bit per page.  Instead, a random insertion
     * may distribute several bits per page.
     *
     * Thus, by default we preallocate maximum
     *     6 bits on amd64 (64-bit platform and 4K pages)
     *     7 bits on i386 (32-bit platform and 4K pages)
     *     7 bits on sparc64 in 64-bit mode (8K pages)
     *     8 bits on sparc64 in 32-bit mode (8K pages)
     */

    if (preallocate == -1) {
        switch (nsd_pagesize / sizeof(geo_radix_node_t)) {

        /* amd64 */
        case 128:
            preallocate = 6;
            break;

        /* i386, sparc64 */
        case 256:
            preallocate = 7;
            break;

        /* sparc64 in 32-bit mode */
        default:
            preallocate = 8;
        }
    }

    mask = 0;
    inc = 0x80000000;

    while (preallocate--) {

        key = 0;
        mask >>= 1;
        mask |= 0x80000000;

        do {
            if (geo_radix32tree_insert(tree, key, mask, GEO_RADIX_NO_VALUE)
                != NSD_OK)
            {
                return NULL;
            }

            key += inc;

        } while (key);

        inc >>= 1;
    }

    return tree;
}


int
geo_radix32tree_insert(geo_radix_tree_t *tree, uint32_t key, uint32_t mask,
    uintptr_t value)
{
    uint32_t           bit;
    geo_radix_node_t  *node, *next;

    bit = 0x80000000;

    node = tree->root;
    next = tree->root;

    while (bit & mask) {
        if (key & bit) {
            next = node->right;

        } else {
            next = node->left;
        }

        if (next == NULL) {
            break;
        }

        bit >>= 1;
        node = next;
    }

    if (next) {
        if (node->value != GEO_RADIX_NO_VALUE) {
            return NSD_BUSY;
        }

        node->value = value;
        return NSD_OK;
    }

    while (bit & mask) {
        next = geo_radix_alloc(tree);
        if (next == NULL) {
            return NSD_ERROR;
        }

        next->right = NULL;
        next->left = NULL;
        next->parent = node;
        next->value = GEO_RADIX_NO_VALUE;

        if (key & bit) {
            node->right = next;

        } else {
            node->left = next;
        }

        bit >>= 1;
        node = next;
    }

    node->value = value;

    return NSD_OK;
}


int
geo_radix32tree_delete(geo_radix_tree_t *tree, uint32_t key, uint32_t mask)
{
    uint32_t           bit;
    geo_radix_node_t  *node;

    bit = 0x80000000;
    node = tree->root;

    while (node && (bit & mask)) {
        if (key & bit) {
            node = node->right;

        } else {
            node = node->left;
        }

        bit >>= 1;
    }

    if (node == NULL) {
        return NSD_ERROR;
    }

    if (node->right || node->left) {
        if (node->value != GEO_RADIX_NO_VALUE) {
            node->value = GEO_RADIX_NO_VALUE;
            return NSD_OK;
        }

        return NSD_ERROR;
    }

    for ( ;; ) {
        if (node->parent->right == node) {
            node->parent->right = NULL;

        } else {
            node->parent->left = NULL;
        }

        node->right = tree->free;
        tree->free = node;

        node = node->parent;

        if (node->right || node->left) {
            break;
        }

        if (node->value != GEO_RADIX_NO_VALUE) {
            break;
        }

        if (node->parent == NULL) {
            break;
        }
    }

    return NSD_OK;
}


uintptr_t
geo_radix32tree_find(geo_radix_tree_t *tree, uint32_t key)
{
    uint32_t           bit;
    uintptr_t          value;
    geo_radix_node_t  *node;

    bit = 0x80000000;
    value = GEO_RADIX_NO_VALUE;
    node = tree->root;

    while (node) {
        if (node->value != GEO_RADIX_NO_VALUE) {
            value = node->value;
        }

        if (key & bit) {
            node = node->right;

        } else {
            node = node->left;
        }

        bit >>= 1;
    }

    return value;
}


#if (GEO_HAVE_INET6)

int
geo_radix128tree_insert(geo_radix_tree_t *tree, u_char *key, u_char *mask,
    uintptr_t value)
{
    u_char             bit;
    geo_uint_t         i;
    geo_radix_node_t  *node, *next;

    i = 0;
    bit = 0x80;

    node = tree->root;
    next = tree->root;

    while (bit & mask[i]) {
        if (key[i] & bit) {
            next = node->right;

        } else {
            next = node->left;
        }

        if (next == NULL) {
            break;
        }

        bit >>= 1;
        node = next;

        if (bit == 0) {
            if (++i == 16) {
                break;
            }

            bit = 0x80;
        }
    }

    if (next) {
        if (node->value != GEO_RADIX_NO_VALUE) {
            return NSD_BUSY;
        }

        node->value = value;
        return NSD_OK;
    }

    while (bit & mask[i]) {
        next = geo_radix_alloc(tree);
        if (next == NULL) {
            return NSD_ERROR;
        }

        next->right = NULL;
        next->left = NULL;
        next->parent = node;
        next->value = GEO_RADIX_NO_VALUE;

        if (key[i] & bit) {
            node->right = next;

        } else {
            node->left = next;
        }

        bit >>= 1;
        node = next;

        if (bit == 0) {
            if (++i == 16) {
                break;
            }

            bit = 0x80;
        }
    }

    node->value = value;

    return NSD_OK;
}


int
geo_radix128tree_delete(geo_radix_tree_t *tree, u_char *key, u_char *mask)
{
    u_char             bit;
    geo_uint_t         i;
    geo_radix_node_t  *node;

    i = 0;
    bit = 0x80;
    node = tree->root;

    while (node && (bit & mask[i])) {
        if (key[i] & bit) {
            node = node->right;

        } else {
            node = node->left;
        }

        bit >>= 1;

        if (bit == 0) {
            if (++i == 16) {
                break;
            }

            bit = 0x80;
        }
    }

    if (node == NULL) {
        return NSD_ERROR;
    }

    if (node->right || node->left) {
        if (node->value != GEO_RADIX_NO_VALUE) {
            node->value = GEO_RADIX_NO_VALUE;
            return NSD_OK;
        }

        return NSD_ERROR;
    }

    for ( ;; ) {
        if (node->parent->right == node) {
            node->parent->right = NULL;

        } else {
            node->parent->left = NULL;
        }

        node->right = tree->free;
        tree->free = node;

        node = node->parent;

        if (node->right || node->left) {
            break;
        }

        if (node->value != GEO_RADIX_NO_VALUE) {
            break;
        }

        if (node->parent == NULL) {
            break;
        }
    }

    return NSD_OK;
}


uintptr_t
geo_radix128tree_find(geo_radix_tree_t *tree, u_char *key)
{
    u_char             bit;
    uintptr_t          value;
    geo_uint_t         i;
    geo_radix_node_t  *node;

    i = 0;
    bit = 0x80;
    value = GEO_RADIX_NO_VALUE;
    node = tree->root;

    while (node) {
        if (node->value != GEO_RADIX_NO_VALUE) {
            value = node->value;
        }

        if (key[i] & bit) {
            node = node->right;

        } else {
            node = node->left;
        }

        bit >>= 1;

        if (bit == 0) {
            i++;
            bit = 0x80;
        }
    }

    return value;
}

#endif


static geo_radix_node_t *
geo_radix_alloc(geo_radix_tree_t *tree)
{
    geo_radix_node_t  *p;

    if (tree->free) {
        p = tree->free;
        tree->free = tree->free->right;
        return p;
    }

    if (tree->size < sizeof(geo_radix_node_t)) {
        tree->start = region_alloc(tree->region, nsd_pagesize);
        if (tree->start == NULL) {
            return NULL;
        }

        tree->size = nsd_pagesize;
    }

    p = (geo_radix_node_t *) tree->start;
    tree->start += sizeof(geo_radix_node_t);
    tree->size -= sizeof(geo_radix_node_t);

    return p;
}
