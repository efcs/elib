add_library_src()
include_build_dir(http)
add_unit_test_src(unit_tests)

include(web/http/build.cmake)