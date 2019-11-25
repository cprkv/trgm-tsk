cmake_minimum_required( VERSION 3.10 )


#######################################################
project( example CXX )
add_executable(
	example
		src/SimpleString.cpp
		src/Example.cpp
)
target_include_directories( example PRIVATE src )
set_target_properties(
	example PROPERTIES
		CXX_STANDARD			11
		CXX_STANDARD_REQUIRED 	ON
		CXX_EXTENSIONS			OFF
)


#######################################################
project( tests CXX )
add_executable(
	tests
		src/SimpleString.cpp
		tests/TestFramework.cpp
		tests/SimpleStringTests.cpp
		tests/SimpleStringComparatorTests.cpp
)
target_include_directories( 
	tests
	PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src
			${CMAKE_CURRENT_SOURCE_DIR}/tests
)
set_target_properties(
	tests PROPERTIES
		CXX_STANDARD			11
		CXX_STANDARD_REQUIRED 	ON
		CXX_EXTENSIONS			OFF
)
