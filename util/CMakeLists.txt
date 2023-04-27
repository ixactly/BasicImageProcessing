cmake_minimum_required(VERSION 3.22)

project(utility)
set(CMAKE_CXX_STANDARD 14)
add_library(util STATIC ./src/image.cpp ./src/io.cpp)
find_package(OpenCV)
target_link_libraries(util ${OpenCV_LIBS})
target_include_directories(util PUBLIC ./include)