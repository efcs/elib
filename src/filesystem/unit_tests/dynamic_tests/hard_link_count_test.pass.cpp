// REQUIRES: ELIB_FILESYSTEM, ELIB_PYTHON_EXECUTABLE
#include <elib/filesystem.hpp>
#include <system_error>
#include <cstdint>
#include "../dynamic_test_helper.hpp"
#include "rapid-cxx-test.hpp"
using namespace elib::fs;

constexpr const std::uintmax_t bad_count = static_cast<std::uintmax_t>(-1);

TEST_SUITE(elib_filesystem_dynamic_hard_link_count_test_suite)

TEST_CASE(dne_test)
{
    scoped_test_env env;
    path const file = env.make_env_path("dne");
    
    {
        std::error_code ec;
        std::uintmax_t count = hard_link_count(file, ec);
        TEST_REQUIRE(ec);
        TEST_CHECK(count == bad_count);
    }
    {
        TEST_REQUIRE_THROW(filesystem_error, hard_link_count(file));
    }
}

TEST_CASE(basic_test)
{
    scoped_test_env env;
    path const file = env.make_env_path("file1");
    env.create_file(file);
    
    std::error_code ec;
    std::uintmax_t count = hard_link_count(file, ec);
    TEST_REQUIRE(not ec);
    TEST_REQUIRE(count == 1);
    
    path const link = env.make_env_path("link1");
    env.create_hardlink(file, link);
    
    count = hard_link_count(file, ec);
    TEST_REQUIRE(not ec);
    TEST_CHECK(count == 2);
}

TEST_SUITE_END()