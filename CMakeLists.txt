cmake_minimum_required (VERSION 2.8.8)

include(macros.cmake)

if ( WIN32 )
    message(FATAL_ERROR "Windows not supported")
endif()

################################################################################
#                            Toolchain config
################################################################################

# C++ Version Config
# NOTE: Default is C++11
option(CONFIG_CXX1Y "Compile using c++1y standard" OFF)

# Enable experimental libraries
option(CONFIG_ENABLE_EXPERIMENTAL "Enable experimental libraries" ON)

# Adds a ton of warnings to the build. 
# NOTE: ALL CODE SHOULD COMPILE CLEANLY WITH THIS ON!
option(CONFIG_ALL_WARNINGS "Add warnings for GCC/Clang" ON)

# Unsupported configurations should work for most
# libraries. Certain libraries require some configuration macros
# not defined by default.
option(CONFIG_ELIB_ASSERT_CONFIG 
      "Ensure that a elib/config finds a valid configuration" ON)

# elib is a open source project that uses coverity scan for defect detection.
# Certain parts of elib are unsupported on otherwise buggy for EDG.
# This configures the enviroment to only shouw EDG what it can handle.
option(CONFIG_COVERITY_SCAN
      "Setup build for when doing a build with coverity scan" OFF)

# Unit tests require the boost test library.
# And a version that also uses the configured standard library
option(CONFIG_UNIT_TESTS "build unit tests" ON)

