#define BOOST_TEST_MODULE Main
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include <elib/filesystem.hpp>
#include <system_error>
#include "../dynamic_test_helper.hpp"
using namespace elib::fs;

BOOST_AUTO_TEST_SUITE(elib_filesystem_dynamic_resize_file_test_suite)

BOOST_AUTO_TEST_CASE(dne_test)
{
    scoped_test_env env;
    path const file = env.make_env_path("dne");
    
    {
        std::error_code ec;
        resize_file(file, 0, ec);
        BOOST_REQUIRE(ec);
    }
    {
        BOOST_REQUIRE_THROW(resize_file(file, 0), filesystem_error);
    }
}

BOOST_AUTO_TEST_CASE(directory_test)
{
    scoped_test_env env;
    path const file = env.make_env_path("dir");
    
    env.create_dir(file);
    BOOST_REQUIRE(is_directory(file));
    
    {
        std::error_code ec;
        resize_file(file, 0, ec);
        BOOST_REQUIRE(ec);
    }
    {
        BOOST_REQUIRE_THROW(resize_file(file, 0), filesystem_error);
    }
}

BOOST_AUTO_TEST_CASE(increase_size_with_error_code_test)
{
    scoped_test_env env;
    path const file = env.make_env_path("file1");
    env.create_file(file, 42);
    BOOST_REQUIRE(file_size(file) == 42);
    
    std::error_code ec;
    resize_file(file, 100, ec);
    BOOST_REQUIRE(not ec);
    BOOST_REQUIRE(file_size(file) == 100);
}

BOOST_AUTO_TEST_CASE(increase_size_without_error_code_test)
{
    scoped_test_env env;
    path const file = env.make_env_path("file1");
    env.create_file(file, 42);
    BOOST_REQUIRE(file_size(file) == 42);
    
    std::error_code ec;
    BOOST_REQUIRE_NO_THROW(resize_file(file, 100));
    BOOST_REQUIRE(file_size(file) == 100);
}

BOOST_AUTO_TEST_CASE(decrease_size_with_error_code_test)
{
    scoped_test_env env;
    path const file = env.make_env_path("file1");
    env.create_file(file, 42);
    BOOST_REQUIRE(file_size(file) == 42);
    
    std::error_code ec;
    resize_file(file, 1, ec);
    BOOST_REQUIRE(not ec);
    BOOST_REQUIRE(file_size(file) == 1);
}

BOOST_AUTO_TEST_CASE(decrease_size_without_error_code_test)
{
    scoped_test_env env;
    path const file = env.make_env_path("file1");
    env.create_file(file, 42);
    BOOST_REQUIRE(file_size(file) == 42);
    
    std::error_code ec;
    BOOST_REQUIRE_NO_THROW(resize_file(file, 1));
    BOOST_REQUIRE(file_size(file) == 1);
}

BOOST_AUTO_TEST_SUITE_END()