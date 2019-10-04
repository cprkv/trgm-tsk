cmake_minimum_required(VERSION 3.10)
project(example CXX)
add_executable(
	example
	src/SimpleString.h
	src/SimpleString.cpp
	src/Example.cpp
)
target_include_directories(
	example
	PRIVATE src
)
set_target_properties(
	example PROPERTIES
	CXX_STANDARD 14
	CXX_STANDARD_REQUIRED TRUE
	CXX_EXTENSIONS OFF
)
