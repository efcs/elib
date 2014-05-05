cmake_minimum_required (VERSION 2.7)

if ( WIN32 )
    message( FATAL_ERROR "Windows not supported!" )
endif()

################################################################################
#                            Toolchain config
################################################################################

# C++ Version Config
# NOTE: Default is C++11
option(CONFIG_CXX1Y "Compile using c++1y standard" OFF)

# Adds a ton of warnings to the build. 
# NOTE: ALL CODE SHOULD COMPILE CLEANLY WITH THIS ON!
option(CONFIG_ALL_WARNINGS "Add warnings for GCC/Clang" ON)

# Unsupported configurations should work for most
# libraries. Certain libraries require some configuration macros
# not defined by default.
option(CONFIG_ELIB_ASSERT_CONFIG 
      "Ensure that a elib/config finds a valid configuration" OFF)

# elib is a open source project that uses coverity scan for defect detection.
# Certain parts of elib are unsupported on otherwise buggy for EDG.
# This configures the enviroment to only shouw EDG what it can handle.
option(CONFIG_ELIB_COVERITY_SCAN
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

option(ELIB_ALGORITHM_SOURCE "Build Algorithm" ON)
option(ELIB_AUX_SOURCE "Build aux" ON)
option(ELIB_CMD_OPTIONS_SOURCE "Build command options" ON)
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
option(ELIB_RANGES_SOURCE "Build ranges library" ON)
option(ELIB_WEB_SOURCE "Build web library" ON)

################################################################################
#                            PROJECT ELIB
################################################################################
# need C to get the pthreads library 
project(EricsLibrary CXX C)
set(CONFIG_ELIB_ROOT "${CMAKE_CURRENT_LIST_DIR}")

################################################################################
#                       Toolchain config (Post-project)
################################################################################

if (DEFINED ENV{ELIB_CMAKE_OPTIONS})
    message(STATUS "Configuring with ELIB_CMAKE_OPTIONS: $ENV{ELIB_CMAKE_OPTIONS}")
endif()

if( NOT CMAKE_BUILD_TYPE )
  set( CMAKE_BUILD_TYPE DEBUG CACHE STRING
       "Choose the type of build"
       FORCE )
endif()
set( CMAKE_CXX_FLAGS_RELEASE "-O2 -DNDEBUG" )
set( CMAKE_C_FLAGS_RELEASE "-O2 -DNDEBUG" )
set( CMAKE_C_FLAGS_DEBUG " -g -fno-omit-frame-pointer -DELIB_WARN_ON " )
set( CMAKE_CXX_FLAGS_DEBUG " -g -fno-omit-frame-pointer  -DDELIB_WARN_ON " )
set( CMAKE_C_FLAGS_TEST " -g -fno-omit-frame-pointer  -DDELIB_WARN_ON -fno-elide-constructors -fprofile-arcs -ftest-coverage")
set( CMAKE_CXX_FLAGS_TEST " -g -fno-omit-frame-pointer  -DDELIB_WARN_ON -fno-elide-constructors -fprofile-arcs -ftest-coverage")


message( STATUS "Configuring for Build Type: ${CMAKE_BUILD_TYPE}")

if (NOT CONFIG_CXX1Y)
    message( STATUS "Configuring for Standard: C++11" )
    set(CXX_VERSION_FLAGS " -std=c++11 ")
else()
    message( STATUS "Configuring for Standard: C++1y" )
    set(CXX_VERSION_FLAGS " -std=c++1y ")
endif()

set(CXX_WARNING_FLAGS " -Wall -Wextra -pedantic ")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${CXX_VERSION_FLAGS} ${CXX_WARNING_FLAGS}")

if (DEFINED ENV{CXXFLAGS})
    message(STATUS "Configuring with extra CXX flags: $ENV{CXXFLAGS}")
endif()
if (DEFINED ENV{LDFLAGS})
    message(STATUS "Configuring with extra LD flags: $ENV{LDFLAGS}")
endif()
################################################################################
##                         Compiler Detection
################################################################################
if ( ${CMAKE_CXX_COMPILER_ID} STREQUAL "GNU" )
    message(STATUS "Configuring for Compiler: GCC")
    set( CXX_COMPILER_GCC TRUE )
    set( CXX_COMPILER_CLANG FALSE )
elseif( ${CMAKE_CXX_COMPILER_ID} STREQUAL "Clang" )
    message(STATUS "Configuring for Compiler: Clang")
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
        message(FATAL_ERROR "Insufficient GCC Version")
    endif()
    
    if(CMAKE_CXX_COMPILER_VERSION VERSION_EQUAL "4.9.0"
        OR CMAKE_CXX_COMPILER_VERSION VERSION_GREATER "4.9.0")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}  -fdiagnostics-color=auto ")
    else()
        set(ELIB_WEB_SOURCE OFF CACHE BOOL "Build web library" FORCE)
    endif()

    # Check C++1y config
    if (CONFIG_CXX1Y AND CMAKE_CXX_COMPILER_VERSION VERSION_LESS "4.9.0")
        message(FATAL_ERROR "Insufficient GCC Version for C++1y")
    endif()

    set(CXX_GCC_FLAGS " -fmax-errors=5 " )
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${CXX_GCC_FLAGS}")

