# Week 6 - Sets

## Team

Team name: Oleksandr
Date:

Members
Oleksandr Kuprii

| Role                                                                                                                                                                          | Name |
|-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|------|
| **Facilitator** keeps track of time, assigns tasks and makes sure all the group members are heard and that decisions are agreed upon.                                             |  Oleksandr    |
| **Spokesperson** communicates group’s questions and problems to the teacher and talks to other teams; presents the group’s findings.                                              |  Oleksandr    |
| **Reflector** observes and assesses the interactions and performance among team members. Provides positive feedback and intervenes with suggestions to improve groups’ processes. |  Oleksandr    |
| **Recorder** guides consensus building in the group by recording answers to questions. Collects important information and data.                                                   | Oleksandr    |

## Activities
Make sure to have the activities signed off regularly to ensure progress is tracked.

Download the provided project and open it in CLion.

### Activity 1: Find out: set membership

1. Checking if the book is available in the store.
2. Cehcking who is the math teacher for the next quarter.
3. Checking if the train ticket is valid.
4. Checking if the person's phone number is in my contact list.
5. Finding the bike on the parking.

### Activity 2: Comparing floating point numbers

Floating point operations usually involve at least tiny rounding errors which are hard to predict. Therefore two floating point operations that should mathematically give the same result (like 4.7 * (1.0 / 3.14) vs. 4.7 / 3.14) may give different results.

```c
bool equals_dbl(double d1, double d2) {
    return fabs(d1 - d2) < 0.00001;
}
```

### Activity 3: Comparing compound data types

```c
bool equals_prs(const person_t * obj1, const person_t * obj2) {
    return strcmp(obj1->name, obj2->name) == 0 && obj1->year_of_birth == obj2->year_of_birth;
}
```

### Activity 4: Function prototypes

```c
void set_add(set_t * set, double value);
void set_remove(set_t * set, double value);
bool set_contains(const set_t * set, double value);
```

### Activity 5: Dynamic sizing

```c
void ensure_cap(set_t * set) { // version 1
    if (set->size < set->capacity) return;
    size_t cap = (set->capacity + 1) * 3 / 2;
    double *ptr = realloc(set->data, cap * sizeof(double));
    if (ptr != NULL) {
        set->data = ptr;
        set->capacity = cap;
    }
}
```
The correct implementation is the version 1. It is necessary to check if the output of the realloc is not null before using its value to check if there is sufficient memory left.

### Activity 6: Function implementations

```c
bool set_contains(const set_t * set, double value) {
    for (int i = 0; i < set->size; i++) {
        if (equals_dbl(value, set->data[i])) {
            return true;
        }
    }
    return false;
}

void set_add(set_t * set, double value) {
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
```

### Activity 7: Time complexity of remove and add

| Operation | Time complexity |
|-----------| --------------- |
| Contains  | O(n)               |
| Add       | O(n)                |
| Remove    | O(n)                |

Record your answer here

### Activity 8: Binary search

Value to find: 46:

| Binary search step | lo  | hi  | mid |
|--------------------|-----|-----|-----|
| 1                  | 0   | 16  | 8  |
| 2                  | 9    | 16    | 12    |
| 3                  | 13    | 16    | 14     |
| 4                  | 13    | 14    | 13    |
| 5                  |     |     |     |

Value to find: 4:

| Binary search step | lo  | hi  | mid |
|--------------------|-----|-----|-----|
| 1                  | 0   | 16  | 8  |
| 2                  | 0    | 8    | 4    |
| 3                  | 0    | 4    | 2    |
| 4                  | 0    | 2    | 1    |
| 5                  | 0    | 0    | 0    |


### Activity 9: Binary search - Time complexity

| Array size | Lookups |
|------------|---------|
| 16         | 5       |
| 32         |6        |
| 64         | 7       |
| 128        |  8      |
| 256        |   9     |

The time complexity of binary search is O(logn).


### Activity 10: Implementing index_of

```c
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
```


### Activity 11: Modifying the sorted array

```c
/// set_add:
/// set_remove:
/// set_contains:
```
Record your answer here

### Activity 12: Time complexity of the sorted set

| Operation | Time complexity |
|-----------| --------------- |
| Add       |    O(n + logn)              |
| Remove    |    O(n + logn)             |
| Contains  |    O(logn)             |

Record your answer here

## Generic set (optional)

### Activity 13: Functions index_of and contains

Record your answer here

### Activity 14: Functions add and remove

Record your answer here


## Looking back

### What we've learnt

Formulate at least one lesson learned.

### What were the surprises

Fill in...

### What problems we've encountered

Fill in...

### What was or still is unclear

Fill in...

### How did the group perform?

How was the collaboration? What were the reasons for hick-ups? What worked well? What can be improved next time?





> Written with [StackEdit](https://stackedit.io/).
