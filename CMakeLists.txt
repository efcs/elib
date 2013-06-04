cmake_minimum_required (VERSION 2.8)

if (EXISTS "/opt/gnu/bin/g++")
	set(CMAKE_C_COMPILER /opt/gnu/bin/gcc)
	set(CMAKE_CXX_COMPILER /opt/gnu/bin/g++)
	add_definitions(-L/opt/gnu/lib64)
	set(ENV{LD_LIBRARY_PATH} "/opt/gnu/lib64")
endif()

# we need C to get the pthreads library 
project(EricsLibrary CXX C)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}) 
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})

set( CMAKE_BUILD_TYPE distribution )
set( CMAKE_CXX_FLAGS_DISTRIBUTION "-O3" )
set( CMAKE_C_FLAGS_DISTRIBUTION "-O3" )
set( CMAKE_C_FLAGS_DEBUG "-g -O0" )
set( CMAKE_CXX_FLAGS_DEBUG "-g -O0" )

add_definitions(-std=c++11 -Wall -Wextra -pedantic)
add_definitions(-include ${CMAKE_CURRENT_LIST_DIR}/src/include/elib/commondef.h)

add_subdirectory(src)
add_subdirectory(tests)

