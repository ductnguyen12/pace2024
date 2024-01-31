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
    src/algorithms/random_search.cpp
    src/algorithms/simulated_annealing.cpp
    src/algorithms/ilp_algorithm.cpp
    src/utils/utility.cpp
    src/utils/argument.cpp
    src/utils/random.cpp
    src/stopping_conditions/time_stopping_condition.cpp
    src/stopping_conditions/iteration_stopping_condition.cpp
    src/stopping_conditions/combined_stopping_condition.cpp
)

set(GENERATE_SOURCES
    src/generate.cpp
    src/utils/random.cpp
)

# Set DEBUG_MODE definition
if(CMAKE_BUILD_TYPE MATCHES "DebugMode")
    add_compile_definitions(DEBUG_MODE)
endif()

list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR})
message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")

# Include directories
include_directories(include/)

# Add executable
if(CMAKE_BUILD_TYPE MATCHES "GenerateMode")
    add_executable(generate ${GENERATE_SOURCES})
else()
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
