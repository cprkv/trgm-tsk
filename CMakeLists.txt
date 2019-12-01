cmake_minimum_required( VERSION 3.1 )

set(
	SOURCES
		${CMAKE_CURRENT_SOURCE_DIR}/src/Str.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/src/StrBuffer.cpp
)
set(
	TESTS
		${SOURCES}
		${CMAKE_CURRENT_SOURCE_DIR}/tests/TestFramework.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/tests/StrTests.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/tests/StrComparatorTests.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/tests/StrBufferTests.cpp
)


#######################################################
project( example CXX )
add_executable(
	example
		${CMAKE_CURRENT_SOURCE_DIR}/src/Example.cpp
		${SOURCES}
)
target_include_directories(
	example
	PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src
)
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
		${CMAKE_CURRENT_SOURCE_DIR}/tests/Entry.cpp
		${TESTS}
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
