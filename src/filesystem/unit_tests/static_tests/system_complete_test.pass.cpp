// REQUIRES: ELIB_FILESYSTEM_SOURCE
#define BOOST_TEST_MODULE Main
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include <elib/filesystem.hpp>
#include <system_error>
#include "../static_test_helper.hpp"
using namespace elib::fs;


BOOST_AUTO_TEST_SUITE(elib_filesystem_static_system_complete_test_suite)

BOOST_AUTO_TEST_CASE(basic_test)
{
    // has_root_name() && has_root_directory()
    {
        const path p("//net/foo");
        path sys_ret = system_complete(p);
        path abs_ret = absolute(p, current_path());
        BOOST_REQUIRE(sys_ret == abs_ret);
    }
    // !has_root_name() && has_root_directory()
    {
        const path p("/foo");
        path sys_ret = system_complete(p);
        path abs_ret = absolute(p, current_path());
        BOOST_REQUIRE(sys_ret == abs_ret);
    }
    // has_root_name() && !has_root_directory()
    {
        const path p("//net");
        path sys_ret = system_complete(p);
        path abs_ret = absolute(p, current_path());
        BOOST_REQUIRE(sys_ret == abs_ret);
    }
    // !has_root_name() && !has_root_directory()
    {
        const path p("bar/baz");
        path sys_ret = system_complete(p);
        path abs_ret = absolute(p, current_path());
        BOOST_REQUIRE(sys_ret == abs_ret);
    }
}

BOOST_AUTO_TEST_CASE(coverage_test)
{
    const path p(".");
    std::error_code ec;
    
    path sys_ret = system_complete(p, ec);
    path abs_ret = absolute(p, current_path());
    BOOST_REQUIRE(not ec);
    BOOST_CHECK(sys_ret == abs_ret);
}

BOOST_AUTO_TEST_SUITE_END()
