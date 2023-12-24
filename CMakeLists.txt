cmake_minimum_required(VERSION 3.0)

project(pace2024)

# Set C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_C_FLAGS_DEBUG "-g -DDEBUG")
set(CMAKE_CXX_FLAGS_DEBUG "-g -DDEBUG")

set(SOURCES
    src/main.cpp
    src/graph/bipartite_graph.cpp
    src/algorithms/brute_force.cpp
    src/utils/utility.cpp
)

# Include directories
include_directories(include/)

# Add executable
add_executable(mincrossing ${SOURCES})
