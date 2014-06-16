// REQUIRES: ELIB_FILESYSTEM_SOURCE
#include <elib/filesystem.hpp>
#include <system_error>
#include "../dynamic_test_helper.hpp"
#include "rapid-cxx-test.hpp"
using namespace elib::fs;

TEST_SUITE(elib_filesystem_dynamic_create_directory_attributes_test_suite)

TEST_CASE(dir_exists_test)
{
    scoped_test_env env;
    
    path const file = env.make_env_path("dir1");
    env.create_dir(file);
    
    path const existing = env.make_env_path("existing");
    env.create_dir(existing);
    
    {
        std::error_code ec;
        TEST_REQUIRE(not create_directory(file, existing, ec));
        TEST_REQUIRE(not ec);
    }
    {
        TEST_CHECK(not create_directory(file, existing));
    }
}

TEST_CASE(file_exists_test)
{
    scoped_test_env env;
    path const file = env.make_env_path("file1");
    env.create_file(file);
    path const existing = env.make_env_path("existing");
    env.create_dir(existing);

    std::error_code ec;
    TEST_REQUIRE(not create_directory(file, existing, ec));
    TEST_REQUIRE(ec);
}

TEST_CASE(bad_parent)
{
    scoped_test_env env;
    path const file = env.make_env_path("dir1/dir2");
    
    path const existing = env.make_env_path("existing");
    env.create_dir(existing);
    
    {
        std::error_code ec;
        TEST_REQUIRE(not create_directory(file, existing, ec));
        TEST_REQUIRE(ec);
        TEST_REQUIRE(not is_directory(env.make_env_path("dir1")));
    }
    {
        TEST_REQUIRE_THROW(filesystem_error, create_directory(file, existing));
    }
}

TEST_CASE(bad_existing_test)
{
    scoped_test_env env;
    path const file = env.make_env_path("dir1");
    path const existing = env.make_env_path("existing");
    
    {
        std::error_code ec;
        TEST_REQUIRE(not create_directory(file, existing, ec));
        TEST_REQUIRE(ec);
        TEST_REQUIRE(not is_directory(file));
    }
    {
        TEST_REQUIRE_THROW(filesystem_error, create_directory(file, existing));
    }
}

TEST_CASE(existing_file_test)
{
    scoped_test_env env;
    path const file = env.make_env_path("dir1");
    path const existing = env.make_env_path("existing");
    
    env.create_file(existing);
    
    /// Set the permissions to somthing non-default.
    file_status existing_st = status(existing);
    TEST_REQUIRE(existing_st.permissions() != perms::owner_all);
    permissions(existing, perms::owner_all);
    
    std::error_code ec;
    TEST_REQUIRE(create_directory(file, existing, ec));
    TEST_REQUIRE(not ec);
    
    file_status st = status(file);
    TEST_REQUIRE(is_directory(st));
    TEST_REQUIRE(st.permissions() == perms::owner_all);
}

TEST_SUITE_END()