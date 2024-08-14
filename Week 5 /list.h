#ifndef SORTING_LIST_H
#define SORTING_LIST_H

#include <stddef.h>

typedef struct node {
    int value;
    struct node * next;
} node_t;

typedef struct list {
    node_t * head;
} list_t;

/// Allocates memory for a node_t, and initializes the node, setting its value
/// \param ppnode The memory address, passed by pointer, at which the address of the allocated memory is stored
/// \param value The value to be stored in the node_t structure
void node_init(node_t ** ppnode, int value);

/// Deallocates memory of a node_t, and sets the address to NULL
/// \param ppnode The address, passed by pointer, of the node_t structure
void node_destroy(node_t ** ppnode);

void list_init(list_t * plist);

void list_destroy(list_t * plist);

void list_append(list_t * plist, int value);

void list_append_multi(list_t * plist, int * values, size_t count);

void list_append_random(list_t * plist, size_t count);

void node_list_print(const node_t * first);



#endif //SORTING_LIST_H
