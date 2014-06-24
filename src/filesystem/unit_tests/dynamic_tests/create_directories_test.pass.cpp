// REQUIRES: ELIB_FILESYSTEM, ELIB_PYTHON_EXECUTABLE
#include <elib/filesystem.hpp>
#include <system_error>
#include "../dynamic_test_helper.hpp"
#include "rapid-cxx-test.hpp"
using namespace elib::fs;

TEST_SUITE(elib_filesystem_dynamic_create_directories_test_suite)

TEST_CASE(single_dir_test)
{
    scoped_test_env env;
    path const file = env.make_env_path("dir1");
    
    std::error_code ec;
    TEST_REQUIRE(create_directories(file, ec));
    TEST_REQUIRE(not ec);
    TEST_REQUIRE(is_directory(file));
}

TEST_CASE(recursive_dir_test)
{
    scoped_test_env env;
    path const first_dir = env.make_env_path("dir1");
    path const second_dir = first_dir / "dir2";
    path const third_dir = second_dir / "dir3";
    
    std::error_code ec;
    TEST_REQUIRE(create_directories(third_dir, ec));
    TEST_REQUIRE(not ec);
    TEST_REQUIRE(is_directory(first_dir));
    TEST_REQUIRE(is_directory(second_dir));
    TEST_REQUIRE(is_directory(third_dir));
}

TEST_CASE(file_already_exists_test)
{
    scoped_test_env env;
    path const first_dir = env.make_env_path("dir1");
    path const second_dir = first_dir / "dir2";
    
    env.create_file(first_dir);
    
    std::error_code ec;
    TEST_REQUIRE(not create_directories(second_dir, ec));
    TEST_REQUIRE(ec);
    TEST_REQUIRE(is_regular_file(first_dir));
}

TEST_CASE(dir_exists_test)
{
    scoped_test_env env;
    path const file = env.make_env_path("dir1");
    
    env.create_dir(file);
    
    std::error_code ec;
    TEST_REQUIRE(not create_directories(file, ec));
    TEST_REQUIRE(not ec);
}

TEST_CASE(bad_perms_test)
{
    scoped_test_env env;
    path const dir1 = env.make_env_path("dir1");
    path const dir2 = dir1 / "dir2";
    path const dir3 = dir2 / "dir3";
    env.create_dir(dir1);
    
    permissions(dir1, perms::none);
    
    {
        std::error_code ec;
        create_directories(dir3, ec);
        TEST_CHECK(ec);
    }{
        TEST_CHECK_THROW(filesystem_error, create_directories(dir3));
    }
    
    permissions(dir1, perms::all);
}

TEST_SUITE_END()