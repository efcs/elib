cmake_minimum_required (VERSION 2.8.4)

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
add_definitions(-imacros ${CMAKE_CURRENT_LIST_DIR}/src/include/elib/commondef.h)

add_subdirectory(src)
add_subdirectory(tests)

