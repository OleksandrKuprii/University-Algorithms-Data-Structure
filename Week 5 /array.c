#include "array.h"
#include <stdlib.h>
#include <stdio.h>

void array_init(array_t *array, size_t cap) {
    array->data = (int*) malloc(sizeof(int) * cap);
    array->capacity = array->data == NULL ? 0 : cap;
    array->count = 0;
}

void array_destroy(array_t *array) {
    free(array->data);
    array->data = NULL;
}

void array_fill(array_t *array, size_t count) {
    if (count > array->capacity) {
        int * ptr = (int*) realloc(array->data, count * sizeof(int));
        if (ptr != NULL) {
            array->data = ptr;
            array->capacity = count;
        }
    }

    if (count > array->capacity) count = array->capacity;
    for (size_t i = 0; i < count; i++) {
        array->data[i] = rand() % (4 * count) - count;
    }
    array->count = count;
}

void array_print(const array_t *array) {
    printf("array contents: [");
    if (array->count > 0) {
        printf("%d", array->data[0]);
        for (size_t i = 1; i < array->count; i++) printf(", %d", array->data[i]);
    }
    printf("]\n");
}