# Source files in header only source directories are uneeded.
# When this option is on those files are removed from the build.
# The disadvantage of this is it does not perform any include tests
# on the build but the build is MUCH faster.
option(CONFIG_HEADER_TESTS
        " Build source files that simple include the matching header.
          This is used in  header only librarys to check for errors" OFF)

################################################################################
##                         Library Parts                                      ##
################################################################################
# NOTE There are top level files that are not a member of any library part
# config, any, fmt, lexical_cast, scope_guard are some examples.

option(ELIB_SOURCE "Build top level source" ON)
option(ELIB_AUX_SOURCE "Build aux" ON)
option(ELIB_CONTAINER_SOURCE "Build containers" ON)
option(ELIB_ENUMERATION_SOURCE "Build enumeration" ON)
option(ELIB_EXCEPTION_SOURCE "Build except" ON)
option(ELIB_FILESYSTEM_SOURCE "Build filesystem" ON)
option(ELIB_FUNCTIONAL_SOURCE "Build functional" ON)
option(ELIB_ITERATOR_SOURCE "Build iterators" ON)
option(ELIB_LOGGING_SOURCE "Build logging library" ON)
option(ELIB_MEMORY_SOURCE "Build memory library" ON)
option(ELIB_MP_SOURCE "Build metaprogramming library" ON)
option(ELIB_PP_SOURCE "Build preprocessor library" ON)


# Experimental libraries
option(ELIB_CONTRACT_ASSERT_SOURCE "Build contract assert source" ON)
option(ELIB_WEB_SOURCE "Build web library (experimental)" ON)

################################################################################
#                            PROJECT ELIB
################################################################################
# need C to get the pthreads library 
project(EricsLibrary CXX C)

################################################################################
#                            ELIB config
################################################################################
set(ELIB_ROOT_PATH "${CMAKE_CURRENT_LIST_DIR}")
add_definitions(-DELIB_ROOT_PATH="${ELIB_ROOT_PATH}")

include_directories(${CMAKE_CURRENT_LIST_DIR})

if (CONFIG_ELIB_ASSERT_CONFIG)
    add_definitions( -DELIB_ASSERT_CONFIG )
endif()

if (CONFIG_COVERITY_SCAN)
    config_message( STATUS "Configuring for Coverity Scan")
    add_definitions( -DELIB_CONFIG_COVERITY_SCAN )
endif()

################################################################################
#                                Build Type Config
################################################################################
if( NOT CMAKE_BUILD_TYPE )
  set( CMAKE_BUILD_TYPE DEBUG CACHE STRING
       "Choose the type of build"
       FORCE )
endif()
set( CMAKE_CXX_FLAGS_RELEASE "-O2 -DNDEBUG" )
set( CMAKE_C_FLAGS_RELEASE "-O2 -DNDEBUG" )
set( CMAKE_C_FLAGS_DEBUG " -g -fno-omit-frame-pointer -DELIB_WARN_ON " )
set( CMAKE_CXX_FLAGS_DEBUG " -g -fno-omit-frame-pointer -DDELIB_WARN_ON " )
set( CMAKE_C_FLAGS_TEST "-v -g -O0 -fno-omit-frame-pointer -DDELIB_WARN_ON -fno-elide-constructors --coverage")
set( CMAKE_CXX_FLAGS_TEST "-v -g -O0 -fno-omit-frame-pointer -DDELIB_WARN_ON -fno-elide-constructors --coverage")


if (DEFINED ENV{ELIB_CMAKE_OPTIONS})
    config_message(STATUS "Configuring with ELIB_CMAKE_OPTIONS: $ENV{ELIB_CMAKE_OPTIONS}")
endif()

config_message( STATUS "Configuring for Build Type: ${CMAKE_BUILD_TYPE}")

if (NOT CONFIG_CXX1Y)
    config_message( STATUS "Configuring for Standard: C++11" )
    set(CXX_VERSION_FLAGS " -std=c++11 ")
else()
    config_message( STATUS "Configuring for Standard: C++1y" )
    set(CXX_VERSION_FLAGS " -std=c++1y ")
endif()

set(CXX_WARNING_FLAGS " -Wall -Wextra -pedantic ")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${CXX_VERSION_FLAGS} ${CXX_WARNING_FLAGS}")

if (DEFINED ENV{CXXFLAGS})
   config_message(STATUS "Configuring with extra CXX flags: $ENV{CXXFLAGS}")
endif()
if (DEFINED ENV{LDFLAGS})
    config_message(STATUS "Configuring with extra LD flags: $ENV{LDFLAGS}")
endif()

################################################################################
##                         Compiler Detection
################################################################################
if ( ${CMAKE_CXX_COMPILER_ID} STREQUAL "GNU" )
    config_message(STATUS "Configuring for Compiler: GCC")
    set( CXX_COMPILER_GCC TRUE )
    set( CXX_COMPILER_CLANG FALSE )
elseif( ${CMAKE_CXX_COMPILER_ID} STREQUAL "Clang" )
    config_message(STATUS "Configuring for Compiler: Clang")
    set( CXX_COMPILER_GCC FALSE )
    set( CXX_COMPILER_CLANG TRUE )
else()
    message( FATAL_ERROR "Compiler not supported! (${CMAKE_CXX_COMPILER_ID})" )
endif()


################################################################################
##                        Compiler Configuration
################################################################################
if ( CXX_COMPILER_GCC )
   
    # check min version
    if (CMAKE_CXX_COMPILER_VERSION VERSION_LESS "4.8.0")
        message(WARNING "Insufficient GCC Version")
    endif()
    
    if(CMAKE_CXX_COMPILER_VERSION VERSION_EQUAL "4.9.0"
        OR CMAKE_CXX_COMPILER_VERSION VERSION_GREATER "4.9.0")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}  -fdiagnostics-color=auto ")
    else()
        set(ELIB_WEB_SOURCE OFF CACHE BOOL "Build web library" FORCE)
    endif()

    set(CXX_GCC_FLAGS " -fmax-errors=5 " )
    if (DEFINED ENV{TRAVIS})
        set(CXX_GCC_FLAGS "${CXX_GCC_FLAGS} -Werror")
    endif()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${CXX_GCC_FLAGS}")

elseif( CXX_COMPILER_CLANG ) ###################################################

    if (CONFIG_CXX1Y AND CMAKE_CXX_COMPILER_VERSION VERSION_LESS "3.4")
        message(FATAL_ERROR "Insufficient Clang Version for C++1y")
    endif()

    set(CXX_CLANG_FLAGS " -ferror-limit=3 " )

    if (DEFINED ENV{TRAVIS})
        set(CXX_CLANG_FLAGS "${CXX_CLANG_FLAGS} -Werror -Wno-mismatched-tags -Wno-old-style-cast")
    endif()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${CXX_CLANG_FLAGS}")

    string(REPLACE " " ";" CXX_FLAGS_LIST ${CMAKE_CXX_FLAGS})
    list(FIND CXX_FLAGS_LIST "-stdlib=libc++" LIBCXX_FLAG_POS)
    if (LIBCXX_FLAG_POS EQUAL -1)
        set(ELIB_WEB_SOURCE OFF CACHE BOOL "Build web library" FORCE)
    endif()

endif()

################################################################################
#                          Build & Installation Config
################################################################################

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/bin) 
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/bin)

################################################################################
add_subdirectory(src)

################################################################################
set(CONFIGURATION_DONE ON CACHE BOOL "Configuration has been done" FORCE)