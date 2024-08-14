#include "list.h"
#include <stdio.h>
#include <stdlib.h>

void node_init(node_t **ppnode, int value) {
    node_t * ptr = malloc(sizeof(node_t));
    if (ptr != NULL) {
        ptr->value = value;
        ptr->next = NULL;
    }
    *ppnode = ptr;
}

void node_destroy(node_t **ppnode) {
    free(*ppnode);
    *ppnode = NULL;
}

void list_init(list_t *plist) {
    plist->head = NULL;
}

void list_destroy(list_t *plist) {
    node_t * ptr = plist->head;
    while (ptr != NULL) {
        node_t * next = ptr->next;
        free(ptr);
        ptr = next;
    }
    plist->head = NULL;
}

void list_append(list_t *plist, int value) {
    node_t ** ptr = &plist->head;
    while (*ptr != NULL) {
        ptr = &(*ptr)->next;
    }
    node_init(ptr, value);
}

void list_append_multi(list_t *plist, int *values, size_t count) {
    if (count == 0) return;

    node_t ** ptr = &plist->head;
    while (*ptr != NULL) {
        ptr = &(*ptr)->next;
    }
    node_init(ptr, values[0]);
    for (size_t i = 1; i < count; i++) {
        ptr = &(*ptr)->next;
        node_init(ptr, values[i]);
    }
}

void list_append_random(list_t *plist, size_t count) {
    for (size_t i = 0; i < count; i++) {
        list_append(plist, rand() % (4 * count) - count);
    }
}

void node_list_print(const node_t *first) {
    printf("nodes -> [");
    if (first != NULL) {
        printf("%d", first->value);
        first = first->next;
        while (first != NULL) {
            printf(", %d", first->value);
            first = first->next;
        }
    }
    printf("]\n");
}

