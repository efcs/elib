add_library_src()
add_library_src(detail)
include_build_dir(unit_tests)

add_definitions( 
    -DELIB_FILESYSTEM_UNIT_TEST_PATH="${CMAKE_CURRENT_LIST_DIR}/unit_tests"
  )