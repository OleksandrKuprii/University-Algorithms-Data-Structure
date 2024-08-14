cmake_minimum_required(VERSION 3.19)
project(sets C)

set(CMAKE_C_STANDARD 99)

add_executable(sets main.c)

target_compile_options(sets PRIVATE -Wall -Wextra -pedantic)
