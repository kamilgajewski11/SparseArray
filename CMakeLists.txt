cmake_minimum_required(VERSION 3.15)
project(SparseArray)

set(CMAKE_CXX_STANDARD 14)

add_executable(SparseArray main.cpp SparseArray.cpp SparseArray.h Z3.cpp Z3.h)