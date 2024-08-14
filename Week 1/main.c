#include <stdio.h>
#include <stdlib.h>

int main() {
    int stack_variable = 42;
    int* ptr = &stack_variable;
    printf("ptr = %p\n", ptr);
//    free(ptr);
    printf("free(ptr) = %p\n", ptr);
    int* null_ptr = NULL;
    printf("ptr = %p\n", null_ptr);
    free(null_ptr);
    printf("free(null_ptr) = %p\n", null_ptr);
}
