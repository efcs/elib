cmake_minimum_required (VERSION 2.8)

option(CONFIG_MY_BUILD "These are my specific build settings" ON)

################################################################################
#                     Personal build enviroment configurations                           
################################################################################

if (CONFIG_MY_BUILD)
	
#set(CONFIG_OPT_GCC CLANG)

      
  if(CONFIG_OPT_GCC MATCHES CLANG)

      set(CMAKE_C_COMPILER /usr/bin/clang)
      set(CMAKE_CXX_COMPILER /usr/bin/clang++)
      add_definitions( -ferror-limit=15 )
                       
      add_definitions( -Weverything -Wno-c++98-compat -Wno-c++98-compat-pedantic
                        -Wno-padded
                     )
      
  endif()

  set(CONFIG_GCC_ALL_WARNINGS TRUE)
  if (CONFIG_GCC_ALL_WARNINGS)
    
#add_definitions( -Werror  )
  
    
    add_definitions( -g -O -Wall -Weffc++ -pedantic  
      -pedantic-errors -Wextra  -Wall -Waggregate-return -Wcast-align 
      -Wcast-qual  -Wchar-subscripts  -Wcomment -Wconversion 
      -Wdisabled-optimization 
      -Wfloat-equal  -Wformat  -Wformat=2 
      -Wformat-nonliteral -Wformat-security  
      -Wformat-y2k 
      -Wimport  -Winit-self  -Winline 
      -Winvalid-pch   
      -Wlong-long -Wmissing-braces 
      -Wmissing-field-initializers -Wmissing-format-attribute   
      -Wmissing-include-dirs -Wmissing-noreturn 
      -Wpacked  -Wpadded -Wparentheses  -Wpointer-arith 
      -Wredundant-decls -Wreturn-type 
      -Wsequence-point  -Wshadow -Wsign-compare  -Wstack-protector 
      -Wstrict-aliasing -Wstrict-aliasing=2 -Wswitch  -Wswitch-default 
      -Wswitch-enum -Wtrigraphs  -Wuninitialized 
      -Wunknown-pragmas  -Wunreachable-code -Wunused 
      -Wunused-function  -Wunused-label  -Wunused-parameter 
      -Wunused-value  -Wunused-variable  -Wvariadic-macros 
      -Wvolatile-register-var  -Wwrite-strings
    )
    
    if (NOT (CONFIG_OPT_GCC MATCHES CLANG))
      add_definitions( -Wunsafe-loop-optimizations )
    endif()
    
    add_definitions( -Wno-padded -Wno-aggregate-return -Wno-inline )
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
#add_subdirectory(unit_tests)
#add_subdirectory(test_main)


