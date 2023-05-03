cmake_minimum_required(VERSION 3.22)

project(processor)
set(CMAKE_CXX_STANDARD 14)
add_library(processor INTERFACE)
target_include_directories(processor INTERFACE .)