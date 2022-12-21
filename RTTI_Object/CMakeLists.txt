cmake_minimum_required(VERSION 3.22)
project(RTTI_Object)

set(CMAKE_CXX_STANDARD 20)

add_library(RTTI_Object Object.cpp)
target_link_libraries(RTTI_Object PRIVATE SIMD_lib)
