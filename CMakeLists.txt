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
option(CONFIG_HEADER_ONLY_SOURCE
        " Build source files for header-only libraries. 
         The source files are usually just include tests. " OFF)

################################################################################
##                         Library Parts                                      ##
################################################################################
# NOTE There are top level files that are not a member of any library part
# config, any, fmt, lexical_cast, scope_guard are some examples.

# TODO aux is header only and turning this option off doesn't do anything
# except turn the unit tests off
option(CONFIG_LIB_AUX "Build Aux" ON)

# Containers and adapters
option(CONFIG_LIB_CONTAINER "Build containers" ON)

# header only. I don't think any other library has mp as dependency.
option(CONFIG_LIB_MPL "Build MPL" ON)

# header only. log uses enumeration when available
# disabling this library disables the log::log_level enum <-> string casting
option(CONFIG_LIB_ENUMERATION "Build Enumeration" ON)

option(CONFIG_LIB_RANGES "Build Range" ON)
option(CONFIG_LIB_ITER "Build Iterator" ON)

# header only. function objects for operators and more
option(CONFIG_LIB_FUNCTIONAL "Build Functional Library" ON)

# header only. pair and tuple
option(CONFIG_LIB_TUPLE "Build Tuple Library" ON)

# requires linkage. 
option(CONFIG_LIB_FILESYSTEM "Build filesystem" ON)

# requires linkage. Log is fairly stable
option(CONFIG_LIB_LOGGING "Build Logging library" ON)

# header only. 
option(CONFIG_LIB_EXCEPT "Build Exception Library" ON)

# Work in progress. Set to ON because it shouldn't break the build
option(CONFIG_LIB_OPTIONS "Build Program Options Library" ON)

# off until GCC supports regex
option(CONFIG_LIB_WEB "Build Web/Socket Library" OFF)

# Stub. Fuse is currently empty
option(CONFIG_LIB_FUSE "Build Fusion Library" OFF)

# Stub. cexpr is currently empty
option(CONFIG_LIB_CEXPR "Build Create Expression Library" OFF)

################################################################################
#                            PROJECT ELIB
################################################################################
# need C to get the pthreads library 
project(EricsLibrary CXX C)
set(CONFIG_ELIB_ROOT "${CMAKE_CURRENT_LIST_DIR}")

################################################################################
#                       Toolchain config (Post-project)
################################################################################

message(STATUS "Configuring for linker: ${CMAKE_LINKER}")

if( NOT CMAKE_BUILD_TYPE )
  set( CMAKE_BUILD_TYPE DEBUG CACHE STRING
       "Choose the type of build"
       FORCE )
endif()
set( CMAKE_CXX_FLAGS_RELEASE "-O2" )
set( CMAKE_C_FLAGS_RELEASE "-O2" )
set( CMAKE_C_FLAGS_DEBUG " -g -fno-omit-frame-pointer -DELIB_WARN_ON " )
set( CMAKE_CXX_FLAGS_DEBUG " -g -fno-omit-frame-pointer  -DDELIB_WARN_ON " )

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
    elseif(CMAKE_CXX_COMPILER_VERSION VERSION_EQUAL "4.9.0"
        OR CMAKE_CXX_COMPILER_VERSION VERSION_GREATER "4.9.0")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}  -fdiagnostics-color=auto ")
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

# adds all c++ file in the CWD
macro(add_library_src)
    set_dot_dir()
    aux_source_directory(${dotDir} _src)
    list(APPEND LIBRARY_SRC ${_src})
endmacro(add_library_src)

# expect /unit_tests in CWD
macro(add_unit_test_src)
    set_dot_dir()
    aux_source_directory(${dotDir}/unit_tests _test)
    list(APPEND UNIT_TEST_SRC ${_test})
endmacro(add_unit_test_src)

# Always add source and unit tests
macro(add_src)
    add_library_src()
    add_unit_test_src()
endmacro(add_src)

# add source files to build only when
# the build is configured for header only source
# always add unit tests
macro(add_header_only_src)
    if (CONFIG_HEADER_ONLY_SOURCE)
        add_library_src()
    endif()
    add_unit_test_src()
endmacro(add_header_only_src)

macro(stringify_list m_list dest)
    string(REPLACE ";" " " ${dest} "${m_list}")
endmacro(stringify_list)

macro(add_flags to)
    stringify_list("${ARGN}" _TMP)
    set(${to} "${${to}} ${_TMP}")
endmacro(add_flags)

# Use the library configuration option to selectivly 
# build build a library. 
macro(include_library_if Pred CFile)
    if (${Pred})
        include(${CFile})
        add_definitions( -DELIB_${Pred} )
    endif()
endmacro(include_library_if)
################################################################################


add_subdirectory(src)
#add_subdirectory(test_main)