elseif( CXX_COMPILER_CLANG ) ###################################################

    if (CMAKE_CXX_COMPILER_VERSION STREQUAL "")
        message(WARNING "Failed to detect clang version")
    elseif (CMAKE_CXX_COMPILER_VERSION VERSION_LESS "3.3")
        message(FATAL_ERROR "Insufficient Clang Version: ${CMAKE_CXX_COMPILER_VERSION} (Requires >= 3.3)")
    endif()

    if (CONFIG_CXX1Y AND CMAKE_CXX_COMPILER_VERSION VERSION_LESS "3.4")
        message(FATAL_ERROR "Insufficient Clang Version for C++1y")
    endif()

    set(CXX_CLANG_FLAGS " -ferror-limit=3 " )
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${CXX_CLANG_FLAGS}")

    string(REPLACE " " ";" CXX_FLAGS_LIST ${CMAKE_CXX_FLAGS})
    list(FIND CXX_FLAGS_LIST "-stdlib=libc++" LIBCXX_FLAG_POS)
    if (LIBCXX_FLAG_POS EQUAL -1)
        set(ELIB_WEB_SOURCE OFF CACHE BOOL "Build web library" FORCE)
    endif()

endif()


#################################################################################
if (CONFIG_ELIB_ASSERT_CONFIG)
    add_definitions( -DELIB_ASSERT_CONFIG )
endif()

if (CONFIG_ELIB_COVERITY_SCAN)
    message( STATUS "Configuring for Coverity Scan")
    add_definitions( -DELIB_CONFIG_COVERITY_SCAN )
   add_definitions( -include config/gcc_4_8_2_coverity_scan_missing_builtins.hpp)
endif()

################################################################################
#                          Build & Installation Config
################################################################################

if(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
    set(CMAKE_INSTALL_PREFIX "/usr" 
        CACHE PATH "library install prefix" FORCE)
    MESSAGE(STATUS "Configuring for Install Prefix: ${CMAKE_INSTALL_PREFIX}")
endif()

set(headerDir ${CMAKE_CURRENT_LIST_DIR}/elib)
include_directories(${CMAKE_CURRENT_LIST_DIR})

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/bin) 
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/bin)

################################################################################
#                           Macros & Functions
################################################################################

macro(set_dot_dir)
    set(dotDir ${CMAKE_CURRENT_LIST_DIR})
endmacro(set_dot_dir)

# Use the library configuration option to selectivly 
# build build a library. 
macro(include_library_if Pred CFile)
    if (${Pred})
        include(${CFile})
        add_definitions( -D${Pred} )
    endif()
endmacro(include_library_if)

macro(include_build_dir BuildDir)
    set_dot_dir()
    include(${dotDir}/${BuildDir}/build.cmake)
endmacro(include_build_dir)

# adds all c++ file in the CWD
macro(add_library_src)
    set_dot_dir()
    if (${ARGC} EQUAL 0)
        aux_source_directory(${dotDir} _library_src)
    elseif(${ARGC} EQUAL 1)
        aux_source_directory(${dotDir}/${ARGV0}/ _library_src)
    else()
        message(FATAL_ERROR "Cannot use macro add_library_src with args ${ARGV}")
    endif()
    list(APPEND LIBRARY_SRC ${_library_src})
endmacro(add_library_src)

macro(add_unit_test_src)
    set_dot_dir()
    if (${ARGC} EQUAL 0)
        message(STATUS "Adding unit tests")
        aux_source_directory(${dotDir} _unit_test_src)
    elseif(${ARGC} EQUAL 1)
        aux_source_directory(${dotDir}/${ARGV0}/ _unit_test_src)
    else()
        message(FATAL_ERROR "Cannot use macro add_unit_test_src with args ${ARGV}")
    endif()
    list(APPEND UNIT_TEST_SRC ${_unit_test_src})
endmacro(add_unit_test_src)

macro(add_header_test_src)
    set_dot_dir()
    if (${ARGC} EQUAL 0)
        aux_source_directory(${dotDir} _header_test_src)
    elseif(${ARGC} EQUAL 1)
        aux_source_directory(${dotDir}/${ARGV0} _header_test_src)
    else()
        message(FATAL_ERROR "Cannot use macro add_header_test_src with args ${ARGV}")
    endif()
    list(APPEND HEADER_TEST_SRC ${_header_test_src})
endmacro(add_header_test_src)



macro(stringify_list m_list dest)
    string(REPLACE ";" " " ${dest} "${m_list}")
endmacro(stringify_list)

macro(add_flags to)
    stringify_list("${ARGN}" _TMP)
    set(${to} "${${to}} ${_TMP}")
endmacro(add_flags)


################################################################################
add_subdirectory(src)
