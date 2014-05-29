#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include <elib/filesystem.hpp>
#include <system_error>
#include "../dynamic_test_helper.hpp"
using namespace elib::fs;

BOOST_AUTO_TEST_SUITE(elib_filesystem_dynamic_create_directories_test_suite)

BOOST_AUTO_TEST_CASE(single_dir_test)
{
    scoped_test_env env;
    path const file = make_env_path("dir1");
    
    std::error_code ec;
    BOOST_REQUIRE(create_directories(file, ec));
    BOOST_REQUIRE(not ec);
    BOOST_REQUIRE(is_directory(file));
}

BOOST_AUTO_TEST_CASE(recursive_dir_test)
{
    scoped_test_env env;
    path const first_dir = make_env_path("dir1");
    path const second_dir = first_dir / "dir2";
    path const third_dir = second_dir / "dir3";
    
    std::error_code ec;
    BOOST_REQUIRE(create_directories(third_dir, ec));
    BOOST_REQUIRE(not ec);
    BOOST_REQUIRE(is_directory(first_dir));
    BOOST_REQUIRE(is_directory(second_dir));
    BOOST_REQUIRE(is_directory(third_dir));
}

BOOST_AUTO_TEST_CASE(file_already_exists_test)
{
    scoped_test_env env;
    path const first_dir = make_env_path("dir1");
    path const second_dir = first_dir / "dir2";
    
    python_create_file(first_dir);
    
    std::error_code ec;
    BOOST_REQUIRE(not create_directories(second_dir, ec));
    BOOST_REQUIRE(ec);
    BOOST_REQUIRE(is_regular_file(first_dir));
}

BOOST_AUTO_TEST_CASE(dir_exists_test)
{
    scoped_test_env env;
    path const file = make_env_path("dir1");
    
    python_create_dir(file);
    
    std::error_code ec;
    BOOST_REQUIRE(not create_directories(file, ec));
    BOOST_REQUIRE(not ec);
}


BOOST_AUTO_TEST_SUITE_END()