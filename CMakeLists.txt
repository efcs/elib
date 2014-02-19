cmake_minimum_required (VERSION 2.7)

################################################################################
#                   Toolchain config
################################################################################

# C++ Version Config 
option(CONFIG_CXX1Y "Compile using c++1y standard" OFF)

# Compiler Config
option(CONFIG_USE_CLANG "use clang instead of gcc" OFF)

# Standard Library config
option(CONFIG_USE_LIBCXX "if clang is selected,  it will use libc++" OFF)
option(CONFIG_USE_OPT_LIBSTDCXX "use /opt/gcc4.9/lib64" OFF)

# Sanitizers
option(CONFIG_ASAN "address sanitizer" OFF)
option(CONFIG_TSAN "thread sanitizer" OFF)
option(CONFIG_MSAN "memory sanitizer" OFF)

# Misc
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

# TODO aux is header only and turning this option off doesn't do anything
# except turn the unit tests off
option(CONFIG_LIB_AUX "Build Aux" ON)

# header only. I don't think any other library has mp as dependency.
option(CONFIG_LIB_MPL "Build MPL" ON)

# header only. log uses enumeration when available
# disabling this library disables the log::log_level enum <-> string casting
option(CONFIG_LIB_ENUMERATION "Build Enumeration" ON)

# header only. function objects for operators and more
option(CONFIG_LIB_FUNCTIONAL "Build Functional Library" ON)

# header only. pair and tuple
option(CONFIG_LIB_TUPLE "Build Tuple Library" ON)

# requires linkage. 
option(CONFIG_LIB_FILESYSTEM "Build filesystem" ON)

# requires linkage. Log is fairly stable
option(CONFIG_LIB_LOG "Build Log" ON)

# Work in progress. Set to ON because it shouldn't break the build
option(CONFIG_LIB_OPTIONS "Build Program Options Library" ON)

# Work in progress. Set to ON because it shouldn't break the build
option(CONFIG_LIB_EXCEPT "Build Exception Library" ON)

# off until GCC supports regex
option(CONFIG_LIB_WEB "Build Web/Socket Library" OFF)

# Stub. Fuse is currently empty
option(CONFIG_LIB_FUSE "Build Fusion Library" OFF)

# Stub. cexpr is currently empty
option(CONFIG_LIB_CEXPR "Build Create Expression Library" OFF)


# Toolchain Configuration
# DEPRECATED Environment variables ore the preferred method of setting
# the compiler. 
if(CONFIG_USE_CLANG)
    set(CMAKE_C_COMPILER /usr/bin/clang)
    set(CMAKE_CXX_COMPILER /usr/bin/clang++)
endif()

################################################################################
#                         PROJECT ELIB
################################################################################

# need C to get the pthreads library 
project(EricsLibrary CXX C)

################################################################################
#                       Toolchain config (Post-project)
################################################################################

set( CMAKE_BUILD_TYPE DEBUG )

if (CONFIG_ELIB_ASSERT_CONFIG)
    add_definitions( -DELIB_ASSERT_CONFIG=1 )
endif()

if (CONFIG_ELIB_COVERITY_SCAN)
    add_definitions( -DELIB_CONFIG_COVERITY_SCAN=1 )
    add_definitions( -include config/gcc_4_8_2_coverity_scan_missing_builtins.hpp)
endif()

if ( WIN32 )
    message( FATAL_ERROR "Windows not supported!" )
endif()

if ( ${CMAKE_CXX_COMPILER_ID} STREQUAL "GNU" )
    message(STATUS "Configuring for GCC")
    set( CXX_COMPILER_GCC TRUE )
    set( CXX_COMPILER_CLANG FALSE )
elseif( ${CMAKE_CXX_COMPILER_ID} STREQUAL "Clang" )
    message(STATUS "Configuring for Clang")
    set( CXX_COMPILER_GCC FALSE )
    set( CXX_COMPILER_CLANG TRUE )
else()
    message( FATAL_ERROR "Compiler not supported! (${CMAKE_CXX_COMPILER_ID})" )
endif()
# Flag Config
if (NOT CONFIG_CXX1Y)
    set(CXX_VERSION_FLAGS " -std=c++11 ")
else()
    message( STATUS "Using c++1y standard")
    set(CXX_VERSION_FLAGS " -std=c++1y ")
endif()

set(CXX_WARNING_FLAGS " -Wall -Wextra -pedantic ")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${CXX_VERSION_FLAGS} ${CXX_WARNING_FLAGS}")

if ( CONFIG_ASAN OR CONFIG_TSAN OR CONFIG_MSAN )
    if (NOT CMAKE_BUILD_TYPE MATCHES "DEBUG")
        message( WARNING "Build configuration forced to DEBUG when using sanitizers")
    endif()
    set(CMAKE_BUILD_TYPE DEBUG CACHE STRING "Build configuration" FORCE)
