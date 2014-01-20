cmake_minimum_required (VERSION 2.7)

################################################################################
#                   Toolchain config
################################################################################

# C++ Version Config 
option(CONFIG_CXX1Y "Compile using c++1y standard" OFF)

# Compiler Config
option(CONFIG_USE_CLANG "use clang instead of gcc" OFF)
option(CONFIG_USE_CLANG_34 " use /opt/clang3.4/bin/clang" OFF)
option(CONFIG_USE_GCC_49 "use /opt/gcc4.9/bin/gcc" OFF)

# Standard Library config
option(CONFIG_USE_LIBCXX "if clang is selected,  it will use libc++" OFF)
option(CONFIG_USE_OPT_LIBSTDCXX "use /opt/gcc4.9/lib64" OFF)

# Sanitizers
option(CONFIG_ASAN "address sanitizer" OFF)
option(CONFIG_TSAN "thread sanitizer" OFF)
option(CONFIG_MSAN "memory sanitizer" OFF)

# Misc
option(CONFIG_ALL_WARNINGS "Add warnings for GCC/Clang" ON)

# Elib Parts
option(CONFIG_UNIT_TESTS "build unit tests" ON)

# Options to select what parts to build
option(CONFIG_LIB_FILESYSTEM "Build filesystem" ON)
option(CONFIG_LIB_MPL "Build MPL" ON)
option(CONFIG_LIB_LOG "Build Log" ON)
option(CONFIG_LIB_AUX "Build aux" ON)
option(CONFIG_LIB_ENUMERATION "Build Enumeration" ON)
option(CONFIG_LIB_CEXPR "Build Create Expression Library" ON)
option(CONFIG_LIB_FUNCTIONAL "Build Functional Library" ON)
option(CONFIG_LIB_FUSE "Build Fusion Library" ON)

# Toolchain Configuration
if(CONFIG_USE_CLANG)
    set(CMAKE_C_COMPILER /usr/bin/clang)
    set(CMAKE_CXX_COMPILER /usr/bin/clang++)
endif()
        
if (CONFIG_USE_GCC_49)
    set(CMAKE_C_COMPILER /opt/gcc4.9/bin/gcc)
    set(CMAKE_CXX_COMPILER /opt/gcc4.9/bin/g++)
endif()

if (CONFIG_USE_CLANG_34)
    set(CMAKE_C_COMPILER /opt/clang3.4/bin/clang)
    set(CMAKE_CXX_COMPILER /opt/clang3.4/bin/clang++)
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


