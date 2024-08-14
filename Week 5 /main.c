#include <stdio.h>
#include <stdlib.h>
#include "array.h"
#include "list.h"

/// Part I - Selection sort
void swap(int * x, int * y) {
    int temp = *x;
    *x = *y;
    *y = temp;
}

/// Finds the minimum value in an array of integers
/// \param values
/// \param count
/// \return
int * find_min(int * values, size_t count) {
    if (count == 0) {
        return NULL;
    }

    int * min = values;
    for (int i = 1; i < count; i++) {
        if (values[i] < *min) {
            min = values + i;
        }
    }
    return min;
}

/// Sorts an array, using selection sort
/// \param array The array to be sorted
void array_sort(array_t * array) {
    for (int i = 0; i < array->count - 1; i++) {
        swap(array->data + i, find_min(array->data + i, array->count - i));
    }
}

/// Part II - Merge sort

/// splits a linked list in two halves. The list must not be empty
/// \param phead the first node of the list, passed by pointer.
/// \return the first node of the second half of the list, returned by pointer
node_t * split(node_t * phead) {
    node_t * fast = phead->next;
    while (fast != NULL && fast->next != NULL) {
        fast = fast->next;
        fast = fast->next;
        phead = phead->next;
    }

    node_t * next = phead->next;
    phead->next = NULL;

    return next;
}

int count = 0;

/// Merges two lists
/// \param a the first node of the first list, passed by pointer
/// \param b the first node of the second list, passed by pointer
/// \return the first node of the merged list, returned by pointer
node_t * merge(node_t * a, node_t * b) {
    node_t temp = {.next = NULL};
    node_t * result = &temp;
    while (a != NULL && b != NULL) {
        if (a->value < b->value) {
            result->next = a;
            a = a->next;
        }
        else {
            result->next = b;
            b = b->next;
        }
        count++;
        result = result->next;
    }

    while (a != NULL) {
        result->next = a;
        a = a->next;
        result = result->next;
    }
    while (b != NULL) {
        result->next = b;
        b = b->next;
        result = result->next;
    }

    return temp.next;
}

/// sorts an entire linked list using merge sort
/// \param first the first node in the unsorted linked list
/// \return the first node in the sorted linked list
node_t * merge_sort(node_t * first) {
    if (first->next == NULL) {
        return first; // only a single node, so already sorted
    }
    else {
        node_t * next = split(first);
        return merge(merge_sort(first), merge_sort(next));
    }
}

/// sorts a linked list, using merge sort
void list_sort(list_t * plist) {
    if (plist->head != NULL) plist->head = merge_sort(plist->head);
}

int main() {
    list_t list;
    list_init(&list);

    int c = 300;

    for (int i = 1; i < c + 1; i++) {
        list_append(&list, i);
    }

    list_sort(&list);
    list_destroy(&list);
    printf("%d\n", count);

    count = 0;

    for (int i = c; i > 0; i--) {
        list_append(&list, i);
    }

    list_sort(&list);
    list_destroy(&list);
    printf("%d", count);

//    list_append_multi(&list, (int[]) {8, 3, 7, 2, 1, 9, 3, 4}, 8);
//    node_list_print(list.head); // must print: [1, 2, 3, 3, 4, 7, 8, 9]
//    list_destroy(&list);
//    list_append_multi(&list, (int[]) {3, 7, 2, 1, 0}, 5);
//    list_sort(&list);
//    node_list_print(list.head); // must print: [0, 1, 2, 3, 7]
}
