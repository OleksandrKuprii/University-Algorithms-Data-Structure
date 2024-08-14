#include "hashmap.h"
#include <stdlib.h>
#include <stdio.h>

bool map_insert(hashmap_t *map, key_type key, value_type value) {
    (void) map;
    (void) key;
    (void) value;
    // TODO: Activity 10 - if the key is not in the hashmap, add the
    //       key-value pair.
    //       otherwise, update the current value with the given value
    // steps:
    //   - compute index of the slot at which the key is stored
    //   - search the linked list for the key
    //   - update the value if the key was found, or
    //   - prepend a new pair to the list if it wasn't found (see the list_prepend function)
    //   - increment the count of pairs in the map (only if a new pair was added)
    //   - return true if a new pair was added, and false otherwise
    return true;
}

void map_remove(hashmap_t *map, key_type key) {
    (void) key;
    (void) map;
    // TODO: Activity 10 - remove the key-value pair from the hashmap if it is present
    // steps:
    //   - compute index of the slot at which the key is stored
    //   - search the linked list for the key
    //   - if found, remove the corresponding node from the list (see the list_remove function)
    //   - decrement the count of pairs in the map if something was removed
}

kv_pair_t *map_lookup(const hashmap_t *map, key_type key) {
    (void) key;
    (void) map;
    // TODO: Activity 9 - return the key-value pair by pointer if it is present
    //       otherwise, return NULL
    // steps:
    //   - compute index of the slot at which the key is stored
    //   - search the linked list for the key
    //   - if found, return the key-value pair, otherwise return NULL

//    int hash = map->hash_fun(key);
    return NULL;
}

void map_init(hashmap_t *array, size_t cap, eq_func_t compare_fun, hash_func_t hash_fun) {
    array->slots = (list_t*) malloc(sizeof(list_t) * cap);
    array->capacity = array->slots == NULL ? 0 : cap;
    array->count = 0;
    array->eq_fun = compare_fun;
    array->hash_fun = hash_fun;
    for (size_t i = 0; i < array->capacity; i++) list_init(&array->slots[i]);
}

void map_destroy(hashmap_t *array) {
    for (size_t i = 0; i < array->capacity; i++) list_destroy(&array->slots[i]);
    free(array->slots);
    array->slots = NULL;
}

void map_print(const hashmap_t *array) {
    printf("hashmap contents: %u pairs", (unsigned int) array->count);
    if (array->count > 0) {
        printf(":\n");
        for (size_t i = 0; i < array->capacity; i++) {
            printf("[%03u]: ", (unsigned int) i);
            node_list_print(array->slots[i].head);
        }
    }
    else
        printf("\n");
}

bool map_rehash(hashmap_t *original) {
    // if no need to rehash, then do nothing
    if (original->count * 10 < original->capacity * 7) return false;

    // set new capacity so that load factor will become 0.5
    size_t new_capacity = original->count * 2;

    // initialize new dynamic array for storing new slots
    list_t * new_slots = malloc(sizeof(list_t) * new_capacity);
    if (new_slots == NULL) return false;

    // TODO: Activity 14 - implement rehashing


    // Deallocate now-empty array of slots
    free(original->slots);

    // Update hashmap to use new slots and new capacity
    original->slots = new_slots;
    original->capacity = new_capacity;

    return true;
}

