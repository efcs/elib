// REQUIRES: ELIB_FILESYSTEM_SOURCE
#define BOOST_TEST_MODULE Main
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include <elib/filesystem.hpp>
#include <system_error>
#include "../static_test_helper.hpp"
using namespace elib::fs;


BOOST_AUTO_TEST_SUITE(elib_filesystem_static_is_empty_test_suite)

BOOST_AUTO_TEST_CASE(dne_test)
{
    const path file = make_static_env_path("dne");
    // with error code
    {
        std::error_code ec;
        bool ret = is_empty(file, ec);
        BOOST_REQUIRE(ec);
        BOOST_REQUIRE(ret == false);
    }
    // without error code
    {
        BOOST_REQUIRE_THROW(is_empty(file), filesystem_error);
    }
}

BOOST_AUTO_TEST_CASE(empty_file_test)
{
    const path file = make_static_env_path("empty_file");
    // with error code
    {
        std::error_code ec;
        bool ret = is_empty(file, ec);
        BOOST_REQUIRE(not ec);
        BOOST_REQUIRE(ret);
    }
    // no error code
    {
        bool ret = true;
        BOOST_REQUIRE_NO_THROW(ret = is_empty(file));
        BOOST_REQUIRE(ret);
    }
}

BOOST_AUTO_TEST_CASE(non_empty_file_test)
{
    const path file = make_static_env_path("non_empty_file");
    // with error code
    {
        std::error_code ec;
        bool ret = is_empty(file, ec);
        BOOST_REQUIRE(not ec);
        BOOST_REQUIRE(not ret);
    }
    // no error code
    {
        bool ret = true;
        BOOST_REQUIRE_NO_THROW(ret = is_empty(file));
        BOOST_REQUIRE(not ret);
    }
}

/// Note: no static empty directory since empty directories
///  cannot be checked into git
BOOST_AUTO_TEST_CASE(not_empty_directory_test)
{
    const path file = make_static_env_path("dir1");
    // with error code
    {
        std::error_code ec;
        bool ret = is_empty(file, ec);
        BOOST_REQUIRE(not ec);
        BOOST_REQUIRE(not ret);
    }
    // no error code
    {
        bool ret = true;
        BOOST_REQUIRE_NO_THROW(ret = is_empty(file));
        BOOST_REQUIRE(not ret);
    }
}

BOOST_AUTO_TEST_SUITE_END()