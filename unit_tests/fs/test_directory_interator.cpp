#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include <elib/fs/path.h>
#include <elib/fs/directory_iterator.h>

#include <vector>
#include <string>
#include <iostream>

using namespace elib::fs;
using namespace elib::fs::detail;


#define PRINTL(x) std::cout << (x) << std::endl


BOOST_AUTO_TEST_SUITE(fs_directory_iterator_test_suite)

BOOST_AUTO_TEST_CASE(fs_directory_iterator_init)
{
    BOOST_CHECK(true);
}

BOOST_AUTO_TEST_SUITE_END()