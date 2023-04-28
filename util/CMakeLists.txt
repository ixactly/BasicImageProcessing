cmake_minimum_required(VERSION 3.22)

project(utility)
set(CMAKE_CXX_STANDARD 14)
add_library(util INTERFACE)
target_include_directories(util INTERFACE include)
find_package(OpenCV)
target_link_libraries(util INTERFACE ${OpenCV_LIBS})