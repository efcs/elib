add_library_src()
add_unit_test_src(unit_tests)

add_definitions( 
    -DELIB_FILESYSTEM_UNIT_TEST_PATH="${CMAKE_CURRENT_LIST_DIR}/unit_tests"
)

if (NOT CONFIG_ELIB_ROOT)
    message(FATAL_ERROR "CONFIG_ELIB_ROOT Must be set to top level directory for elib")
endif()
add_definitions(
    -DELIB_FILESYSTEM_ELIB_ROOT_PATH="${CONFIG_ELIB_ROOT}"
)
