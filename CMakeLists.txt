cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

project(decaf)

set(CMAKE_CXX_FLAGS "-std=c++11 ${CMAKE_CXX_FLAGS} -ggdb -O0 -Wall -Wextra -Wno-unused -Wno-unused-parameter -Wno-sign-compare")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -lstdc++")
set(CMAKE_EXPORT_COMPILE_COMMANDS 1)

find_package(FLEX REQUIRED)
find_package(BISON REQUIRED)

include_directories(decaf)
include_directories(${CMAKE_BINARY_DIR})

add_subdirectory(decaf)
add_subdirectory(test)
