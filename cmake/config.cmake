################################################################################
#                                Build Type Config
################################################################################
if( NOT CMAKE_BUILD_TYPE )
  set( CMAKE_BUILD_TYPE DEBUG CACHE STRING
       "Choose the type of build"
       FORCE )
endif()

config_message( STATUS "Configuring for Build Type: ${CMAKE_BUILD_TYPE}")

set( CMAKE_CXX_FLAGS_RELEASE "-O2 -DNDEBUG" )
set( CMAKE_C_FLAGS_RELEASE "-O2 -DNDEBUG" )
set( CMAKE_C_FLAGS_DEBUG " -g -fno-omit-frame-pointer -DELIB_WARN_ON " )
set( CMAKE_CXX_FLAGS_DEBUG " -g -fno-omit-frame-pointer -DDELIB_WARN_ON " )
set( CMAKE_C_FLAGS_TEST " -g -O0 -fno-omit-frame-pointer -DDELIB_WARN_ON -fno-elide-constructors --coverage")
set( CMAKE_CXX_FLAGS_TEST " -g -O0 -fno-omit-frame-pointer -DDELIB_WARN_ON -fno-elide-constructors --coverage")


set(CXX_WARNING_FLAGS " -Wall -Wextra -pedantic ")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${CXX_VERSION_FLAGS} ${CXX_WARNING_FLAGS}")


################################################################################
##                         Compiler Config
################################################################################
if ( ${CMAKE_CXX_COMPILER_ID} STREQUAL "GNU" )
    include(cmake/gcc-config.cmake)
elseif( ${CMAKE_CXX_COMPILER_ID} STREQUAL "Clang" )
    include(cmake/clang-config.cmake)
else()
    message( FATAL_ERROR "Compiler not supported! (${CMAKE_CXX_COMPILER_ID})" )
endif()

if (CONFIG_ALL_WARNINGS)
    include(cmake/warning-flags.cmake)
endif()

################################################################################
#                          Environment Configuration
################################################################################

if ( WIN32 )
    message(FATAL_ERROR "Windows not supported")
elseif(CYGWIN)
    include(cmake/cygwin-config.cmake)
endif()

# Travis CI enviroment specific configuration.
if (DEFINED ENV{TRAVIS})
    include(cmake/travis-config.cmake)
endif()


################################################################################
#                       Enviroment Variables
################################################################################
if (DEFINED ENV{CXXFLAGS})
    config_message(STATUS "Configuring with CXXFLAGS: $ENV{CXXFLAGS}")
endif()

if (DEFINED ENV{LDFLAGS})
    config_message(STATUS "Configuring with LDFLAGS: $ENV{LDFLAGS}")
endif()

