# Week 1 - Memory

## Team

Team name: Encoder
Date: 8 February 2022

Members

| Role                                                                                                                                                                          | Name |
|-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|------|
| **Facilitator** keeps track of time, assigns tasks and makes sure all the group members are heard and that decisions are agreed upon.                                             | Karina |
| **Spokesperson** communicates group’s questions and problems to the teacher and talks to other teams; presents the group’s findings.                                              | Illia |
| **Reflector** observes and assesses the interactions and performance among team members. Provides positive feedback and intervenes with suggestions to improve groups’ processes. | Rimma |
| **Recorder** guides consensus building in the group by recording answers to questions. Collects important information and data.                                                   | Oleksandr |

## Activities
Make sure to have the activities signed off regularly to ensure progress is tracked.

Set up a project in CLion to write the small programs needed in some of the activities.

### Activity 1: Memory usage - the sizeof operator
```C
#include <stdio.h>

int main() {
    printf("size of char %d\n", sizeof(char));
    printf("size of short int %d\n", sizeof(short int));
    printf("size of int %d\n", sizeof(int));
    printf("size of long int %d\n", sizeof(long int));
    printf("size of long long int %d\n", sizeof(long long int));
    printf("size of float %d\n", sizeof(float));
    printf("size of double %d\n", sizeof(double));
    printf("size of long double %d\n", sizeof(long double));
    printf("size of char* %d\n", sizeof(char*));
    printf("size of int* %d\n", sizeof(int*));
    printf("size of  float* %d\n", sizeof(float*));
    printf("size of double* %d\n", sizeof(double*));
    printf("size of void* %d", sizeof(void*));
    return 0;
}
```
|   Data type   | Size in bytes |   | Pointer data type | Size in bytes |
|:-------------:|:-------------:|:-:|:-----------------:|:-------------:|
| char          | 1             |   | char *            | 8             |
| short int     | 2             |   | int *             | 8             |
| int           | 4             |   | float *           | 8             |
| long int      | 8             |   | double *          | 8             |
| long long int | 8             |   | void *            | 8             |
| float         | 4             |   |                   |               |
| double        | 8             |   |                   |               |
| long double   | 16            |   |                   |               |



### Activity 2: Array and structure sizes
Size of int array equals 40, because type integer is 4 bytes and array is defined as array with 10 elements (4*10=40).
Size of person_t structure equals 84, because name (char) takes 80 bytes and age(int) takes 4.
Size of array parameter equals 8, because it is a pointer to the first character of the first element of array and every pointer is 8 bytes.
Size of p parameter equals 84, because it is a pointer to the whole structure == size of the structure(84).

```C
typedef struct {
	char name[80];
	int age;
} person_t;

void size_array(int array[]) {
	printf("Size of array parameter: %lu\n", sizeof(array));
}

void size_struct(person_t p) {
	printf("Size of p parameter: %lu\n", sizeof(p));
}

int main() {
	int array[10];
	person_t bob = {.name = "Bob", .age = 22};
	
	printf("Size of int array: %lu\n", sizeof(array));
	printf("Size of person_t structure: %lu\n", sizeof(bob));
	
	size_array(array);
	size_struct(bob);
}
```
|    Data type    | Size in bytes |
|:---------------:|:-------------:|
| int array       | 40            |
| person_t struct | 84            |
| array parameter | 8             |
| p parameter     | 84            |

