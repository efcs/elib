// REQUIRES: ELIB_FILESYSTEM_SOURCE
#include <elib/filesystem.hpp>
#include <system_error>
#include "../static_test_helper.hpp"
#include "rapid-cxx-test.hpp"
using namespace elib::fs;


TEST_SUITE(elib_filesystem_static_is_empty_test_suite)

TEST_CASE(dne_test)
{
    const path file = make_static_env_path("dne");
    // with error code
    {
        std::error_code ec;
        bool ret = is_empty(file, ec);
        TEST_REQUIRE(ec);
        TEST_REQUIRE(ret == false);
    }
    // without error code
    {
        TEST_REQUIRE_THROW(filesystem_error,  is_empty(file));
    }
}

TEST_CASE(empty_file_test)
{
    const path file = make_static_env_path("empty_file");
    // with error code
    {
        std::error_code ec;
        bool ret = is_empty(file, ec);
        TEST_REQUIRE(not ec);
        TEST_REQUIRE(ret);
    }
    // no error code
    {
        bool ret = true;
        TEST_REQUIRE_NO_THROW(ret = is_empty(file));
        TEST_REQUIRE(ret);
    }
}

TEST_CASE(non_empty_file_test)
{
    const path file = make_static_env_path("non_empty_file");
    // with error code
    {
        std::error_code ec;
        bool ret = is_empty(file, ec);
        TEST_REQUIRE(not ec);
        TEST_REQUIRE(not ret);
    }
    // no error code
    {
        bool ret = true;
        TEST_REQUIRE_NO_THROW(ret = is_empty(file));
        TEST_REQUIRE(not ret);
    }
}

/// Note: no static empty directory since empty directories
///  cannot be checked into git
TEST_CASE(not_empty_directory_test)
{
    const path file = make_static_env_path("dir1");
    // with error code
    {
        std::error_code ec;
        bool ret = is_empty(file, ec);
        TEST_REQUIRE(not ec);
        TEST_REQUIRE(not ret);
    }
    // no error code
    {
        bool ret = true;
        TEST_REQUIRE_NO_THROW(ret = is_empty(file));
        TEST_REQUIRE(not ret);
    }
}

TEST_SUITE_END()