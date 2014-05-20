
set(ELIB_ROOT_PATH "${CMAKE_CURRENT_LIST_DIR}")
add_definitions(-DELIB_ROOT_PATH="${ELIB_ROOT_PATH}")


################################################################################
#                       Toolchain config (Post-project)
################################################################################

if (DEFINED ENV{ELIB_CMAKE_OPTIONS})
    config_message(STATUS "Configuring with ELIB_CMAKE_OPTIONS: $ENV{ELIB_CMAKE_OPTIONS}")
endif()

if( NOT CMAKE_BUILD_TYPE )
  set( CMAKE_BUILD_TYPE DEBUG CACHE STRING
       "Choose the type of build"
       FORCE )
endif()
set( CMAKE_CXX_FLAGS_RELEASE "-O3 -DNDEBUG" )
set( CMAKE_C_FLAGS_RELEASE "-O3 -DNDEBUG" )
set( CMAKE_C_FLAGS_DEBUG " -g -fno-omit-frame-pointer -DELIB_WARN_ON " )
set( CMAKE_CXX_FLAGS_DEBUG " -g -fno-omit-frame-pointer -DDELIB_WARN_ON " )
set( CMAKE_C_FLAGS_TEST "-g -O0 -fno-omit-frame-pointer -DDELIB_WARN_ON -fno-elide-constructors --coverage")
set( CMAKE_CXX_FLAGS_TEST "-g -O0 -fno-omit-frame-pointer -DDELIB_WARN_ON -fno-elide-constructors --coverage")


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

if (CONFIG_COVERITY_SCAN)
    config_message( STATUS "Configuring for Coverity Scan")
    add_definitions( -DELIB_CONFIG_COVERITY_SCAN )
endif()

################################################################################
#                          Build & Installation Config
################################################################################

set(headerDir ${CMAKE_CURRENT_LIST_DIR}/elib)
include_directories(${CMAKE_CURRENT_LIST_DIR})

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/bin) 
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/bin)
