// REQUIRES: ELIB_FILESYSTEM_SOURCE
#define BOOST_TEST_MODULE Main
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include <elib/filesystem.hpp>
#include <system_error>
#include "../dynamic_test_helper.hpp"
using namespace elib::fs;

BOOST_AUTO_TEST_SUITE(elib_filesystem_dynamic_create_directory_test_suite)

BOOST_AUTO_TEST_CASE(dir_exists_test)
{
    scoped_test_env env;
    path const file = env.make_env_path("dir1");
    env.create_dir(file);
    
    {
        std::error_code ec;
        BOOST_REQUIRE(not create_directory(file, ec));
        BOOST_REQUIRE(not ec);
    }
    {
        BOOST_CHECK(not create_directory(file));
    }
}

BOOST_AUTO_TEST_CASE(file_exists_test)
{
    scoped_test_env env;
    path const file = env.make_env_path("file1");
    env.create_file(file);

    {
        std::error_code ec;
        BOOST_REQUIRE(not create_directory(file, ec));
        BOOST_REQUIRE(ec);
    }
}

BOOST_AUTO_TEST_CASE(bad_parent)
{
    scoped_test_env env;
    path const file = env.make_env_path("dir1/dir2");
    
    {
        std::error_code ec;
        BOOST_REQUIRE(not create_directory(file, ec));
        BOOST_REQUIRE(ec);
        BOOST_REQUIRE(not is_directory(env.make_env_path("dir1")));
    }
    {
        BOOST_REQUIRE_THROW(create_directory(file), filesystem_error);
    }
}

BOOST_AUTO_TEST_CASE(success_test)
{
    scoped_test_env env;
    path const file = env.make_env_path("dir1");
    
    std::error_code ec;
    BOOST_REQUIRE(create_directory(file, ec));
    BOOST_REQUIRE(not ec);
    BOOST_CHECK(is_directory(file));
}

BOOST_AUTO_TEST_SUITE_END()
