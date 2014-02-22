
add_src()
add_definitions( 
    -DELIB_CONFIGURE_FS_UNIT_TEST_PATH="${CMAKE_CURRENT_LIST_DIR}/unit_tests"
)
add_definitions(
    -DELIB_FS_ELIB_ROOT_PATH="${CONFIG_ELIB_ROOT}"
)
