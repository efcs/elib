// REQUIRES: ELIB_FILESYSTEM
#include <elib/filesystem/filesystem_error.hpp>
#include <elib/filesystem/path.hpp>
#include <string>
#include <system_error>
#include "rapid-cxx-test.hpp"

using namespace elib;
using namespace elib::fs;

TEST_SUITE(filesystem_filesystem_error_test_suite)

TEST_CASE(coverage_tests)
{
    const std::string s("message");
    const std::error_code ec;
    const path p1("path1");
    const path p2("path2");
    
    // no path ctor
    {
        filesystem_error e(s, ec);
        TEST_CHECK(e.what());
        TEST_CHECK(e.path1().empty());
        TEST_CHECK(e.path2().empty());
    }
    // one path ctor
    {
        filesystem_error e(s, p1, ec);
        TEST_CHECK(e.what());
        TEST_CHECK(e.path1() == p1);
        TEST_CHECK(e.path2().empty());
    }
    // two path ctor
    {
        filesystem_error e(s, p1, p2, ec);
        TEST_CHECK(e.what());
        TEST_CHECK(e.path1() == p1);
        TEST_CHECK(e.path2() == p2);
    }
}

TEST_SUITE_END()