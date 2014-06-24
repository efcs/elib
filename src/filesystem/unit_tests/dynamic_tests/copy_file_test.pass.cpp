// REQUIRES: ELIB_FILESYSTEM, ELIB_PYTHON_EXECUTABLE
#include <elib/filesystem.hpp>
#include <chrono>
#include <system_error>
#include "../dynamic_test_helper.hpp"
#include "rapid-cxx-test.hpp"
using namespace elib::fs;

using Clock = std::chrono::system_clock;

TEST_SUITE(elib_filesystem_dynamic_copy_file_test_suite)

TEST_CASE(dne_test)
{
    scoped_test_env env;
    path const file = env.make_env_path("file1");
    path const to = env.make_env_path("file2");
    
    {
        std::error_code ec;
        copy_file(file, to, ec);
        TEST_REQUIRE(ec);
        TEST_REQUIRE(not exists(to));
    }
    {
        TEST_REQUIRE(not exists(to));
        TEST_REQUIRE_THROW(filesystem_error, copy_file(file, to));
        TEST_REQUIRE(not exists(to));
    }
}

TEST_CASE(directory_test)
{
    scoped_test_env env;
    path const file = env.make_env_path("file1");
    path const to = env.make_env_path("file2");
    
    env.create_dir(file);
    TEST_REQUIRE(is_directory(file));
    
    {
        std::error_code ec;
        copy_file(file, to, ec);
        TEST_REQUIRE(ec);
        TEST_REQUIRE(not exists(to));
    }
    {
        TEST_REQUIRE_THROW(filesystem_error, copy_file(file, to));
        TEST_REQUIRE(not exists(to));
    }
}

TEST_CASE(file_copy_test)
{
    scoped_test_env env;
    path const file = env.make_env_path("file1");
    path const to = env.make_env_path("file2");
    
    env.create_file(file, 42);
    TEST_REQUIRE(not exists(to));
    
    std::error_code ec;
    TEST_REQUIRE(copy_file(file, to, ec));
    TEST_REQUIRE(not ec);
    TEST_REQUIRE(file_size(file) == 42);
    TEST_REQUIRE(file_size(file) == 42);
}

TEST_CASE(file_copy_existing_test)
{
    scoped_test_env env;
    path const file = env.make_env_path("file1");
    path const to = env.make_env_path("file2");
    
    env.create_file(file, 42);
    env.create_file(to, 1);
    
    std::error_code ec;
    TEST_REQUIRE(not copy_file(file, to, ec));
    TEST_REQUIRE(ec);
    TEST_REQUIRE(file_size(file) == 42);
    TEST_REQUIRE(file_size(to) == 1);
}

TEST_CASE(file_copy_existing_throw_test)
{
    scoped_test_env env;
    path const file = env.make_env_path("file1");
    path const to = env.make_env_path("file2");
    
    env.create_file(file, 42);
    env.create_file(to, 1);
    
    TEST_REQUIRE_THROW(filesystem_error, copy_file(file, to));
    TEST_REQUIRE(file_size(to) == 1);
}

TEST_CASE(file_copy_existing_skip_test)
{
    scoped_test_env env;
    path const file = env.make_env_path("file1");
    path const to = env.make_env_path("file2");
    
    env.create_file(file, 42);
    env.create_file(to, 1);
    
    std::error_code ec;
    TEST_REQUIRE(not copy_file(file, to, copy_options::skip_existing, ec));
    TEST_REQUIRE(not ec);
    TEST_REQUIRE(file_size(file) == 42);
    TEST_REQUIRE(file_size(to) == 1);
}

TEST_CASE(file_copy_existing_overwrite_test)
{
    scoped_test_env env;
    path const file = env.make_env_path("file1");
    path const to = env.make_env_path("file2");
    
    env.create_file(file, 42);
    env.create_file(to, 1);
    
    std::error_code ec;
    TEST_REQUIRE(copy_file(file, to, copy_options::overwrite_existing, ec));
    TEST_REQUIRE(not ec);
    TEST_REQUIRE(file_size(file) == 42);
    TEST_REQUIRE(file_size(file) == 42);
}

TEST_CASE(file_copy_update_existing_older)
{
    scoped_test_env env;
    path const file = env.make_env_path("file1");
    path const to = env.make_env_path("file2");
    
    env.create_file(file, 42);
    env.create_file(to, 1);
    
    file_time_type new_update = Clock::now() - std::chrono::seconds(100);
    last_write_time(file, new_update);
    
    std::error_code ec;
    TEST_REQUIRE(not copy_file(file, to, copy_options::update_existing, ec));
    TEST_REQUIRE(not ec);
    TEST_REQUIRE(file_size(file) == 42);
    TEST_REQUIRE(file_size(to) == 1);
}

TEST_CASE(file_copy_update_existing_newer)
{
    scoped_test_env env;
    path const file = env.make_env_path("file1");
    path const to = env.make_env_path("file2");
    
    env.create_file(file, 42);
    env.create_file(to, 1);
    
    file_time_type new_update = Clock::now() - std::chrono::seconds(100);
    last_write_time(to, new_update);
    TEST_REQUIRE(last_write_time(to) < last_write_time(file));
    
    std::error_code ec;
    //TEST_REQUIRE(copy_file(file, to, copy_options::update_existing, ec));
    copy_file(file, to, copy_options::update_existing, ec);
    TEST_REQUIRE(not ec);
    TEST_REQUIRE(file_size(file) == 42);
    TEST_REQUIRE(file_size(to) == 42);
}

TEST_CASE(empty_file_test)
{
    scoped_test_env env;
    path const file = env.make_env_path("file1");
    path const to = env.make_env_path("file2");
    
    // create with size of 0
    env.create_file(file, 0);
    TEST_REQUIRE(is_regular_file(file));
    
    std::error_code ec;
    copy_file(file, to, ec);
    TEST_REQUIRE(not ec);
    TEST_REQUIRE(is_regular_file(to));
    TEST_REQUIRE(file_size(to) == 0);
}

TEST_SUITE_END()