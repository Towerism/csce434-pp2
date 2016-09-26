cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

project(decaf)

set(CMAKE_CXX_FLAGS "-std=c++11 ${CMAKE_CXX_FLAGS} -Wall -Wextra")

find_package(FLEX REQUIRED)
find_package(BISON REQUIRED)

include_directories(decaf)
add_subdirectory(decaf)
add_subdirectory(test)
