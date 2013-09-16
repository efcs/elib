cmake_minimum_required (VERSION 2.8)

option(CONFIG_MY_BUILD "These are my specific build settings" ON)

################################################################################
#                     Personal build enviroment configurations                           
################################################################################
set(CONFIG_OPT_GCC 4.7.3)
if (CONFIG_OPT_GCC MATCHES 4.8.1)
    set(CMAKE_C_COMPILER /opt/gnu/bin/gcc)
    set(CMAKE_CXX_COMPILER /opt/gnu/bin/g++)
    set(LD_FLAGS -Wl,-rpath -Wl,/opt/gnu/lib64)
    add_definitions( -fmax-errors=10 )
elseif(CONFIG_OPT_GCC MATCHES 4.9.0)
    set(CMAKE_C_COMPILER /opt/gcc/4.9.0/bin/gcc)
    set(CMAKE_CXX_COMPILER /opt/gcc/4.9.0/bin/g++)
    set(LD_FLAGS -Wl,-rpath -Wl,/opt/gcc/4.9.0/lib64)
    add_definitions( -fmax-errors=10 )
elseif(CONFIG_OPT_GCC MATCHES 4.7.3)
# default compiler 
    add_definitions( -fmax-errors=10 )
elseif(CONFIG_OPT_GCC MATCHES CLANG)
    set(CMAKE_C_COMPILER /usr/bin/clang)
    set(CMAKE_CXX_COMPILER /usr/bin/clang++)
    add_definitions( -ferror-limit=5)
    set(LD_FLAGS -Wl,-rpath -Wl,/opt/gcc/4.9.0/lib64)
elseif(CONFIG_OPT_GCC)
    message(FATAL_ERROR "${CONFIG_OPT_GCC} is not a valid value for CONFIG_OPT_GCC")
endif()


# we need C to get the pthreads library 
project(EricsLibrary CXX C)

if (CONFIG_MY_BUILD)
	# I like to install in weird places 
	if(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
		set(CMAKE_INSTALL_PREFIX "/usr" 
			CACHE PATH "library install prefix" FORCE)
		MESSAGE(STATUS "Using install prefix: ${CMAKE_INSTALL_PREFIX}")
	endif()
endif()
	

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/bin) 
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/bin)


set( CMAKE_BUILD_TYPE DEBUG)
set( CMAKE_CXX_FLAGS_RELEASE "-O3  -DNDEBUG" )
set( CMAKE_C_FLAGS_RELEASE "-O3  -DNDEBUG" )
set( CMAKE_C_FLAGS_DEBUG " -g -O0 " )
set( CMAKE_CXX_FLAGS_DEBUG " -g -O0 " )

set(headerDir ${CMAKE_CURRENT_LIST_DIR}/elib)
include_directories(${CMAKE_CURRENT_LIST_DIR})

find_package( Threads REQUIRED )
add_definitions(-std=c++11 -Wall -Wextra -pedantic)
add_definitions(-include ${CMAKE_CURRENT_LIST_DIR}/elib/common_def.hpp)

add_subdirectory(src)
add_subdirectory(unit_tests)
add_subdirectory(test_main)


