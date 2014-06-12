#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include <elib/filesystem.hpp>
#include <chrono>
#include <system_error>
#include "../dynamic_test_helper.hpp"
using namespace elib::fs;

using Clock = std::chrono::system_clock;

BOOST_AUTO_TEST_SUITE(elib_filesystem_dynamic_copy_file_test_suite)

BOOST_AUTO_TEST_CASE(dne_test)
{
    scoped_test_env env;
    path const file = env.make_env_path("file1");
    path const to = env.make_env_path("file2");
    
    {
        std::error_code ec;
        copy_file(file, to, ec);
        BOOST_REQUIRE(ec);
        BOOST_REQUIRE(not exists(to));
    }
    {
        BOOST_REQUIRE(not exists(to));
        BOOST_REQUIRE_THROW(copy_file(file, to), filesystem_error);
        BOOST_REQUIRE(not exists(to));
    }
}

BOOST_AUTO_TEST_CASE(directory_test)
{
    scoped_test_env env;
    path const file = env.make_env_path("file1");
    path const to = env.make_env_path("file2");
    
    env.create_dir(file);
    BOOST_REQUIRE(is_directory(file));
    
    {
        std::error_code ec;
        copy_file(file, to, ec);
        BOOST_REQUIRE(ec);
        BOOST_REQUIRE(not exists(to));
    }
    {
        BOOST_REQUIRE_THROW(copy_file(file, to), filesystem_error);
        BOOST_REQUIRE(not exists(to));
    }
}

BOOST_AUTO_TEST_CASE(file_copy_test)
{
    scoped_test_env env;
    path const file = env.make_env_path("file1");
    path const to = env.make_env_path("file2");
    
    env.create_file(file, 42);
    BOOST_REQUIRE(not exists(to));
    
    std::error_code ec;
    BOOST_REQUIRE(copy_file(file, to, ec));
    BOOST_REQUIRE(not ec);
    BOOST_REQUIRE(file_size(file) == 42);
    BOOST_REQUIRE(file_size(file) == 42);
}

BOOST_AUTO_TEST_CASE(file_copy_existing_test)
{
    scoped_test_env env;
    path const file = env.make_env_path("file1");
    path const to = env.make_env_path("file2");
    
    env.create_file(file, 42);
    env.create_file(to, 1);
    
    std::error_code ec;
    BOOST_REQUIRE(not copy_file(file, to, ec));
    BOOST_REQUIRE(ec);
    BOOST_REQUIRE(file_size(file) == 42);
    BOOST_REQUIRE(file_size(to) == 1);
}

BOOST_AUTO_TEST_CASE(file_copy_existing_throw_test)
{
    scoped_test_env env;
    path const file = env.make_env_path("file1");
    path const to = env.make_env_path("file2");
    
    env.create_file(file, 42);
    env.create_file(to, 1);
    
    BOOST_REQUIRE_THROW(copy_file(file, to), filesystem_error);
    BOOST_REQUIRE(file_size(to) == 1);
}

BOOST_AUTO_TEST_CASE(file_copy_existing_skip_test)
{
    scoped_test_env env;
    path const file = env.make_env_path("file1");
    path const to = env.make_env_path("file2");
    
    env.create_file(file, 42);
    env.create_file(to, 1);
    
    std::error_code ec;
    BOOST_REQUIRE(not copy_file(file, to, copy_options::skip_existing, ec));
    BOOST_REQUIRE(not ec);
    BOOST_REQUIRE(file_size(file) == 42);
    BOOST_REQUIRE(file_size(to) == 1);
}

BOOST_AUTO_TEST_CASE(file_copy_existing_overwrite_test)
{
    scoped_test_env env;
    path const file = env.make_env_path("file1");
    path const to = env.make_env_path("file2");
    
    env.create_file(file, 42);
    env.create_file(to, 1);
    
    std::error_code ec;
    BOOST_REQUIRE(copy_file(file, to, copy_options::overwrite_existing, ec));
    BOOST_REQUIRE(not ec);
    BOOST_REQUIRE(file_size(file) == 42);
    BOOST_REQUIRE(file_size(file) == 42);
}

BOOST_AUTO_TEST_CASE(file_copy_update_existing_older)
{
    scoped_test_env env;
    path const file = env.make_env_path("file1");
    path const to = env.make_env_path("file2");
    
    env.create_file(file, 42);
    env.create_file(to, 1);
    
    file_time_type new_update = Clock::now() - std::chrono::seconds(100);
    last_write_time(file, new_update);
    
    std::error_code ec;
    BOOST_REQUIRE(not copy_file(file, to, copy_options::update_existing, ec));
    BOOST_REQUIRE(not ec);
    BOOST_REQUIRE(file_size(file) == 42);
    BOOST_REQUIRE(file_size(to) == 1);
}

BOOST_AUTO_TEST_CASE(file_copy_update_existing_newer)
{
    scoped_test_env env;
    path const file = env.make_env_path("file1");
    path const to = env.make_env_path("file2");
    
    env.create_file(file, 42);
    env.create_file(to, 1);
    
    file_time_type new_update = Clock::now() - std::chrono::seconds(100);
    last_write_time(to, new_update);
    BOOST_REQUIRE(last_write_time(to) < last_write_time(file));
    
    std::error_code ec;
    //BOOST_REQUIRE(copy_file(file, to, copy_options::update_existing, ec));
    copy_file(file, to, copy_options::update_existing, ec);
    BOOST_REQUIRE(not ec);
    BOOST_REQUIRE(file_size(file) == 42);
    BOOST_REQUIRE(file_size(to) == 42);
}

BOOST_AUTO_TEST_CASE(empty_file_test)
{
    scoped_test_env env;
    path const file = env.make_env_path("file1");
    path const to = env.make_env_path("file2");
    
    // create with size of 0
    env.create_file(file, 0);
    BOOST_REQUIRE(is_regular_file(file));
    
    std::error_code ec;
    copy_file(file, to, ec);
    BOOST_REQUIRE(not ec);
    BOOST_REQUIRE(is_regular_file(to));
    BOOST_REQUIRE(file_size(to) == 0);
}

BOOST_AUTO_TEST_SUITE_END()