#ifndef SORTING_ARRAY_H
#define SORTING_ARRAY_H

#include <stddef.h>

typedef struct array {
    size_t capacity, count;
    int * data;
} array_t;

void array_init(array_t * array, size_t cap);
void array_destroy(array_t * array);

void array_fill(array_t * array, size_t count);
void array_print(const array_t * array);

#endif //SORTING_ARRAY_H
