# Week 5 - Sorting

## Team

Team name: Olrksandr
Date:

Members
Oleksandr Kuprii

| Role                                                                                                                                                                          | Name |
|-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|------|
| **Facilitator** keeps track of time, assigns tasks and makes sure all the group members are heard and that decisions are agreed upon.                                             | Oleksandr     |
| **Spokesperson** communicates group’s questions and problems to the teacher and talks to other teams; presents the group’s findings.                                              | Oleksandr     |
| **Reflector** observes and assesses the interactions and performance among team members. Provides positive feedback and intervenes with suggestions to improve groups’ processes. | Oleksandr     |
| **Recorder** guides consensus building in the group by recording answers to questions. Collects important information and data.                                                   | Oleksandr     |

## Activities
Make sure to have the activities signed off regularly to ensure progress is tracked.

Download the provided project and open it in CLion.

### Activity 1: Benefits of sorted data

Finding a value in the unsorted array has O(n) time complexity, whereas finding a value in the sorted array - O(log(n)).
The algorithm to find a value in the sorted array is called **binary search**.

### Activity 2: Find the smallest element

```c
int* find_min(int * values, size_t count) {
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
```

### Activity 3: Implement selection sort

```c
void swap(float * a, float * b) {
    if (a == b)
        return;
    
    *a += *b;
    *b = *a - *b;
    *a = *a - *b;
}

void array_sort(array_t * array) {
    for (int i = 0; i < array->count - 1; i++) {
        swap(array->data + i, find_min(array->data + i, array->count - i));
    }
}
```

### Activity 4: Selection sort: comparisons

| List length | Comparisons |
|-------------|-------------|
| 5           | 10          |
| 10          | 45          |
| 15          | 105         |
| 20          | 190         |
| 30          | 435         |
| 60          | 1770        |
| 90          | 4005        |
| 150         | 11175       |
| 300         | 44850       |

### Activity 5: Merge sort - step by step

| Stage     | Subsequences                                                         |
|-----------|----------------------------------------------------------------------|
| 13 lists: | [9], [0], [31], [5], [2], [8], [15], [13], [6], [4], [7], [11], [19] |
| 7 lists:  | [0, 9], [5, 31], [2, 8], [13, 15], [4, 6], [7, 11], [19]             |
| 4 lists:  | [0, 5, 9, 31], [2, 8, 13, 15], [4, 6, 7, 11], [19]                   |
| 2 lists:  | [0, 2, 5, 8, 9, 13, 15, 31], [4, 6, 7, 11, 19]                       |
| 1 list:   | [0, 2, 4, 5, 6, 7, 8, 9, 11, 13, 15, 19, 31]                         |

### Activity 6: Splitting a linked list in two halves

```c
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
```

### Activity 7: Merging two linked lists

```c
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
```

### Activity 8: Implement merge sort

```c
node_t * merge_sort(node_t * first) {
    if (first->next == NULL) {
        return first; // only a single node, so already sorted
    }
    else {
        node_t * next = split(first);
        return merge(merge_sort(first), merge_sort(next));
    }
}
```

### Activity 9: Merge sort: comparisons

| List length |  Comparions |
|:-----------:|:-----------:|
|      5      |    5 - 7    |
|      10     |   15 - 19   |
|      15     |   28 - 31   |
|      20     |   40 - 48   |
|      30     |   71 - 77   |
|      60     |  172 - 184  |
|      90     |  275 - 317  |
|     150     |  515 - 579  |
|     300     | 1180 - 1308 |

### Activity 10: Compare merge sort and selection sort

| Algorithm | Time complexity |
| --------------------------------- | --------------- |
| Merge sort | 1/2 * n<sup>2</sup>               |
| Selection sort | 1/2 * n * logn                 |


## Looking back

### What we've learnt

Selection and merge sort.

### What were the surprises

How the number of comparisons fastly grows with the increasing of the array's size.

### What problems we've encountered

No problems.

### What was or still is unclear

Nothing.

### How did the group perform?

How was the collaboration? What were the reasons for hick-ups? What worked well? What can be improved next time?





> Written with [StackEdit](https://stackedit.io/).
