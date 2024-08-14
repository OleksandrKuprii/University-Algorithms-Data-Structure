cmake_minimum_required(VERSION 3.15)
project(hashing C)

set(CMAKE_C_STANDARD 99)

add_executable(hashing main.c hashmap.h hashmap.c list.h list.c)
configure_file(alice0.txt alice0.txt COPYONLY)
configure_file(short.txt short.txt COPYONLY)

target_compile_options(hashing PRIVATE -Wall -Wextra -pedantic)
