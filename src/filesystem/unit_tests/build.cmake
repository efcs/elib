################################################################################
file(GLOB DYNAMIC_TEST_SRC ${CMAKE_CURRENT_LIST_DIR}/dynamic_tests/*.pass.cpp)
file(GLOB STATIC_TEST_SRC ${CMAKE_CURRENT_LIST_DIR}/static_tests/*.pass.cpp)

set_property(SOURCE ${STATIC_TEST_SRC} ${DYNAMIC_TEST_SRC}
    APPEND PROPERTY COMPILE_DEFINITIONS
    ELIB_FILESYSTEM_UNIT_TEST_PATH="${CMAKE_CURRENT_LIST_DIR}"
    ELIB_ROOT_PATH="${ELIB_ROOT_PATH}")

add_test_list(${STATIC_TEST_SRC})

# These tests rely on
if (DEFINED ELIB_PYTHON_EXECUTABLE)
    set_property(SOURCE ${DYNAMIC_TEST_SRC}
        APPEND PROPERTY COMPILE_DEFINITIONS
        ELIB_PYTHON_EXECUTABLE=${ELIB_PYTHON_EXECUTABLE})
    add_test_list(${DYNAMIC_TEST_SRC})
else()
    config_message(WARNING "No python executable found." 
                           " Disabling filesystem's dynamic tests")
endif()
