// REQUIRES: ELIB_FILESYSTEM_SOURCE, ELIB_BOOST_TEST
#define BOOST_TEST_MODULE Main
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include <elib/filesystem.hpp>
#include <system_error>
#include "../dynamic_test_helper.hpp"
using namespace elib::fs;

BOOST_AUTO_TEST_SUITE(elib_filesystem_dynamic_remove_test_suite)

BOOST_AUTO_TEST_CASE(dne_test)
{
    scoped_test_env env;
    path const file = env.make_env_path("dne");
    
    {
        std::error_code ec;
        BOOST_REQUIRE(not remove(file, ec));
        BOOST_REQUIRE(ec);
    }
    {
        BOOST_REQUIRE_THROW(remove(file), filesystem_error);
    }
}

BOOST_AUTO_TEST_CASE(remove_file_test)
{
    scoped_test_env env;
    path const file = env.make_env_path("file1");
    env.create_file(file);
    
    std::error_code ec;
    BOOST_REQUIRE(remove(file, ec));
    BOOST_REQUIRE(not ec);
    BOOST_REQUIRE(not exists(file));
}

BOOST_AUTO_TEST_CASE(remove_empty_directory_test)
{
    scoped_test_env env;
    path const file = env.make_env_path("file1");
    env.create_dir(file);
    
    std::error_code ec;
    BOOST_REQUIRE(remove(file, ec));
    BOOST_REQUIRE(not ec);
    BOOST_REQUIRE(not exists(file));
}

BOOST_AUTO_TEST_CASE(remove_non_empty_directory_test)
{
    scoped_test_env env;
    path const file = env.make_env_path("file1");
    path const nested_file = file / "file2";
    env.create_dir(file);
    env.create_file(nested_file);
    
    std::error_code ec;
    BOOST_REQUIRE(not remove(file, ec));
    BOOST_REQUIRE(ec);
    BOOST_REQUIRE(is_directory(file) && is_regular_file(nested_file));
}

BOOST_AUTO_TEST_CASE(remove_symlink_test)
{
    scoped_test_env env;
    path const real_file = env.make_env_path("real_file");
    path const file = env.make_env_path("file1");
    env.create_file(real_file);
    env.create_symlink(real_file, file);
    
    std::error_code ec;
    BOOST_REQUIRE(remove(file, ec));
    BOOST_REQUIRE(not ec);
    BOOST_REQUIRE(not exists(file));
    BOOST_REQUIRE(is_regular_file(real_file));
}

BOOST_AUTO_TEST_SUITE_END()