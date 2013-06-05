cmake_minimum_required (VERSION 2.8)

option(CONFIG_MY_BUILD "These are my specific build settings" ON)

if (CONFIG_MY_BUILD)

	option(CONFIG_OPT_GCC "Use /opt/gnu/bin/* and /opt/gnu/lib64" ON)
	
	if (CONFIG_OPT_GCC)
		set(CMAKE_C_COMPILER /opt/gnu/bin/gcc)
		set(CMAKE_CXX_COMPILER /opt/gnu/bin/g++)
		add_definitions(-L/opt/gnu/lib64 -Wl,-rpath -Wl,/opt/gnu/lib64)
		set(LD_FLAGS "-static-libstdc++")
	endif()	
endif()

# we need C to get the pthreads library 
project(EricsLibrary CXX C)


if (CONFIG_MY_BUILD)
	if(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
		set(CMAKE_INSTALL_PREFIX "/home/eric/lib" 
			CACHE PATH "library install prefix" FORCE)
		MESSAGE(STATUS "Using install prefix: $ENV{HOME}/lib")
	endif()
endif()
	


set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}) 
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})

set( CMAKE_BUILD_TYPE distribution )
set( CMAKE_CXX_FLAGS_DISTRIBUTION "-O3" )
set( CMAKE_C_FLAGS_DISTRIBUTION "-O3" )
set( CMAKE_C_FLAGS_DEBUG "-g -O0" )
set( CMAKE_CXX_FLAGS_DEBUG "-g -O0" )

include_directories(${CMAKE_CURRENT_LIST_DIR}/src/include) 
add_definitions(-std=c++11 -Wall -Wextra -pedantic)
add_definitions(-include ${CMAKE_CURRENT_LIST_DIR}/src/include/elib/commondef.h)

add_subdirectory(src)
add_subdirectory(tests)


