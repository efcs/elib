// REQUIRES: ELIB_FILESYSTEM_SOURCE
#include <elib/filesystem.hpp>
#include <system_error>
#include "../dynamic_test_helper.hpp"
#include "rapid-cxx-test.hpp"
using namespace elib::fs;

TEST_SUITE(elib_filesystem_dynamic_create_directory_test_suite)

TEST_CASE(dir_exists_test)
{
    scoped_test_env env;
    path const file = env.make_env_path("dir1");
    env.create_dir(file);
    
    {
        std::error_code ec;
        TEST_REQUIRE(not create_directory(file, ec));
        TEST_REQUIRE(not ec);
    }
    {
        TEST_CHECK(not create_directory(file));
    }
}

TEST_CASE(file_exists_test)
{
    scoped_test_env env;
    path const file = env.make_env_path("file1");
    env.create_file(file);

    {
        std::error_code ec;
        TEST_REQUIRE(not create_directory(file, ec));
        TEST_REQUIRE(ec);
    }
}

TEST_CASE(bad_parent)
{
    scoped_test_env env;
    path const file = env.make_env_path("dir1/dir2");
    
    {
        std::error_code ec;
        TEST_REQUIRE(not create_directory(file, ec));
        TEST_REQUIRE(ec);
        TEST_REQUIRE(not is_directory(env.make_env_path("dir1")));
    }
    {
        TEST_REQUIRE_THROW(filesystem_error, create_directory(file));
    }
}

TEST_CASE(success_test)
{
    scoped_test_env env;
    path const file = env.make_env_path("dir1");
    
    std::error_code ec;
    TEST_REQUIRE(create_directory(file, ec));
    TEST_REQUIRE(not ec);
    TEST_CHECK(is_directory(file));
}

TEST_SUITE_END()
