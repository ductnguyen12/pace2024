# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "C:/Users/LENOVO/Desktop/Graph lab/pace2024/cmake-build-debug/_deps/argparse-src"
  "C:/Users/LENOVO/Desktop/Graph lab/pace2024/cmake-build-debug/_deps/argparse-build"
  "C:/Users/LENOVO/Desktop/Graph lab/pace2024/cmake-build-debug/_deps/argparse-subbuild/argparse-populate-prefix"
  "C:/Users/LENOVO/Desktop/Graph lab/pace2024/cmake-build-debug/_deps/argparse-subbuild/argparse-populate-prefix/tmp"
  "C:/Users/LENOVO/Desktop/Graph lab/pace2024/cmake-build-debug/_deps/argparse-subbuild/argparse-populate-prefix/src/argparse-populate-stamp"
  "C:/Users/LENOVO/Desktop/Graph lab/pace2024/cmake-build-debug/_deps/argparse-subbuild/argparse-populate-prefix/src"
  "C:/Users/LENOVO/Desktop/Graph lab/pace2024/cmake-build-debug/_deps/argparse-subbuild/argparse-populate-prefix/src/argparse-populate-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "C:/Users/LENOVO/Desktop/Graph lab/pace2024/cmake-build-debug/_deps/argparse-subbuild/argparse-populate-prefix/src/argparse-populate-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "C:/Users/LENOVO/Desktop/Graph lab/pace2024/cmake-build-debug/_deps/argparse-subbuild/argparse-populate-prefix/src/argparse-populate-stamp${cfgdir}") # cfgdir has leading slash
endif()
