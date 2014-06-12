// REQUIRES: ELIB_FILESYSTEM_SOURCE
#define BOOST_TEST_MODULE Main
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include <elib/filesystem.hpp>
#include <system_error>
#include <cstdint>
#include "../static_test_helper.hpp"
using namespace elib::fs;

std::uintmax_t bad_result = static_cast<std::uintmax_t>(-1);

BOOST_AUTO_TEST_SUITE(elib_filesystem_static_file_size_test_suite)

BOOST_AUTO_TEST_CASE(dne_test)
{
    const path file = make_static_env_path("dne");
    
    // with error code
    {
        std::error_code ec;
        std::uintmax_t const ret = file_size(file, ec);
        BOOST_REQUIRE(ec);
        BOOST_REQUIRE(ret == bad_result);
    }
    // without error code
    {
        BOOST_REQUIRE_THROW(file_size(file), filesystem_error);
    }
}

BOOST_AUTO_TEST_CASE(directory_test)
{
    const path file = make_static_env_path("dir1");
    
    // with error code
    {
        std::error_code ec;
        std::uintmax_t const ret = file_size(file, ec);
        BOOST_REQUIRE(ec);
        BOOST_REQUIRE(ret == bad_result);
    }
    // without error code
    {
        BOOST_REQUIRE_THROW(file_size(file), filesystem_error);
    }
}

BOOST_AUTO_TEST_CASE(empty_file_test)
{
    const path file = make_static_env_path("empty_file");
    
    // with error code
    {
        std::error_code ec;
        std::uintmax_t const ret = file_size(file, ec);
        BOOST_REQUIRE(not ec);
        BOOST_REQUIRE(ret == 0);
    }
    // without error code
    {
        std::uintmax_t ret;
        BOOST_REQUIRE_NO_THROW(ret = file_size(file));
        BOOST_REQUIRE(ret == 0);
    }
}

BOOST_AUTO_TEST_CASE(non_empty_file_test)
{
    const path file = make_static_env_path("non_empty_file");
    
    // with error code
    {
        std::error_code ec;
        std::uintmax_t const ret = file_size(file, ec);
        BOOST_REQUIRE(not ec);
        BOOST_REQUIRE(ret == 42);
    }
    // without error code
    {
        std::uintmax_t ret;
        BOOST_REQUIRE_NO_THROW(ret = file_size(file));
        BOOST_REQUIRE(ret == 42);
    }
}

BOOST_AUTO_TEST_SUITE_END()