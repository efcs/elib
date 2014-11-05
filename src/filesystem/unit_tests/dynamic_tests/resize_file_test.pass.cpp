// REQUIRES: ELIB_FILESYSTEM, ELIB_PYTHON_EXECUTABLE
#include <elib/filesystem.hpp>
#include <system_error>
#include "../dynamic_test_helper.hpp"
#include "rapid-cxx-test.hpp"
using namespace elib::fs;

TEST_SUITE(elib_filesystem_dynamic_resize_file_test_suite)

TEST_CASE(dne_test)
{
    scoped_test_env env;
    path const file = env.make_env_path("dne");
    
    {
        std::error_code ec;
        resize_file(file, 0, ec);
        TEST_REQUIRE(ec);
    }
    {
        TEST_REQUIRE_THROW(filesystem_error, resize_file(file, 0));
    }
}

TEST_CASE(directory_test)
{
    scoped_test_env env;
    path const file = env.make_env_path("dir");
    
    env.create_dir(file);
    TEST_REQUIRE(is_directory(file));
    
    {
        std::error_code ec;
        resize_file(file, 0, ec);
        TEST_REQUIRE(ec);
    }
    {
        TEST_REQUIRE_THROW(filesystem_error, resize_file(file, 0));
    }
}

TEST_CASE(increase_size_with_error_code_test)
{
    scoped_test_env env;
    path const file = env.make_env_path("file1");
    env.create_file(file, 42);
    TEST_REQUIRE(file_size(file) == 42);
    
    std::error_code ec;
    resize_file(file, 100, ec);
    TEST_REQUIRE(not ec);
    TEST_REQUIRE(file_size(file) == 100);
}

TEST_CASE(increase_size_without_error_code_test)
{
    scoped_test_env env;
    path const file = env.make_env_path("file1");
    env.create_file(file, 42);
    TEST_REQUIRE(file_size(file) == 42);
    
    std::error_code ec;
    TEST_REQUIRE_NO_THROW(resize_file(file, 100));
    TEST_REQUIRE(file_size(file) == 100);
}

TEST_CASE(decrease_size_with_error_code_test)
{
    scoped_test_env env;
    path const file = env.make_env_path("file1");
    env.create_file(file, 42);
    TEST_REQUIRE(file_size(file) == 42);
    
    std::error_code ec;
    resize_file(file, 1, ec);
    TEST_REQUIRE(not ec);
    TEST_REQUIRE(file_size(file) == 1);
}

TEST_CASE(decrease_size_without_error_code_test)
{
    scoped_test_env env;
    path const file = env.make_env_path("file1");
    env.create_file(file, 42);
    TEST_REQUIRE(file_size(file) == 42);
    
    std::error_code ec;
    TEST_REQUIRE_NO_THROW(resize_file(file, 1));
    TEST_REQUIRE(file_size(file) == 1);
}

TEST_SUITE_END()