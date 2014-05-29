#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include <elib/filesystem.hpp>
#include <system_error>
#include "../static_test_helper.hpp"
using namespace elib::fs;


BOOST_AUTO_TEST_SUITE(elib_filesystem_static_recursive_directory_iterator_test_suite)

BOOST_AUTO_TEST_CASE(simple_test)
{
    recursive_directory_iterator it(static_test_env_path);
    recursive_directory_iterator end;
    
    while (it != end) {
        *it;
        ++it;
    }
    BOOST_CHECK(true);
}

BOOST_AUTO_TEST_SUITE_END()