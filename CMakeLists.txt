cmake_minimum_required (VERSION 2.8)

option(CONFIG_MY_BUILD "turn on personal configurations" ON)

option(CONFIG_USE_CLANG "use clang instead of gcc" ON)

option(CONFIG_NO_LIBRARIES "only produce the object files for /src. useful for
                              when you don't want to link against a library
                              e.g. clang's sanatizers" OFF)
                              
option(CONFIG_CLANG_ASAN "compile and link elib_boost_test_main using boost
                            address sanitizer" OFF)

option(CONFIG_CLANG_TSAN "use clangs thread sanitizer" OFF)
option(CONFIG_CLANG_MSAN "clangs memory sanitizer" OFF)
                            
option(CONFIG_ALL_WARNINGS "turn on all warnings for either GCC on clang" OFF)


#set(CONFIG_CLANG_ASAN ON CACHE BOOL "" FORCE)

  
if (CONFIG_CLANG_ASAN)
  set(CONFIG_USE_CLANG ON CACHE BOOL "" FORCE)
  set(CONFIG_NO_LIBRARIES ON CACHE BOOL "" FORCE)
  set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} " -O1 -fsanitize=address ")
endif()

if (CONFIG_CLANG_TSAN)
   set(CONFIG_USE_CLANG ON CACHE BOOL "" FORCE)
  set(CONFIG_NO_LIBRARIES ON CACHE BOOL "" FORCE)
  set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} " -fsanitize=thread ")
endif() 

if (CONFIG_CLANG_MSAN)
   set(CONFIG_USE_CLANG ON CACHE BOOL "" FORCE)
  set(CONFIG_NO_LIBRARIES ON CACHE BOOL "" FORCE)
#set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} -fmemory-saniziter )
  set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} " -O2 -fsanitize=memory -fno-omit-frame-pointer ")
endif() 
      
if(CONFIG_USE_CLANG)
    set(CMAKE_C_COMPILER /usr/bin/clang)
    set(CMAKE_CXX_COMPILER /usr/bin/clang++)
endif()


################################################################################
#                         PROJECT ELIB
################################################################################

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
	
	
################################################################################
#                             BOOST Version Configuration
################################################################################
	
set(CONFIG_BOOST_VERSION 1.54.0)

set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREADED OFF)
set(Boost_USE_STATIC_RUNTIME OFF)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/bin) 
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/bin)


set( CMAKE_BUILD_TYPE DEBUG)
set( CMAKE_CXX_FLAGS_RELEASE "-O3  -DNDEBUG " )
set( CMAKE_C_FLAGS_RELEASE "-O3  -DNDEBUG " )
set( CMAKE_C_FLAGS_DEBUG " -g -DELIB_WARN_ON " )
set( CMAKE_CXX_FLAGS_DEBUG " -g -DDELIB_WARN_ON " )

set(headerDir ${CMAKE_CURRENT_LIST_DIR}/elib)
include_directories(${CMAKE_CURRENT_LIST_DIR})

find_package( Threads REQUIRED )
add_definitions( -std=c++11 -Wall -Wextra -pedantic )
add_definitions( -DELIB_DEFAULT_CONFIG )
add_definitions(-include ${CMAKE_CURRENT_LIST_DIR}/elib/common_def.hpp)

add_subdirectory(src)
add_subdirectory(unit_tests)
#add_subdirectory(test_main)


