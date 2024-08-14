cmake_minimum_required(VERSION 3.19)
project(sorting C)

set(CMAKE_C_STANDARD 99)

add_executable(sorting main.c array.c array.h list.c list.h)

target_compile_options(sorting PRIVATE -Wall)