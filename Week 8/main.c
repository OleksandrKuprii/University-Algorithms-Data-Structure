#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include <string.h>
#include "hashmap.h"
#include "list.h"

void process_line(char* line, hashmap_t * map) {
    const char* sep = "\t ()[]_,.;:?!/\\\"\n'";
    char* token = strtok(line, sep);
    while (token) {
        if (strlen(token)) {
            // TODO: Acitivity 11 - update the frequency of the word contained in 'token'
            // - use the map_lookup and the map_insert functions
        }
        token = strtok(NULL, sep);
    }
}

void process_file(const char* fileName, hashmap_t * map) {
    FILE* fp = fopen(fileName, "r");
    if (fp) {
        char buffer[1024];
        while (fgets(buffer, sizeof(buffer), fp)) {
            process_line(buffer, map);
        }
    }
}

bool compare(const char* s1, const char* s2) {
    return strcmp(s1, s2) == 0;
}

size_t fnv_hash(const char* key) {
    const size_t FNV_PRIME = 0x00000100000001B3;
    const size_t FNV_OFFSET_BASIS = 0xcbf29ce484222325;

    size_t h = FNV_OFFSET_BASIS;

    for (unsigned long i = 0; i < strlen(key); i++) {
        h ^= key[i];
        h *= FNV_PRIME;
    }

    return h;
}

// returns the modulo index of a string key based on its FNV-1a hash
size_t hash_index_str(const char* key, size_t size) {
    size_t h = fnv_hash(key);
    return h % size;
}

size_t simple_hash(const char* key, size_t size) {
    return strlen(key) % size;
}

int main(void) {
    hashmap_t map;
    map_init(&map, 7, compare, simple_hash);
    list_prepend(&map.slots[5], make_pair("Alice", 42));
    list_prepend(&map.slots[3], make_pair("Bob", 84));
    list_prepend(&map.slots[5], make_pair("Bob Dobalina", 126));
    list_prepend(&map.slots[5], make_pair("Cindy", 6));
    kv_pair_t * p1 = map_lookup(&map, "Joe");
    kv_pair_t * p2 = map_lookup(&map, "Alice");
    kv_pair_t * p3 = map_lookup(&map, "Bob");
    kv_pair_t * p4 = map_lookup(&map, "Bob Dobalina");
    kv_pair_t * p5 = map_lookup(&map, "Cindy");
    assert(p1 == NULL);
    assert(p2 != NULL && p3 != NULL && p4 != NULL && p5 != NULL);
    assert(strcmp(p2->key, "Alice") == 0);
    assert(p2->value == 42);
    assert(strcmp(p3->key, "Bob") == 0);
    assert(p3->value == 84);
    assert(strcmp(p4->key, "Bob Dobalina") == 0);
    assert(p4->value == 126);
    assert(strcmp(p5->key, "Cindy") == 0);
    assert(p5->value == 6);
}
