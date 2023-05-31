cmake_minimum_required(VERSION 3.22)

project(processor)
set(CMAKE_CXX_STANDARD 14)
find_package(Eigen3 REQUIRED)
add_library(processor INTERFACE)

find_package(Eigen3)
target_link_libraries(util INTERFACE Eigen3::Eigen)
target_include_directories(processor INTERFACE .)