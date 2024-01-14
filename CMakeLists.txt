cmake_minimum_required(VERSION 3.0)

project(pace2024)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_C_FLAGS_DEBUG "-g -DDEBUG")
set(CMAKE_CXX_FLAGS_DEBUG "-g -DDEBUG")

# Set sources
set(SOURCES
    src/main.cpp
    src/problems/problem.cpp
    src/graph/bipartite_graph.cpp
    src/algorithms/brute_force.cpp
    src/algorithms/genetic_algorithm.cpp
    src/utils/utility.cpp
    src/utils/argument.cpp
    src/utils/random.cpp
    src/stopping_conditions/time_stopping_condition.cpp
        include/algorithms/random_search.h
        include/algorithms/simulated_annealing.h
        src/algorithms/random_search.cpp
        src/algorithms/simulated_annealing.cpp
)

# Set DEBUG_MODE definition
if(CMAKE_BUILD_TYPE MATCHES "Debug")
    add_compile_definitions(DEBUG_MODE)
endif()

# Include directories
include_directories(include/)

# Add executable
add_executable(mincrossing ${SOURCES})

# Dependencies
include(FetchContent)

# fetch latest argparse
FetchContent_Declare(
    argparse
    GIT_REPOSITORY https://github.com/p-ranav/argparse.git
)
FetchContent_MakeAvailable(argparse)

target_link_libraries(mincrossing argparse)
