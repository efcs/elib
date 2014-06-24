cmake_minimum_required (VERSION 2.8.11)

include(config/macros.cmake)
include(config/options.cmake)
include(config/library-options.cmake)

################################################################################
#                            PROJECT ELIB
################################################################################
# need C to get the pthreads library 
project(EricsLibrary CXX C)
enable_testing()

# Set configuration variables for elib's root path.
set(ELIB_ROOT_PATH ${CMAKE_CURRENT_LIST_DIR})
include_directories(${ELIB_ROOT_PATH})

# Auto-generated makefile rules should go here.
set(ELIB_MAKEFILE_RULE_PATH ${ELIB_ROOT_PATH}/build/rules/)

# Library configuration variables. These are used to exclude
# libraries and directories from tests.
set(ELIB_LIBRARIES "")
set(ELIB_EXCLUDE_LIBRARIES "")
set(ELIB_EXCLUDE_DIRECTORIES "")
set(ELIB_INCLUDE_DIRECTORIES "")
set(ELIB_AVAILABLE_FEATURES "")

# Include compiler, library, build-type configuration.
include(config/config.cmake)

# Include dependancy configuration.
include(config/depends.cmake)

# Add package configurations.
include(packages/lit.cmake)
include(packages/rapid-cxx-test.cmake)

# Test-suite configuration variables. To add a test-suite to check-all
# You must add the directory of its lit.site.cfg to ELIB_TEST_SUITES
# and add its dependancies to check-all-depends
set(ELIB_TEST_SUITES "")
add_custom_target(check-all-depends)

add_subdirectory(src)
add_subdirectory(header_tests)

# Add a check-all Makefile rule if we have a python interpreter
if (PYTHONINTERP_FOUND)
    configure_file(
        ${ELIB_ROOT_PATH}/config/check-all.mk.in
        ${ELIB_MAKEFILE_RULE_PATH}/check-all.mk
        @ONLY)
endif()


# NOTE: This should be the last line of this file.
# When reconfiguring CMake some commands are noisy. We only need information
# about build configuration to be printed the first time cmake is run. 
# This variable is put in the cache to signal that CMake has completed its
# configuration step.
set(CONFIGURATION_DONE ON CACHE BOOL "Configuration has been done" FORCE)