// REQUIRES: ELIB_FILESYSTEM
#include <elib/filesystem.hpp>
#include "rapid-cxx-test.hpp"
using namespace elib::fs;


/// NOTE: the iterators test this class nicely. This testsuite just handles
/// unhit lines
TEST_SUITE(elib_filesystem_static_directory_entry_test_suite)

TEST_CASE(symlink_status_test)
{
    directory_entry d(".");
    TEST_CHECK(d.status().type() == file_type::directory);
    TEST_CHECK(d.symlink_status().type() == file_type::directory);
}
 

TEST_SUITE_END()
