cmake_minimum_required(VERSION 3.22)
project(SIMD_lib)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

add_library(SIMD_lib STATIC simd.cpp)
