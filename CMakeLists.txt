cmake_minimum_required(VERSION 3.6)
project(backlight)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c99")

set(SOURCE_FILES main.c)
add_executable(backlight ${SOURCE_FILES})
