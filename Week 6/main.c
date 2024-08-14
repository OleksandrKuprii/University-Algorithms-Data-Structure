#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <assert.h>
#include <string.h>

typedef struct person {
    const char* name;
    int year_of_birth;
} person_t;

typedef struct set {
    size_t capacity;
    size_t size;
    double * data;
} set_t;

bool equals_dbl(double a, double b) {
    return fabs(a - b) < 0.00001;
}

bool equals_prs(const person_t * obj1, const person_t * obj2) {
    return strcmp(obj1->name, obj2->name) == 0 && obj1->year_of_birth == obj2->year_of_birth;
}

/// Creates and initializes a set
/// \param init_cap The initial capacity for the items in the set
/// \return
set_t * make_set(size_t init_cap) {
    set_t * set = (set_t*) malloc(sizeof(set_t));
    if (set != NULL) {
        set->data = (double*) malloc(sizeof(double) * init_cap);
        set->size = 0;
        set->capacity = set->data != NULL ? init_cap : 0;
    }
    return set;
}

/// Ensures that the set can hold at least one more value.
/// Reallocates memory for the set's items if necessary
/// \param set
void ensure_cap(set_t * set) { // version 1
    if (set->size < set->capacity) return;
    size_t cap = (set->capacity + 1) * 3 / 2;
    double *ptr = realloc(set->data, cap * sizeof(double));
    if (ptr != NULL) {
        set->data = ptr;
        set->capacity = cap;
    }
}


/// Returns the index at which the value is located, if it is a member of the set,
/// or the index at which it must be inserted to maintain sorted order, if it is not
/// \param set The (sorted) set to search
/// \param value The value to find
/// \return if value is in the set, its index, otherwise the index at which it should be inserted
size_t index_of(const set_t * set, double value) {
    size_t lo = 0, hi = set->size;
    while (lo < hi) {
        size_t mid = lo + (hi - lo) / 2;
        if (equals_dbl(set->data[mid], value)) {
            return mid;
        }
        else if (set->data[mid] < value) {
            lo = mid + 1;
        }
        else {
            hi = mid;
        }
    }
    return lo;
}

/// Deallocates a set
/// \param set
void destroy_set(set_t * set){
    free(set->data);
    free(set);
}

bool set_contains(const set_t * set, double value) {
    size_t index = index_of(set, value);
    if (index == set->size){
        return false;
    }
    return equals_dbl(set->data[index], value);
}

void set_add(set_t * set, double value) {
//    if (set_contains(set, value))
//        return;
//
//    size_t index = index_of(set, value);
//    ensure_cap(set);
//
//    for (size_t i = set->size + 1; i > index; i--) {
//        set->data[i] = set->data[i-1];
//    }
//
//    set->data[index] = value;
//    set->size++;
    if (!set_contains(set, value)) {
        ensure_cap(set);
        set->data[set->size] = value;
        set->size++;
    }
}

void set_remove(set_t * set, double value) {
    bool shift = false;

    for (int i = 0; i < set->size; i++) {
        if (!shift && equals_dbl(value, set->data[i])) {
            shift = true;
            set->size--;
            continue;
        }

        if (shift) {
            set->data[i - 1] = set->data[i];
        }
    }
}

/// Uses binary search to find a value in a set
/// \param set The (sorted) set to search
/// \param value The value to find
/// \return true if the value was found, false otherwise
bool set_contains_binsearch(const set_t * set, double value) {
    size_t lo = 0, hi = set->size;
    while (lo < hi) {
        size_t mid = lo + (hi - lo) / 2;
        if (equals_dbl(set->data[mid], value)) {
            return true;
        } else if (set->data[mid] < value) {
            lo = mid + 1;
        } else {
            hi = mid;
        }
    }
    return false;
}

//#define _TEST_SET_
void test_set() {
#ifndef _TEST_SET_
    fprintf(stderr, "Not testing the set - uncomment the line that contains \"#define _TEST_SET_\"\n");
#else
    set_t * set = make_set(0);
    set_add(set, 41.0 + 0.5 + 0.2 + 0.2 + 0.1);
    set_remove(set, 43.0 - 0.5 - 0.2 - 0.2 - 0.1);
    assert(0 == set->size);
    set_add(set, 1.0); assert(1 == set->size);
    set_remove(set, 1.0); assert(0 == set->size);
    set_add(set, 1.0); assert(1 == set->size);
    set_add(set, 4.0); assert(2 == set->size);
    set_add(set, 4.0); assert(2 == set->size);
    set_add(set, 2.0); assert(3 == set->size);
    set_add(set, 3.0); assert(4 == set->size);

    assert(set_contains(set, 1.0));
    assert(set_contains(set, 2.0));
    assert(set_contains(set, 3.0));
    assert(set_contains(set, 4.0));

    set_remove(set, 3.14);
    assert(4 == set->size);

    set_remove(set, 3.0);
    assert(3 == set->size);
    assert(!set_contains(set, 3.0));

    set_remove(set, 2.0);
    assert(2 == set->size);
    assert(!set_contains(set, 2.0));

    destroy_set(set);
#endif
}

int main(void) {
    set_t * set = make_set(0);
    set_add(set, 41.0 + 0.5 + 0.2 + 0.2 + 0.1);
    set_remove(set, 43.0 - 0.5 - 0.2 - 0.2 - 0.1);
    assert(0 == set->size);
    set_add(set, 1.0); assert(1 == set->size);
    set_remove(set, 1.0); assert(0 == set->size);
    set_add(set, 1.0); assert(1 == set->size);
    set_add(set, 4.0); assert(2 == set->size);
    set_add(set, 4.0); assert(2 == set->size);
    set_add(set, 2.0); assert(3 == set->size);
    set_add(set, 3.0); assert(4 == set->size);

    assert(set_contains(set, 1.0));
    assert(set_contains(set, 2.0));
    assert(set_contains(set, 3.0));
    assert(set_contains(set, 4.0));

    set_remove(set, 3.14); assert(4 == set->size);

    set_remove(set, 3.0); assert(3 == set->size);
    assert(!set_contains(set, 3.0));

    set_remove(set, 2.0); assert(2 == set->size);
    assert(!set_contains(set, 2.0));

    destroy_set(set);
}
