cmake_minimum_required(VERSION 3.6)
project(Matrix)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES library.cpp library.h Matrix.cpp)
add_library(Matrix ${SOURCE_FILES})