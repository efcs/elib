// REQUIRES: ELIB_FILESYSTEM_SOURCE
#include <elib/filesystem.hpp>
#include <system_error>
#include <cstdint>
#include "../static_test_helper.hpp"
#include "rapid-cxx-test.hpp"
using namespace elib::fs;

std::uintmax_t bad_result = static_cast<std::uintmax_t>(-1);

TEST_SUITE(elib_filesystem_static_file_size_test_suite)

TEST_CASE(dne_test)
{
    const path file = make_static_env_path("dne");
    
    // with error code
    {
        std::error_code ec;
        std::uintmax_t const ret = file_size(file, ec);
        TEST_REQUIRE(ec);
        TEST_REQUIRE(ret == bad_result);
    }
    // without error code
    {
        TEST_REQUIRE_THROW(filesystem_error,  file_size(file));
    }
}

TEST_CASE(directory_test)
{
    const path file = make_static_env_path("dir1");
    
    // with error code
    {
        std::error_code ec;
        std::uintmax_t const ret = file_size(file, ec);
        TEST_REQUIRE(ec);
        TEST_REQUIRE(ret == bad_result);
    }
    // without error code
    {
        TEST_REQUIRE_THROW(filesystem_error,  file_size(file));
    }
}

TEST_CASE(empty_file_test)
{
    const path file = make_static_env_path("empty_file");
    
    // with error code
    {
        std::error_code ec;
        std::uintmax_t const ret = file_size(file, ec);
        TEST_REQUIRE(not ec);
        TEST_REQUIRE(ret == 0);
    }
    // without error code
    {
        std::uintmax_t ret;
        TEST_REQUIRE_NO_THROW(ret = file_size(file));
        TEST_REQUIRE(ret == 0);
    }
}

TEST_CASE(non_empty_file_test)
{
    const path file = make_static_env_path("non_empty_file");
    
    // with error code
    {
        std::error_code ec;
        std::uintmax_t const ret = file_size(file, ec);
        TEST_REQUIRE(not ec);
        TEST_REQUIRE(ret == 42);
    }
    // without error code
    {
        std::uintmax_t ret;
        TEST_REQUIRE_NO_THROW(ret = file_size(file));
        TEST_REQUIRE(ret == 42);
    }
}

TEST_SUITE_END()