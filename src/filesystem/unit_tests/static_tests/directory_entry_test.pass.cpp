// REQUIRES: ELIB_FILESYSTEM_SOURCE, ELIB_BOOST_TEST
#define BOOST_TEST_MODULE Main
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include <elib/filesystem.hpp>
using namespace elib::fs;


/// NOTE: the iterators test this class nicely. This testsuite just handles
/// unhit lines
BOOST_AUTO_TEST_SUITE(elib_filesystem_static_directory_entry_test_suite)

BOOST_AUTO_TEST_CASE(symlink_status_test)
{
    directory_entry d(".", file_status(), file_status(file_type::regular));
    BOOST_CHECK(d.status().type() == file_type::regular);
    BOOST_CHECK(d.symlink_status().type() == file_type::regular);
}
 

BOOST_AUTO_TEST_SUITE_END()