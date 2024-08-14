#ifndef HASHING_LIST_H
#define HASHING_LIST_H

#include <stddef.h>

typedef const char* key_type;
typedef unsigned int value_type;

typedef struct kv_pair {
    key_type key;
    value_type value;
} kv_pair_t;

typedef struct node {
    kv_pair_t * kv_pair;
    struct node * next;
} node_t;

typedef struct list {
    node_t * head;
} list_t;

kv_pair_t* make_pair(key_type key, value_type value);
void destroy_pair(kv_pair_t * pair);

/// Allocates memory for a node_t, and initializes the node, setting its value
/// \param ppnode The memory address, passed by pointer, at which the address of the allocated memory is stored
/// \param value The value to be stored in the node_t structure
void node_init(node_t ** ppnode, kv_pair_t *pair);

/// Deallocates memory of a node_t, and sets the address to NULL
/// \param ppnode The address, passed by pointer, of the node_t structure
void node_destroy(node_t ** ppnode);

void list_init(list_t * plist);

void list_destroy(list_t * plist);

void list_prepend(list_t *plist, kv_pair_t* pair);

void list_remove(list_t *plist, node_t * p_node);

size_t list_length(const list_t *plist);

void node_list_print(const node_t * first);

void node_prepend(node_t ** pbefore, node_t *newbefore);

#endif //HASHING_LIST_H
