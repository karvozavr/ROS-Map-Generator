#
# ROS map generator
#  CMakeLists.txt
#
# Created by Dmitriy Abramov (karvozavr@gmail.com) April, 2017
#

cmake_minimum_required(VERSION 3.5)
project(map_generator)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        include/room.h
        include/ros_navigation_environment_renderer.h
        include/ros_navigation_environment.h
        src/main.cpp
        src/room.cpp
        src/ros_navigation_environment.cpp
        src/ros_navigation_environment_renderer.cpp
        include/randomizer.h
        include/graph.h)

include_directories(include)

link_libraries(boost_system boost_program_options)
add_executable(map_generator ${SOURCE_FILES})