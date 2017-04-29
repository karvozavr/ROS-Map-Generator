cmake_minimum_required(VERSION 3.7)
project(ROS_map_generator)

set(CMAKE_CXX_STANDARD 14)
find_package(catkin REQUIRED map_server)
include_directories(include ${catkin_INCLUDE_DIRS})

set(SOURCE_FILES
        include/room.h
        include/ros_map_printer.h
        include/ros_navigation_environment.h
        src/main.cpp
        src/room.cpp
        src/ros_navigation_environment.cpp src/ros_map_printer.cpp)

include_directories(include)

link_libraries(boost_system)
add_executable(ROS_map_generator ${SOURCE_FILES})