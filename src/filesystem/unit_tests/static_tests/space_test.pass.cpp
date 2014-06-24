// REQUIRES: ELIB_FILESYSTEM
#include <elib/filesystem.hpp>
#include <system_error>
#include <cstdint>
#include "../static_test_helper.hpp"
#include "rapid-cxx-test.hpp"
using namespace elib::fs;

constexpr const std::uintmax_t bad_size = static_cast<std::uintmax_t>(-1);

TEST_SUITE(elib_filesystem_static_space_test_suite)

TEST_CASE(dne_test)
{
    const path file = make_static_env_path("dne");
    
    {
        std::error_code ec;
        space_info info = space(file, ec);
        TEST_REQUIRE(ec);
        TEST_CHECK(info.capacity == bad_size);
        TEST_CHECK(info.free == bad_size);
        TEST_CHECK(info.available == bad_size);
    }
    {
        TEST_REQUIRE_THROW(filesystem_error,  space(file));
    }
}

TEST_CASE(file_test)
{
    const path file = make_static_env_path("empty_file");
    
    std::error_code ec;
    space_info info = space(file, ec);
    TEST_REQUIRE(not ec);
    TEST_CHECK(info.capacity > 0);
    TEST_CHECK(info.free > 0 && info.free < info.capacity);
    TEST_CHECK(info.available > 0 && info.available < info.capacity);
}

TEST_SUITE_END()