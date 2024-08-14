//
// Created by Dawid Zalewski on 05/12/2020.
//
#include "Counter.h"

#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

static const int DEFAULT_CAPACITY = 64;
static const int GROWTH_FACTOR = 2; // for resizing counter_t's capacity

static bool _insertAt(counter_t* counter, const size_t index, const char* key, unsigned long value);
static bool _ensureCapacity(counter_t* counter, size_t minimumCapacity);

pair_t* initPair(pair_t* pair, const char* key, unsigned long value){

    size_t length = key == NULL? 0 : strlen(key);

    if (length){
        *pair = (pair_t){.key = malloc(length + 1),
                       .value = value};
        if (pair->key) {
            memcpy((char*) pair->key, key, length + 1); // memcpy because length is already computed
        }
        else{
            pair->value = 0;
        }
    }
    else{
        *pair = (pair_t){.key = NULL,
                       .value = 0};
    }
    return pair;
}

pair_t makePair(const char* key, unsigned long value){
    pair_t pair;
    initPair(&pair, key, value);
    return pair;
}

void destroyPair(pair_t* pair){
    free((char *)pair->key);
    initPair(pair, NULL, 0);
}

counter_t* initCounter(counter_t* counter, int capacity){
    if (capacity){
        *counter = (counter_t) {
            .data = malloc(capacity * sizeof(pair_t)),
            .size = 0,
            .capacity = capacity
        };
        if (!counter->data)
            counter->capacity = 0;
    }
    else{
        *counter = (counter_t){
            .data = NULL,
            .size = 0,
            .capacity = 0
        };
    }
    return counter;
}


counter_t makeCounter(){
    counter_t counter;
    initCounter(&counter, DEFAULT_CAPACITY);
    return counter;
}

void destroyCounter(counter_t* counter){
    for (size_t i = 0; i < counter->size; ++i){
        destroyPair(&counter->data[i]);
    }
    free(counter->data);
    initCounter(counter, 0);
}


// return the index of the key if found (or index of insertion)
key_index_t indexOf(const counter_t* counter, const char* key){
    // a simple binary search
    size_t lo = 0, hi = counter->size;
    while (lo < hi){
        size_t mid = lo + (hi - lo) / 2;

        int cmp = strcmp(counter->data[mid].key, key);

        if (cmp < 0){
            lo = mid + 1;
        }
        else if (cmp > 0){
            hi = mid;
        }
        else{
            return (key_index_t) {mid, true};
        }
    }
    // key not found - `lo` is the index of insertion that maintains the ordered property
    return (key_index_t) {lo, false};
}


bool insert(counter_t* counter, const char* key, unsigned long value){
    key_index_t index = indexOf(counter, key);
    if (index.found){
        // update the value if an item with this key already exists
        counter->data[index.index].value = value;
        return true;
    }
    else {
        // an item with this key doesn't exists yet
        // insert a new pair_t at given index
        return _insertAt(counter, index.index, key, value);
    }
}

unsigned long getOrDefault(const counter_t* counter, const char* key, unsigned long defaultValue){
    key_index_t index = indexOf(counter, key);
    if (index.found){
        return counter->data[index.index].value;
    }
    return defaultValue;
}

bool contains(const counter_t* counter, const char* key){
    return indexOf(counter, key).found;
}

unsigned long increment(counter_t* counter, const char* key){
    // TODO: implement the increment function as described in Activity 8
    // TIP: you can use the existing functions to do it
    //      or implement an own version (that's potentially a bit faster)
    (void)counter;// prevents unused-parameter error
    (void)key;// prevents unused-parameter error
    return 0;
}


// Internal function, called to resize a counter_t if needed
bool _ensureCapacity(counter_t* counter, const size_t minimumCapacity){
    size_t new_capacity = counter->capacity;
    while (minimumCapacity > new_capacity){
        new_capacity = new_capacity * GROWTH_FACTOR + 1;
    }

    if (new_capacity > counter->capacity){
        pair_t *ptr = realloc(counter->data, new_capacity * sizeof(pair_t));
        if (ptr != NULL) {
            counter->data = ptr;
            counter->capacity = new_capacity;
            return true;
        }
    }
    return false;
}

// Internal function for inserting a key-value at index
// Returns: true on success, false otherwise
static bool _insertAt(counter_t* counter, const size_t index, const char* key, unsigned long value){
    (void)index;// prevents unused-parameter error
    (void)key;// prevents unused-parameter error
    (void)value;// prevents unused-parameter error
    if (_ensureCapacity(counter, counter->size + 1)) {
        pair_t new_pair = makePair(key, value);
        memcpy((void *) counter->data[index+1], counter->data[index], sizeof(pair_t) * counter->size-index);
        counter->data[index] = new_pair;
        counter->size++;
        return true;
    }
    return false;
}
