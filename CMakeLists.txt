cmake_minimum_required(VERSION 3.7)
project(ROS_map_generator)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS_DEBUG "-Wall -Wextra -Wshadow")
include_directories(include)

set(SOURCE_FILES
        src/main.cpp include/some_header.h)

add_executable(ROS_map_generator ${SOURCE_FILES})