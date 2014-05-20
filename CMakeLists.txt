cmake_minimum_required (VERSION 2.7)

if ( WIN32 )
    message(FATAL_ERROR "Windows not supported")
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

option(ELIB_SOURCE "Build top level source" ON)
option(ELIB_ALGORITHM_SOURCE "Build Algorithm" ON)
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
option(ELIB_RANGES_SOURCE "Build ranges library" ON)
option(ELIB_WEB_SOURCE "Build web library" ON)

################################################################################
#                            PROJECT ELIB
################################################################################
# need C to get the pthreads library 
project(EricsLibrary CXX C)

include(macros.cmake)
include(configure.cmake)
add_subdirectory(src)
set(CONFIGURATION_DONE ON CACHE BOOL "Configuration has been done" FORCE)
