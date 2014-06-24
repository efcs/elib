// REQUIRES: ELIB_FILESYSTEM, ELIB_PYTHON_EXECUTABLE
#include <elib/filesystem.hpp>
#include <system_error>
#include "../dynamic_test_helper.hpp"
#include "rapid-cxx-test.hpp"
using namespace elib::fs;

TEST_SUITE(elib_filesystem_dynamic_remove_test_suite)

TEST_CASE(dne_test)
{
    scoped_test_env env;
    path const file = env.make_env_path("dne");
    
    {
        std::error_code ec;
        TEST_REQUIRE(not remove(file, ec));
        TEST_REQUIRE(ec);
    }
    {
        TEST_REQUIRE_THROW(filesystem_error, remove(file));
    }
}

TEST_CASE(remove_file_test)
{
    scoped_test_env env;
    path const file = env.make_env_path("file1");
    env.create_file(file);
    
    std::error_code ec;
    TEST_REQUIRE(remove(file, ec));
    TEST_REQUIRE(not ec);
    TEST_REQUIRE(not exists(file));
}

TEST_CASE(remove_empty_directory_test)
{
    scoped_test_env env;
    path const file = env.make_env_path("file1");
    env.create_dir(file);
    
    std::error_code ec;
    TEST_REQUIRE(remove(file, ec));
    TEST_REQUIRE(not ec);
    TEST_REQUIRE(not exists(file));
}

TEST_CASE(remove_non_empty_directory_test)
{
    scoped_test_env env;
    path const file = env.make_env_path("file1");
    path const nested_file = file / "file2";
    env.create_dir(file);
    env.create_file(nested_file);
    
    std::error_code ec;
    TEST_REQUIRE(not remove(file, ec));
    TEST_REQUIRE(ec);
    TEST_REQUIRE(is_directory(file) && is_regular_file(nested_file));
}

TEST_CASE(remove_symlink_test)
{
    scoped_test_env env;
    path const real_file = env.make_env_path("real_file");
    path const file = env.make_env_path("file1");
    env.create_file(real_file);
    env.create_symlink(real_file, file);
    
    std::error_code ec;
    TEST_REQUIRE(remove(file, ec));
    TEST_REQUIRE(not ec);
    TEST_REQUIRE(not exists(file));
    TEST_REQUIRE(is_regular_file(real_file));
}

TEST_SUITE_END()