cmake_minimum_required(VERSION 3.15)
project(graphs)

set(CMAKE_CXX_STANDARD 20)

add_executable(graphs main.cpp graph.cpp graph.h colours.h visitor.cpp visitor.h)

target_compile_options(graphs PRIVATE -Wall -Wextra -pedantic)

file(GLOB MY_PUBLIC_HEADERS "graphs/*")
file(COPY ${MY_PUBLIC_HEADERS} DESTINATION ${CMAKE_BINARY_DIR})

