// REQUIRES: ELIB_FILESYSTEM_SOURCE
#include <elib/config.hpp>
#include <elib/filesystem.hpp>
#include <chrono>
#include <system_error>
#include "../dynamic_test_helper.hpp"
#include "rapid-cxx-test.hpp"
using namespace elib::fs;

using Clock = std::chrono::system_clock;

TEST_SUITE(elib_filesystem_write_time_operations_test_suite)

TEST_CASE(dne_test)
{
    scoped_test_env env;
    path const file = env.make_env_path("file1");
    
    // with error code
    {
        file_time_type expect = file_time_type::min();
        std::error_code ec;
        file_time_type const time = last_write_time(file, ec);
        TEST_REQUIRE(ec);
        TEST_REQUIRE(time == expect);
    }
    // without error code
    {
        TEST_REQUIRE_THROW(filesystem_error, last_write_time(file));
    }
}

/// We don't actually know what to expect. but make sure we get something normal
TEST_CASE(read_time_test)
{
    scoped_test_env env;
    path const file = env.make_env_path("file1");
    env.create_file(file);
    file_time_type bad_result = file_time_type::min();
    file_time_type expect_before = Clock::now() + std::chrono::seconds(1);
    file_time_type expect_after = expect_before - std::chrono::seconds(10);
    
    file_time_type time;
    // with error code
    {
        std::error_code ec;
        time = last_write_time(file, ec);
        TEST_REQUIRE(not ec);
        TEST_REQUIRE(time != bad_result);
        TEST_CHECK(time < expect_before);
        TEST_CHECK(time > expect_after);
    }
    // without error code
    {
        file_time_type other_time;
        TEST_REQUIRE_NO_THROW(other_time = last_write_time(file));
        TEST_REQUIRE(time == other_time);
    }
}

TEST_CASE(write_time_test)
{
    scoped_test_env env;
    path const file = env.make_env_path("file1");
    env.create_file(file);
    file_time_type const bad_result = file_time_type::min();
    file_time_type const new_time = Clock::now() + std::chrono::seconds(100);
    
    // check old time
    {
        std::error_code ec;
        file_time_type const time = last_write_time(file, ec);
        TEST_REQUIRE(not ec);
        TEST_REQUIRE(time != bad_result);
        TEST_REQUIRE(time != new_time);
    }
    // set new time
    {
        std::error_code ec;
        last_write_time(file, new_time, ec);
        TEST_REQUIRE(not ec);
    }
    // check new time
    {
        std::error_code ec;
        file_time_type const time = last_write_time(file, ec);
        TEST_REQUIRE(not ec);
        TEST_REQUIRE(Clock::to_time_t(time) == Clock::to_time_t(new_time));
    }
}

#if !defined(ELIB_CONFIG_CYGWIN)
TEST_CASE(stat_fail_test)
{
    scoped_test_env env;
    path const dir = env.make_env_path("dir");
    path const file = dir / "file1";
    env.create_dir(dir);
    env.create_file(file, 42);
    
    permissions(dir, perms::none);
    
    {
        std::error_code ec;
        last_write_time(file, Clock::now(), ec);
        TEST_REQUIRE(ec);
    }
    {
        TEST_REQUIRE_THROW(filesystem_error, last_write_time(file, Clock::now()));
    }
    
    permissions(dir, perms::all);
}
# endif

TEST_SUITE_END()