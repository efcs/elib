cmake_minimum_required (VERSION 2.8)

option(CONFIG_MY_BUILD "These are my specific build settings" ON)

################################################################################
#                     Personal build enviroment configurations                           
################################################################################

if (CONFIG_MY_BUILD)

  set(CONFIG_OPT_GCC 4.8.1)

  if (CONFIG_OPT_GCC MATCHES 4.8.1)
    
      set(CMAKE_C_COMPILER /opt/gnu/bin/gcc)
      set(CMAKE_CXX_COMPILER /opt/gnu/bin/g++)
      set(LD_FLAGS -Wl,-rpath -Wl,/opt/gnu/lib64)
      add_definitions( -fmax-errors=30 )
      
  elseif(CONFIG_OPT_GCC MATCHES 4.9.0)

      set(CMAKE_C_COMPILER /opt/gcc/4.9.0/bin/gcc)
      set(CMAKE_CXX_COMPILER /opt/gcc/4.9.0/bin/g++)
      set(LD_FLAGS -Wl,-rpath -Wl,/opt/gcc/4.9.0/lib64)
      
  elseif(CONFIG_OPT_GCC MATCHES 4.7.3)

      # default compiler 
      add_definitions( -fmax-errors=30 )

  elseif(CONFIG_OPT_GCC MATCHES CLANG)

  ## clang currently doesn't correctly compile std::thread on linux
  ## but the compile messages are so helpful
      set(CMAKE_C_COMPILER /usr/bin/clang)
      set(CMAKE_CXX_COMPILER /usr/bin/clang++)
      add_definitions( -ferror-limit=15)
  ##set(LD_FLAGS -Wl,-rpath -Wl,/opt/gcc/4.9.0/lib64)

  elseif(CONFIG_OPT_GCC)

    set(CMAKE_C_COMPILER /usr/bin/gcc)
    set(CMAKE_CXX_COMPILER /usr/bin/g++)
    
  endif()

endif() # CONFIG_MY_BUILD

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
	
set(CONFIG_BOOST_VERSION 1.52.0)
set(BOOST_DEFAULT_VERSION 1.52.0)

set(CONFIG_BOOST_VERSION_LIST ${BOOST_DEFAULT_VERSION} 
  1.46.1 1.48.0 1.54.0 1.52.0 CACHE
  STRING "available boost versions" FORCE)

if (NOT CONFIG_BOOST_VERSION)
  set(CONFIG_BOOST_VERSION ${BOOST_DEFAULT_VERSION})
endif()

list(FIND CONFIG_BOOST_VERSION_LIST ${CONFIG_BOOST_VERSION} boost_ver_good)
  if (boost_ver_good EQUAL -1)
  message(STATUS "${CONFIG_BOOST_VERSION_LIST}")
  message(FATAL_ERROR "bad boost version: ${CONFIG_BOOST_VERSION}")
endif()

if (NOT CONFIG_BOOST_VERSION MATCHES ${BOOST_DEFAULT_VERSION})
  set(ENV{BOOST_ROOT} /opt/boost-${CONFIG_BOOST_VERSION})
  set(Boost_NO_SYSTEM_PATHS OFF)
endif()


set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREADED OFF)
set(Boost_USE_STATIC_RUNTIME OFF)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/bin) 
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/bin)


set( CMAKE_BUILD_TYPE DEBUG)
set( CMAKE_CXX_FLAGS_RELEASE "-O3  -DNDEBUG " )
set( CMAKE_C_FLAGS_RELEASE "-O3  -DNDEBUG " )
set( CMAKE_C_FLAGS_DEBUG " -g -O0 -DELIB_WARN_ON " )
set( CMAKE_CXX_FLAGS_DEBUG " -g -O0 -DELIB_WARN_ON " )

set(headerDir ${CMAKE_CURRENT_LIST_DIR}/elib)
include_directories(${CMAKE_CURRENT_LIST_DIR})

find_package( Threads REQUIRED )
add_definitions( -std=c++11 -Wall -Wextra -pedantic )
add_definitions( -DELIB_DEFAULT_CONFIG )
add_definitions(-include ${CMAKE_CURRENT_LIST_DIR}/elib/common_def.hpp)

add_subdirectory(src)
add_subdirectory(unit_tests)
add_subdirectory(test_main)