endif()


if ( CXX_COMPILER_GCC )
    # check min version
    if (CMAKE_CXX_COMPILER_VERSION VERSION_LESS "4.8.0")
        message(FATAL_ERROR "Insufficient GCC Version")
    elseif(CMAKE_CXX_COMPILER_VERSION VERSION_GREATER "4.9.0")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}  -fdiagnostics-color=auto ")
    endif()
    # Check C++1y config
    if (CONFIG_CXX1Y AND CMAKE_CXX_COMPILER_VERSION VERSION_LESS "4.9.0")
        message(FATAL_ERROR "Insufficient GCC Version for C++1y")
    endif()
    set(CXX_GCC_FLAGS " -fmax-errors=3 " )
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${CXX_GCC_FLAGS}")
elseif( CXX_COMPILER_CLANG )
    if (CMAKE_CXX_COMPILER_VERSION VERSION_LESS "3.3")
        message(FATAL_ERROR "Insufficient Clang Version")
    endif()
    if (CONFIG_CXX1Y AND CMAKE_CXX_COMPILER_VERSION VERSION_LESS "3.4")
        message(FATAL_ERROR "Insufficient Clang Version for C++1y")
    endif()
    set(CXX_CLANG_FLAGS " -ferror-limit=3 " )
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${CXX_CLANG_FLAGS}")
endif()


if (CONFIG_USE_LIBCXX)
    if (NOT CXX_COMPILER_CLANG)
        message( FATAL_ERROR "Cannot use libc++ with GNU" )
    endif()
    message( STATUS "Using libc++ with Clang" )
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}  -stdlib=libc++ ")
endif()

# Currently only GCC's libstdc++ works with -std=c++1y
if (CONFIG_USE_OPT_LIBSTDCXX OR CONFIG_CXX1Y)
    message( STATUS "Using libstdc++ in /opt/gcc4.9/lib64" )
    add_definitions( -nostdinc++ )
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -I/opt/gcc4.9/include/c++/4.9.0/x86_64-unknown-linux-gnu/ -I/opt/gcc4.9/include/c++/4.9.0/")
    set(STDLIB_LINK "-L/opt/gcc4.9/lib64 -Wl,-rpath -Wl,/opt/gcc4.9/lib64")
endif()


if (CONFIG_ASAN)
  message( STATUS "Compiling with address sanitizer")
  set(CONFIG_NO_LIBRARIES ON CACHE BOOL "" FORCE)
  set(CMAKE_CXX_FLAGS  " ${CMAKE_CXX_FLAGS} -fsanitize=address ")
endif()


if (CONFIG_TSAN)
  message( STATUS "Compiling with thread sanitizer")
  set(CONFIG_NO_LIBRARIES ON CACHE BOOL "" FORCE)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}  -fsanitize=thread ")
endif() 


if (CONFIG_MSAN)
  message( STATUS "Compiling with memory sanitizer")
  set(CONFIG_NO_LIBRARIES ON CACHE BOOL "" FORCE)
  set(CMAKE_CXX_FLAGS " ${CMAKE_CXX_FLAGS} -fsanitize=memory ")
endif() 

set( CMAKE_CXX_FLAGS_RELEASE "-O3  -DNDEBUG " )
set( CMAKE_C_FLAGS_RELEASE "-O3  -DNDEBUG " )
set( CMAKE_C_FLAGS_DEBUG " -g -fno-omit-frame-pointer -DELIB_WARN_ON " )
set( CMAKE_CXX_FLAGS_DEBUG " -g -fno-omit-frame-pointer  -DDELIB_WARN_ON " )

################################################################################
#                          Build & Installation Config
################################################################################

if(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
    set(CMAKE_INSTALL_PREFIX "/usr" 
        CACHE PATH "library install prefix" FORCE)
    MESSAGE(STATUS "Using install prefix: ${CMAKE_INSTALL_PREFIX}")
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

macro(add_library_src)
    set_dot_dir()
    aux_source_directory(${dotDir} _src)
    list(APPEND LIBRARY_SRC ${_src})
endmacro(add_library_src)

macro(add_unit_test_src)
    set_dot_dir()
    aux_source_directory(${dotDir}/unit_tests _test)
    list(APPEND UNIT_TEST_SRC ${_test})
endmacro(add_unit_test_src)

macro(add_src)
    add_library_src()
    add_unit_test_src()
endmacro(add_src)

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

macro(include_library_if Pred CFile)
    if (${Pred})
        include(${CFile})
        add_definitions( -DELIB_${Pred} )
    endif()
endmacro(include_library_if)

################################################################################
#
################################################################################

add_subdirectory(src)
#add_subdirectory(test_main)


