//
// Created by Dawid Zalewski on 05/12/2020.
//

#ifndef WORDS_COUNTING_COUNTER_H
#define WORDS_COUNTING_COUNTER_H

#include <stdbool.h>
#include <stddef.h>

// A key-count pair
typedef struct pair {
    const char* key;
    unsigned long value;
} pair_t;

// A counter (map of string->int)
typedef struct counter {
    pair_t* data;
    size_t size;		// number of items in this set
    size_t capacity;   // size of the `data` array
} counter_t;

// Used for searching for a key
typedef struct key_index {
    size_t index;      // index of the pair_t with the key or insertion index to maintain sorted property
    bool found;    // key was found
} key_index_t;

// Initializes an existing pair by copying the key.
// `key` can be NULL
extern pair_t* initPair(pair_t* pair, const char* key, unsigned long value);

// Creates a new pair_t, key is always copied
extern pair_t makePair(const char* key, unsigned long value);

// Destroys a pair_t (frees key)
extern void destroyPair(pair_t* pair);

// Creates a counter_t with default capacity
extern counter_t makeCounter();

// Initializes a counter with a capacity
extern counter_t* initCounter(counter_t* counter, int capacity);

// Destroys a counter_t and its content freeing the memory
extern void destroyCounter(counter_t* counter);

// Returns the index of the key if found (or index of insertion if key not found)
extern key_index_t indexOf(const counter_t* counter, const char* key);

// Inserts a new key-value pair or updates and existing one
// Returns: true if inserted, false if updated
extern bool insert(counter_t *counter, const char* key, const unsigned long value);

// Gets the value associated with a key (or `defaultValue` if key doesn't exist)
extern unsigned long getOrDefault(const counter_t* counter, const char* key, const unsigned long defaultValue);

// Checks if a counter_t contains a key
extern bool contains(const counter_t* counter, const char* key);

// Increments a value associated with a key (or inserts with a count of 1)
extern unsigned long increment(counter_t* counter, const char* key);

#endif //WORDS_COUNTING_COUNTER_H
