cmake_minimum_required(VERSION 3.15)
project(BSTs)

set(CMAKE_CXX_STANDARD 20)

add_executable(BSTs main.cpp bintree_node.cpp bintree_node.h bintree.cpp bintree.h bintree_tester.cpp bintree_tester.h bintree_writer.cpp bintree_writer.h)
target_compile_options(BSTs PRIVATE -Wall -Wextra -pedantic -fsanitize=address)
target_link_options(BSTs PRIVATE -fsanitize=address)