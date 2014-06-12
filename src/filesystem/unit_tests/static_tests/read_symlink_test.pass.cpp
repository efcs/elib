// REQUIRES: ELIB_FILESYSTEM_SOURCE, ELIB_BOOST_TEST
#define BOOST_TEST_MODULE Main
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include <elib/filesystem.hpp>
#include <system_error>
#include "../static_test_helper.hpp"
using namespace elib::fs;

BOOST_AUTO_TEST_SUITE(elib_filesystem_static_read_symlink_test_suite)

BOOST_AUTO_TEST_CASE(dne_test)
{
    const path file = make_static_env_path("dne");
    // with error code
    {
        std::error_code ec;
        path ret = read_symlink(file, ec);
        BOOST_REQUIRE(ec);
        BOOST_REQUIRE(ret == path());
    }
    // no error code
    {
        BOOST_REQUIRE_THROW(read_symlink(file), filesystem_error);
    }
}

BOOST_AUTO_TEST_CASE(regular_file_test)
{
    const path file = make_static_env_path("empty_file");
    // with error code
    {
        std::error_code ec;
        path ret = read_symlink(file, ec);
        BOOST_REQUIRE(ec);
        BOOST_REQUIRE(ret == path());
    }
    // no error code
    {
        BOOST_REQUIRE_THROW(read_symlink(file), filesystem_error);
    }
}

BOOST_AUTO_TEST_CASE(directory_test)
{
    const path file = make_static_env_path("dir1");
    // with error code
    {
        std::error_code ec;
        path ret = read_symlink(file, ec);
        BOOST_REQUIRE(ec);
        BOOST_REQUIRE(ret == path());
    }
    // no error code
    {
        BOOST_REQUIRE_THROW(read_symlink(file), filesystem_error);
    }
}

BOOST_AUTO_TEST_SUITE_END()