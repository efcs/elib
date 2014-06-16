// REQUIRES: ELIB_FILESYSTEM_SOURCE
#include <elib/filesystem.hpp>
#include <system_error>
#include "../static_test_helper.hpp"
#include "rapid-cxx-test.hpp"
using namespace elib::fs;


TEST_SUITE(elib_filesystem_static_system_complete_test_suite)

TEST_CASE(basic_test)
{
    // has_root_name() && has_root_directory()
    {
        const path p("//net/foo");
        path sys_ret = system_complete(p);
        path abs_ret = absolute(p, current_path());
        TEST_REQUIRE(sys_ret == abs_ret);
    }
    // !has_root_name() && has_root_directory()
    {
        const path p("/foo");
        path sys_ret = system_complete(p);
        path abs_ret = absolute(p, current_path());
        TEST_REQUIRE(sys_ret == abs_ret);
    }
    // has_root_name() && !has_root_directory()
    {
        const path p("//net");
        path sys_ret = system_complete(p);
        path abs_ret = absolute(p, current_path());
        TEST_REQUIRE(sys_ret == abs_ret);
    }
    // !has_root_name() && !has_root_directory()
    {
        const path p("bar/baz");
        path sys_ret = system_complete(p);
        path abs_ret = absolute(p, current_path());
        TEST_REQUIRE(sys_ret == abs_ret);
    }
}

TEST_CASE(coverage_test)
{
    const path p(".");
    std::error_code ec;
    
    path sys_ret = system_complete(p, ec);
    path abs_ret = absolute(p, current_path());
    TEST_REQUIRE(not ec);
    TEST_CHECK(sys_ret == abs_ret);
}

TEST_SUITE_END()
