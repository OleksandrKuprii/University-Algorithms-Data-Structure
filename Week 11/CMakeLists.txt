cmake_minimum_required(VERSION 3.15)
project(heap)

set(CMAKE_CXX_STANDARD 20)

add_executable(heap main.cpp maxheap.cpp maxheap.h heap_tester.cpp heap_tester.h task.cpp task.h)
target_compile_options(heap PRIVATE -Wall -Wextra -pedantic -Werror)
