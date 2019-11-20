cmake_minimum_required( VERSION 3.10 )


#######################################################
project( example CXX )
add_executable(
	example
		src/SimpleString.cpp
		src/Example.cpp
)
target_include_directories( example PUBLIC src )
set_target_properties(
	example PROPERTIES
		CXX_STANDARD			11
		CXX_STANDARD_REQUIRED 	ON
		CXX_EXTENSIONS			OFF
		INCLUDE_DIRECTORIES 	${CMAKE_CURRENT_SOURCE_DIR}/src
)


#######################################################
project( tests CXX )
add_executable(
	tests
		src/SimpleString.cpp
		src/Tests.cpp
)
set_target_properties(
	tests PROPERTIES
		CXX_STANDARD			11
		CXX_STANDARD_REQUIRED 	ON
		CXX_EXTENSIONS			OFF
		INCLUDE_DIRECTORIES 	${CMAKE_CURRENT_SOURCE_DIR}/src
)
