// REQUIRES: ELIB_FILESYSTEM_SOURCE, ELIB_BOOST_TEST
#define BOOST_TEST_MODULE Main
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include <elib/filesystem/filesystem_error.hpp>
#include <elib/filesystem/path.hpp>
#include <string>
#include <system_error>

using namespace elib;
using namespace elib::fs;

BOOST_AUTO_TEST_SUITE(filesystem_filesystem_error_test_suite)

BOOST_AUTO_TEST_CASE(coverage_tests)
{
    const std::string s("message");
    const std::error_code ec;
    const path p1("path1");
    const path p2("path2");
    
    // no path ctor
    {
        filesystem_error e(s, ec);
        BOOST_CHECK(e.what());
        BOOST_CHECK(e.path1().empty());
        BOOST_CHECK(e.path2().empty());
    }
    // one path ctor
    {
        filesystem_error e(s, p1, ec);
        BOOST_CHECK(e.what());
        BOOST_CHECK(e.path1() == p1);
        BOOST_CHECK(e.path2().empty());
    }
    // two path ctor
    {
        filesystem_error e(s, p1, p2, ec);
        BOOST_CHECK(e.what());
        BOOST_CHECK(e.path1() == p1);
        BOOST_CHECK(e.path2() == p2);
    }
}

BOOST_AUTO_TEST_SUITE_END()