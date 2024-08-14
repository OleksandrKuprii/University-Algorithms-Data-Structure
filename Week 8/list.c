#include "list.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

kv_pair_t *make_pair(key_type key, value_type value) {
    kv_pair_t * ptr = (kv_pair_t*) malloc(sizeof(kv_pair_t));
    if (ptr != NULL) {
        ptr->key = malloc(strlen(key) + 1);
        strcpy((char*) ptr->key, key);
        ptr->value = value;
    }
    return ptr;
}

void destroy_pair(kv_pair_t * pair) {
    if (pair != NULL) {
        free((char*) pair->key);
    }
    free(pair);
}

void node_init(node_t **ppnode, kv_pair_t *pair) {
    node_t * ptr = malloc(sizeof(node_t));
    if (ptr != NULL) {
        ptr->kv_pair = pair;
        ptr->next = NULL;
    }
    *ppnode = ptr;
}

void node_destroy(node_t **ppnode) {
    if (*ppnode != NULL) {
        destroy_pair((*ppnode)->kv_pair);
    }
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
        node_destroy(&ptr);
        ptr = next;
    }
    plist->head = NULL;
}

void list_prepend(list_t *plist, kv_pair_t *pair) {
    node_t * pnode;
    node_init(&pnode, pair);
    node_prepend(&plist->head, pnode);
}

void list_remove(list_t *plist, node_t *p_node) {
    if (plist->head == NULL) return;
    node_t **ptr = &plist->head;
    if (*ptr == p_node) {
        *ptr = p_node->next;
    }
    else {
        while ((*ptr)->next != NULL && (*ptr)->next != p_node) ptr = &((*ptr)->next);
        if ((*ptr)->next == p_node) {
            *ptr = p_node->next;
            free(p_node);
        }
    }
}

size_t list_length(const list_t *plist) {
    size_t len = 0;
    for (const node_t * ptr = plist->head; ptr != NULL; ptr = ptr->next) len++;
    return len;
}

void node_list_print(const node_t *first) {
    printf("nodes -> [");
    if (first != NULL) {
        printf("%s: %u", first->kv_pair->key, first->kv_pair->value);
        first = first->next;
        while (first != NULL) {
            printf(", %s: %u", first->kv_pair->key, first->kv_pair->value);
            first = first->next;
        }
    }
    printf("]\n");
}

void node_prepend(node_t **pbefore, node_t *newbefore) {
    newbefore->next = *pbefore;
    *pbefore = newbefore;
}

