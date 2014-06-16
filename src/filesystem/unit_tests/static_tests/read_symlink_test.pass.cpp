// REQUIRES: ELIB_FILESYSTEM_SOURCE
#include <elib/filesystem.hpp>
#include <system_error>
#include "../static_test_helper.hpp"
#include "rapid-cxx-test.hpp"
using namespace elib::fs;

TEST_SUITE(elib_filesystem_static_read_symlink_test_suite)

TEST_CASE(dne_test)
{
    const path file = make_static_env_path("dne");
    // with error code
    {
        std::error_code ec;
        path ret = read_symlink(file, ec);
        TEST_REQUIRE(ec);
        TEST_REQUIRE(ret == path());
    }
    // no error code
    {
        TEST_REQUIRE_THROW(filesystem_error,  read_symlink(file));
    }
}

TEST_CASE(regular_file_test)
{
    const path file = make_static_env_path("empty_file");
    // with error code
    {
        std::error_code ec;
        path ret = read_symlink(file, ec);
        TEST_REQUIRE(ec);
        TEST_REQUIRE(ret == path());
    }
    // no error code
    {
        TEST_REQUIRE_THROW(filesystem_error,  read_symlink(file));
    }
}

TEST_CASE(directory_test)
{
    const path file = make_static_env_path("dir1");
    // with error code
    {
        std::error_code ec;
        path ret = read_symlink(file, ec);
        TEST_REQUIRE(ec);
        TEST_REQUIRE(ret == path());
    }
    // no error code
    {
        TEST_REQUIRE_THROW(filesystem_error,  read_symlink(file));
    }
}

TEST_SUITE_END()