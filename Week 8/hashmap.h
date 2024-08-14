#ifndef HASHING_HASHMAP_H
#define HASHING_HASHMAP_H

#include <stddef.h>
#include <stdbool.h>
#include "list.h"

typedef list_t element_t;
typedef bool (*eq_func_t)(key_type, key_type);
typedef size_t (*hash_func_t)(key_type, size_t);

typedef struct hashmap {
    size_t capacity, count;
    list_t * slots;
    eq_func_t eq_fun;
    hash_func_t hash_fun;
} hashmap_t;

unsigned int compute_index(const hashmap_t* map, key_type key);

bool map_insert(hashmap_t * map, key_type key, value_type value);
void map_remove(hashmap_t * map, key_type key);
kv_pair_t * map_lookup(const hashmap_t * map, key_type key);

void map_init(hashmap_t * array, size_t cap, eq_func_t compare_fun, hash_func_t hash_fun);
void map_destroy(hashmap_t * array);

void map_print(const hashmap_t * array);

bool map_rehash(hashmap_t * original);

#endif //HASHING_HASHMAP_H
