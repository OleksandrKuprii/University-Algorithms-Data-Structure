# Week 2 - Dynamic Arrays

## Team

Team name: Encoder
Date: 15-03-2022

Members
Oleksandr Kuprii
Illia Kara

| Role                                                                                                                                                                          | Name |
|-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|------|
| **Facilitator** keeps track of time, assigns tasks and makes sure all the group members are heard and that decisions are agreed upon.                                             | Oleksandr     |
| **Spokesperson** communicates group’s questions and problems to the teacher and talks to other teams; presents the group’s findings.                                              | Illia     |
| **Reflector** observes and assesses the interactions and performance among team members. Provides positive feedback and intervenes with suggestions to improve groups’ processes. | Illia     |
| **Recorder** guides consensus building in the group by recording answers to questions. Collects important information and data.                                                   | Oleksandr     |

## Activities
Make sure to have the activities signed off regularly to ensure progress is tracked.

Set up a project in CLion to write the small programs needed in some of the activities.

### Activity 1: Random access

````c
#include <stdio.h>

#define COUNT (50)

void fill_fibonacci(unsigned long long * storage, int count) {
    storage[0] = 0;
    storage[1] = 1;

    for (int i = 2; i < count; i++) {
        storage[i] = storage[i - 1] + storage[i-2];
    }
}


int main(void) {
    unsigned long long array[COUNT];
    fill_fibonacci(array, COUNT);

    for (int i = 1; i < COUNT; i++) {
        printf("f(%d) = %llu\n", i, array[i]);
    }
}
````



### Activity 2: Array definition
```C
typedef struct array {
    size_t capacity;
    size_t count;
    float *data;
} array_t;
```

Description of fields:
**capacity** - the maximum number of elements
**count**    - the actual number of elements in the array
***data**    - the pointer to the first element of the array

### Activity 3: Correct initialization

The correct initialization is version 3. It checks if the array_t pointer is not NULL and if the capacity is not zero. Then, it allocates the required amount of memory to store data.
```C
array_t* array_init(array_t *pArray, size_t capacity) { // version 3
    if (pArray != NULL) {
        if (capacity != 0) {
            pArray->data = malloc(sizeof(float[capacity]));
            pArray->count = 0;
            pArray->capacity = pArray->data != NULL ? capacity : 0;
        } else {
            pArray->data = NULL;
            pArray->count = 0;
            pArray->capacity = 0;
        }
    }
    return pArray;
}
```


### Activity 4: Cleaning up

Program 2 is correct. The first one initialises the array on stack, so its memory cannot be freed. Oppositely, the array in the second program is initialized on heap, thus can be freed.
```c
int main(void) {
    array_t *array = (array_t *) malloc(sizeof(array_t));
    array_init(array, 10);

    // .... do some work ...
    // finally, clean up

    array_destroy(array);
    free(array);
}
```



Record your answer here

### Activity 5: Resizing an array

```c
void array_reserve(array_t *p_array, size_t min_capacity) {
    size_t capacity = p_array->capacity;
    while (capacity < min_capacity) {
        capacity = (size_t) (((double) capacity + 1) * 1.6);
    }

    p_array->capacity = capacity;
    p_array->data = realloc(p_array->data, sizeof (array_t) * capacity);
}
```

### Activity 6: Appending values

```c
void array_append(array_t * p_array, float value) {
    if (p_array->count == p_array->capacity) {
        array_reserve(p_array, p_array->count + 1);
    }
    
    p_array->data[p_array->count] = value;
    p_array->count++;
}
```


### Activity 7: Inserting values

```c
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
```


### Activity 8: Removing by index

```c
void array_remove(array_t * p_array, int index) {

    for (size_t i = index; i < p_array->count; i++) {
            p_array->data[i] = p_array->data[i + 1];
    }

    p_array->count--;
}
```



### Activity 9: Finding a value

```c
int array_find(array_t * p_array, float value) {

    for (size_t i = 0; i < p_array->count; i++) {
        if (p_array->data[i] == value) {
           return i;
        }
    }

    return -1;
}
```


### Activity 10: Constant time complexity

Time complexity is a time efficiency of algorithm which needed for computer to compute algorith. 
The worst time complexity are: insert, remove, find. All of them have **O(n)** time complexity

### Activity 11: Worst-case time complexity

| Operation       | Worst-case time complexity |
| --------------- |:--------------------------:|
| Insert          |            O(n)            |
| Remove          |            O(n)            |
| Find            |            O(n)            |
| Lookup / access |            O(1)            |


### Activity 12: Complexity of *append*

Time complexity of **Append** is **O(1)**, but if we do not have enough capacity in array it will use array_reserve() so time compexity can be **O(n)** 

### Activity 13: Storing grades in a dynamically growing array

```c
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
    array_t grades;
    array_init(&grades, 4);
    input_grades(&grades);
    float averageReturn = average(&grades);
    int passed = num_passed(&grades);

    printf("Average grade: %.2f\n", averageReturn);
    printf("%d out of %zu students passed\n", passed, grades.count);

    array_destroy(&grades);
}
```


## Looking back

### What we've learnt

We have learnt how to implement and use dynamic arrays.

### What were the surprises

The early morning of the Thursday on the 24th of February

### What problems we've encountered

- The ruthless war in Ukraine
- The difficulty to work efficiently in this period

### What was or still is unclear

... pointers

### How did the group perform?

According to the situation, pretty good




