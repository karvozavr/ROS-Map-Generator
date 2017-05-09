#!/bin/bash

echo "Installing map generator..."

# CMake project files generation
cmake CMakeLists.txt

if [ $? -ne 0 ] 
then
	echo "\"CMake\" error occured during installation!"
	exit 1
fi

# make the project
make

if [ $? -ne 0 ] 
then
	echo "\"make\" error occured during installation!"
	exit 1
fi
