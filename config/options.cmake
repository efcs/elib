
################################################################################
# C++ Version Config
# NOTE: Default is C++11
option(CONFIG_CXX1Y "Compile using c++1y standard" OFF)

if (NOT CONFIG_CXX1Y)
    config_message( STATUS "Configuring for Standard: C++11" )
    set(CXX_VERSION_FLAGS " -std=c++11 " )
else()
    config_message( STATUS "Configuring for Standard: C++1y" )
    set(CXX_VERSION_FLAGS " -std=c++1y ")
endif()

################################################################################
# Enable experimental libraries
option(CONFIG_ENABLE_EXPERIMENTAL "Enable experimental libraries" ON)

################################################################################
# Adds a ton of warnings to the build. 
# NOTE: ALL CODE SHOULD COMPILE CLEANLY WITH THIS ON!
option(CONFIG_ALL_WARNINGS "Add warnings for GCC/Clang" ON)


################################################################################
# Unsupported configurations should work for most
# libraries. Certain libraries require some configuration macros
# not defined by default.
option(CONFIG_ELIB_ASSERT_CONFIG 
      "Ensure that a elib/config finds a valid configuration" ON)
if (CONFIG_ELIB_ASSERT_CONFIG)
    add_definitions( -DELIB_ASSERT_CONFIG )
endif()

################################################################################
# elib is a open source project that uses coverity scan for defect detection.
# Certain parts of elib are unsupported on otherwise buggy for EDG.
# This configures the enviroment to only show EDG what it can handle.
option(CONFIG_COVERITY_SCAN
      "Setup build for when doing a build with coverity scan" OFF)

if (CONFIG_COVERITY_SCAN)
    config_message( STATUS "Configuring for Coverity Scan")
    add_definitions( -DELIB_CONFIG_COVERITY_SCAN )
endif()

################################################################################
# Unit tests require the boost test library.
option(CONFIG_UNIT_TESTS "build unit tests" ON)

################################################################################
# Make LIT and filesystem's test-helper use python3 instead of python
option(CONFIG_PYTHON3
        "Require that the python interpreter used in the testsuite is 
         Python 3.0 or greater" OFF)
if (CONFIG_PYTHON3)
    set(PythonInterp_FIND_VERSION  "3.0")
endif()