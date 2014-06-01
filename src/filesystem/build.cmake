add_library_src()
add_library_src(detail)
add_header_test_src(header_tests)
include_build_dir(unit_tests)

add_definitions( 
    -DELIB_FILESYSTEM_UNIT_TEST_PATH="${CMAKE_CURRENT_LIST_DIR}/unit_tests"
  )