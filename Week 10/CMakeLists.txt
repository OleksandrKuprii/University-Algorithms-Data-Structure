cmake_minimum_required(VERSION 3.15)
project(BalancedBSTs)

set(CMAKE_CXX_STANDARD 20)

add_executable(BalancedBSTs main.cpp bintree_node.cpp bintree_node.h bintree.cpp bintree.h bintree_tester.cpp bintree_tester.h bintree_writer.cpp bintree_writer.h)
target_compile_options(BalancedBSTs PRIVATE -Wall -Wextra -pedantic)