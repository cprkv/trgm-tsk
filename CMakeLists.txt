cmake_minimum_required( VERSION 3.10 )
project( example CXX )

add_executable(
	example
		src/SimpleString.cpp
		src/Example.cpp
)
target_include_directories(
	example
	PUBLIC
		src
)
set_target_properties(
	example
	PROPERTIES
		CXX_STANDARD 11
		CXX_STANDARD_REQUIRED ON
		CXX_EXTENSIONS OFF
)
