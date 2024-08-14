#include <stdio.h>
#include <stdlib.h>

typedef struct array {
    size_t capacity;
    size_t count;
    float *data;
} array_t;

array_t* array_init(array_t *p_array, size_t capacity) { // version 3
    if (p_array != NULL) {
        if (capacity != 0) {
            p_array->data = malloc(sizeof(float[capacity]));
            p_array->count = 0;
            p_array->capacity = p_array->data != NULL ? capacity : 0;
        } else {
            p_array->data = NULL;
            p_array->count = 0;
            p_array->capacity = 0;
        }
    }
    return p_array;
}

array_t* array_create(size_t capacity){
    array_t *ptr = (array_t *) malloc(sizeof(array_t));
    array_init(ptr, capacity);
    return ptr;
}

void array_destroy(array_t *p_array) {
    if (p_array != NULL) {
        free(p_array->data);
        array_init(p_array, 0);
    }
}

void array_reserve(array_t *p_array, size_t min_capacity) {
    size_t capacity = p_array->capacity;
    while (capacity < min_capacity) {
        capacity = (size_t) (((double) capacity + 1) * 1.6);
    }

    p_array->capacity = capacity;
    p_array->data = realloc(p_array->data, sizeof (array_t) * capacity);
}

void array_append(array_t * p_array, float value) {
    if (p_array->count == p_array->capacity) {
        array_reserve(p_array, p_array->count + 1);
    }

    p_array->data[p_array->count] = value;
    p_array->count++;
}

void array_insert(array_t * p_array, int index, float value) {
    if (p_array->count == p_array->capacity) {
        array_reserve(p_array, p_array->count + 1);
    }

    for (size_t i = p_array->count - 1; i > index - 1; i--) {
        p_array->data[i + 1] = p_array->data[i];
    }

    p_array->data[index] = value;
    p_array->count++;
}

void array_remove(array_t * p_array, int index) {
    for (size_t i = index; i < p_array->count; i++) {
        p_array->data[i] = p_array->data[i + 1];
    }

    p_array->count--;
}

int array_find(array_t * p_array, float value) {
    for (int i = 0; i < p_array->count; i++) {
        if (p_array->data[i] == value) {
            return i;
        }
    }

    return -1;
}

void input_grades(array_t * grades) {
    if (grades->count == grades->capacity) {
        array_reserve(grades, grades->count + 1);
    }

    for (int i = 0; i <= grades->capacity; i++) {
        printf("Enter grade of a student #%d\n", i);
        scanf("%f", &grades->data[i]);
        grades->count++;
    }
}

float average(const array_t * grades) {
    float gradesSum = 0;

    for (int i = 0; i <= grades->capacity; i++) {
        gradesSum += grades->data[i];
    }

    return gradesSum / (float) grades->capacity;
}

int num_passed(const array_t * grades) {
    int passedNum = 0;
    for (int i = 0; i <= grades->capacity; i++) {
        if(grades->data[i] >= 5.5) {
            passedNum++;
        }
    }
    return passedNum;
}

int main(void) {
    array_t *array = (array_t *) malloc(sizeof(array_t));
    array_init(array, 10);

    for (int i = 0; i < 20; i++) {
        array_append(array, (float) i);
//        printf("%f ", array->data[i]);
    }

    array_insert(array, 4, (float) 40.7);

    for (int i = 0; i < 26; i++) {
        printf("%d %f\n", i, array->data[i]);
    }

    // .... do some work ...
    // finally, clean up

    array_destroy(array);
    free(array);
}