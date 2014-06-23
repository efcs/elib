cmake_minimum_required (VERSION 2.8.11)

include(cmake/macros.cmake)
include(cmake/options.cmake)
include(cmake/library-options.cmake)

################################################################################
#                            PROJECT ELIB
################################################################################
# need C to get the pthreads library 
project(EricsLibrary CXX C)
enable_testing()

set(ELIB_ROOT_PATH ${CMAKE_CURRENT_LIST_DIR})
set(ELIB_MAKEFILE_RULE_PATH ${ELIB_ROOT_PATH}/build/rules/)
add_definitions(-DELIB_ROOT_PATH="${ELIB_ROOT_PATH}")
include_directories(${ELIB_ROOT_PATH})

include(cmake/config.cmake)
include(cmake/depends.cmake)

set(ELIB_TEST_SUITES "")
set(ELIB_EXCLUDE_DIRECTORIES "")
set(ELIB_INCLUDE_DIRECTORIES "")
add_custom_target(check-all-depends)

add_subdirectory(src)
add_subdirectory(header_tests)

configure_file(
    ${ELIB_ROOT_PATH}/cmake/check-all.mk.in
    ${ELIB_ROOT_PATH}/build/rules/check-all.mk
    @ONLY)


# NOTE: This should be the last line of this file.
# When reconfiguring CMake some commands are noisy. We only need information
# about build configuration to be printed the first time cmake is run. 
# This variable is put in the cache to signal that CMake has completed its
# configuration step.
set(CONFIGURATION_DONE ON CACHE BOOL "Configuration has been done" FORCE)