### Activity 3: Memory addresses
Characters of the string "Hello" stored near the variables s (address of s variable is the address of string's first character).
There are memory gaps between stored variables (a, c and b), while variables s and buf[] have no gap between them.
```C
#include <stdio.h>
int main( void )  {
    int a = 0xA0B0C0D0;
    short int b = 0x7856;
    const char * s = "Hello!";
    char buf[] = "Pointer";
    short int c = 0x3412;

    printf("int a: %p\n", (void*) &a);
    printf("short int b: %p\n", (void*) &b);
    printf("const char *s: %p\n", (void*) &s);
    printf("char buf[]: %p\n", (void*) buf);
    printf("short int c: %p\n", (void*) &c);

    printf("%c: %p\n", *s, (void*)&s);
}
```
|    Variable    |     Address    |
|:--------------:|:--------------:|
| int a          | 0x7ffee2e57a7c |
| short int b    | 0x7ffee2e57a7a |
| const char * c | 0x7ffee2e57a70 |
| char buf[]     | 0x7ffee2e57a80 |
| short int c    | 0x7ffee2e57a6e |
| 'H'            | 0x7ffee2e57a70 |


### Activity 4: Observing automatic lifetime
Memory addresses of local variables inside the function reused, because two variables can’t co-exist at the same memory location.
a,b,c and x,y,z are variables that need to be alive at a given point during the execution of a program, so they must be stored at different memory addresses.
```C
#include <stdio.h>
int add(int a, int b) {
    int c = a + b;
    printf("int a: %p\n", (void*) &a);
    printf("int b: %p\n", (void*) &b);
    printf("int c: %p\n", (void*) &c);
    return c;
}
int mul(int x, int y) {
    int z = x * y;
    printf("int x: %p\n", (void*) &x);
    printf("int y: %p\n", (void*) &y);
    printf("int z: %p\n", (void*) &z);
    return z;
}
int main( void ) {
    printf("%d\n", mul(add(3, 4), add(1, 5)));
}
```
| Variable |     Address    |
|:--------:|:--------------:|
| int a    | 0x7ffeee5d3a6c |
| int b    | 0x7ffeee5d3a68 |
| int c    | 0x7ffeee5d3a64 |
| int a    | 0x7ffeee5d3a6c |
| int b    | 0x7ffeee5d3a68 |
| int c    | 0x7ffeee5d3a64 |
| int x    | 0x7ffeee5d3a6c |
| int y    | 0x7ffeee5d3a68 |
| int z    | 0x7ffeee5d3a64 |

Result: 42

### Activity 5: Observing the stack
Addresses for a and b variables are reused, because function "poly" executed twice separately in function "add_polys". For x and y required other addresses, because they are used with "poly" function at the same time.
```C
#include <stdio.h>
int poly(int a) {
     int b = a * (a + 1);
     return b / 2;
     }

 int add_polys(int x, int y) {
     int bx = poly(x);
     int by = poly(y);
     return bx + by;
     }

 int main( void ) {
     printf("%d\n", add_polys(42, 24));
     }
```     
| Variable |     Address    |
|:--------:|:--------------:|
| int a    | 0x7ffeed892a5c |
| int b    | 0x7ffeed892a58 |
| int a    | 0x7ffeed892a5c |
| int b    | 0x7ffeed892a58 |
| int x    | 0x7ffeed892a7c |
| int y    | 0x7ffeed892a78 |

Result: 1203

### Activity 6: Leaking local addresses
Program outputs different values of ``*ptr_answer`, because of leaking local addresses.

```C
#include <stdio.h>
int* get_answer( void ) {
    int answer = 42;
    int *ptr_answer = &answer;
    return ptr_answer;
}
void i_do_nothing(void) {
        int no_answer[] = {24, 24, 24, 24};
}

int main( void ) {
    int* ptr_answer = get_answer();
    printf("The answer is: %d\n", *ptr_answer);
    i_do_nothing();
    printf("The answer is: %d\n", *ptr_answer);
}
```

The answer is: 42
The answer is: -748962895

Bug can be solved by passing the value of local variable instead of passing its' address. For example:
```C
#include <stdio.h>
int get_answer( void ) {
    int answer = 42;
    return answer;
}
int main( void ) {
    printf("The answer is: %d\n", get_answer());
}
```
The answer is: 42

### Activity 7: Memory addresses of local variables

ERRORS: 
Undefined symbols for architecture x86_64:
  "_do_some_work", referenced from:
      _main in main.c.o
ld: symbol(s) not found for architecture x86_64
clang: error: linker command failed with exit code 1 (use -v to see invocation)
make[3]: *** [untitled] Error 1
make[2]: *** [CMakeFiles/untitled.dir/all] Error 2
make[1]: *** [CMakeFiles/untitled.dir/rule] Error 2
make: *** [untitled] Error 2

The problem is that in this program we have an array
that can subsequently be used by other parts of the program for storing data

### Activity 8: Using malloc

```C
#include <stdio.h>
#include <stdlib.h>
int* func(int count){
     int *p = (int*)malloc(count*4);
     return p;
}
int main( void ) {
    unsigned long (*number) = (unsigned long*) malloc(8);
    float(*b)[256] = (float(*)[256]) malloc(1024);
    func(23);
}
```

### Activity 9: Using allocated memory as an array

1) In the allocated block of memory 5 integeres can be stored. The reason is that the number of bytes passed to the `malloc()` is 20. It equals to 5 integers as the size of the integer is 4 bytes.
2) Accessing an array outside its bounds is undefined behavior. That means that anything can happen, including the program behaving as expected it to.
3) The problem is the number of bytes allocated by `malloc()`. Fix: use `malloc(sizeof(int) * capacity)`.

```C
#include "stdio.h"
#include "stdlib.h"

int main( void ) {
     const int capacity = 20;
     int *ptr = (int*) malloc(capacity);

     for (int i = 0; i < capacity + 1; i++) {
         printf("ptr[%d] = %d", i, ptr[i]);
    }
}

```

### Activity 10: Infinite memory?

The program ends when it cannot allocate more memory then available on the machine.
```C
int main( void ) {
     const unsigned int block_size = 1 << 28;
     unsigned int counter = 1;

     void *ptr = malloc(block_size);
     while (ptr != NULL) {
         ptr = malloc(block_size);
         counter++;
     }
     printf("%d", counter);
}
```
On different machines we got different results: **127**, **84** - on Intel processors.
The anomaly results **522712** and **524139** received on Macs both on Intel and M1 chips. Probably, it has something to do with the OS.

### Activity 11: Fixing a memory leak

The program does not crash, because we deallocate memory in every iteration. It reaches the counter to be 1 million and quits.
```C
int main( void ) {
     const unsigned int block_size = 1 << 28;
     unsigned int counter = 1;

     void *ptr = malloc(block_size);

     while (ptr != NULL) {
         free(ptr);
         ptr = malloc(block_size);
         counter++;

         if (counter == 1000000) {
             break;
         }
     }
     printf("%d", counter);
}
```

### Activity 12: Dangerous `free`s

Malloc allocates memory to the **heap** this is the only memory type that can freed. **int** pointer allocated in the **stack** memory that cannot be freed.
```C
#include <stdio.h>
#include <stdlib.h>

int main() {
    int stack_variable = 42;
    int* ptr = &stack_variable;
    printf("ptr = %p\n", ptr);
    free(ptr);
    printf("free(ptr) = %p\n", ptr);
    int* null_ptr = NULL;
    printf("ptr = %p\n", null_ptr);
    free(null_ptr);
    printf("free(null_ptr) = %p\n", null_ptr);
}
```
Output:
```C
ptr = 000000000061FE0C
free(ptr) = 000000000061FE0C
ptr = 0000000000000000
free(null_ptr) = 0000000000000000
```

### Activity 13: Using realloc

Realloc releases old memory when relocates. So you need to use **free** only once

```C
#include <stdio.h>
#include <stdlib.h>

 int main( void ) {
    float *grades = NULL;
    for (int capacity = 10; capacity <= 100; capacity += 10) {
        float *new_grades = (float*)realloc(grades, sizeof(float[capacity]));
        if (new_grades != NULL) {
            grades = new_grades;
            printf("%p\n", grades);
        }
    }
}
```

### Activity 14: Using a dynamically sized buffer

```C
#include <stdio.h>
#include <stddef.h>
#include "stdlib.h"

int main( void ) {
    char *ptr = NULL;
    unsigned long capacity = 20;
    ptr = realloc(ptr, sizeof(char[capacity]));
    
    if (!ptr) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    FILE *file = fopen("input.txt", "r");
    if (!file) {
        fprintf(stderr, "Error opening file\n");
        return 1;
    }
    
    unsigned long count = 0;
    int c = fgetc(file);
    
    while (c != EOF) {
        if (count == capacity) {
            ptr = realloc(ptr, sizeof(char[(int) (capacity * 1.5)] ));
            count = 0;
            
            if (ptr == NULL) {
                fprintf(stderr, "Pointer is null\n");
            }
        }
        ptr[count++] = (char) c;
        printf("%p %c\n", ptr + count - 1, c);
        c = fgetc(file);
    }

}
```


## Looking back

### What we've learnt

We deepened our knowledge in working with memory in C. We learnt how to allocate and deallocate memory, how to prevent the leakage of memory.

### What were the surprises

It was surprising how Mac on M1 chip could allocate so much memory.

### What problems we've encountered

Sometimes it is complicated and counfusing to debug code which requires memory management.

### What was or still is unclear

What is the magic under the result of Activity 10 on Macs and what is the bahaviour of Mac system.

### How did the group perform?

During this week, all activities were equally shared and discussed within the group. No one in a team was left behind, meaning all of us got qualitative knowledge. Overall, group performance was on a high level.





> Written with [StackEdit](https://stackedit.io/).
