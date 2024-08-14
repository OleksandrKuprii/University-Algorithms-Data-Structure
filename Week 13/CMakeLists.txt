cmake_minimum_required(VERSION 3.15)
project(shortestpaths)

set(CMAKE_CXX_STANDARD 20)
#set(CMAKE_CXX_FLAGS -mmacosx-version-min=10.7)

add_executable(shortestpaths main.cpp graph.cpp graph.h colours.h path_data.cpp path_data.h shortest_paths.cpp shortest_paths.h shortest_paths_tester.cpp shortest_paths_tester.h vertex_heap.cpp vertex_heap.h visitor.cpp visitor.h)

target_compile_options(shortestpaths PRIVATE -Wall -Wextra -pedantic)

file(GLOB MY_PUBLIC_HEADERS "graphs/*")
file(COPY ${MY_PUBLIC_HEADERS} DESTINATION ${CMAKE_BINARY_DIR})
