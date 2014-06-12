// REQUIRES: ELIB_FILESYSTEM_SOURCE, ELIB_BOOST_TEST
#define BOOST_TEST_MODULE Main
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include <elib/filesystem.hpp>
#include <system_error>
#include "../dynamic_test_helper.hpp"
using namespace elib::fs;

BOOST_AUTO_TEST_SUITE(elib_filesystem_dynamic_create_directory_attributes_test_suite)

BOOST_AUTO_TEST_CASE(dir_exists_test)
{
    scoped_test_env env;
    
    path const file = env.make_env_path("dir1");
    env.create_dir(file);
    
    path const existing = env.make_env_path("existing");
    env.create_dir(existing);
    
    {
        std::error_code ec;
        BOOST_REQUIRE(not create_directory(file, existing, ec));
        BOOST_REQUIRE(not ec);
    }
    {
        BOOST_CHECK(not create_directory(file, existing));
    }
}

BOOST_AUTO_TEST_CASE(file_exists_test)
{
    scoped_test_env env;
    path const file = env.make_env_path("file1");
    env.create_file(file);
    path const existing = env.make_env_path("existing");
    env.create_dir(existing);

    std::error_code ec;
    BOOST_REQUIRE(not create_directory(file, existing, ec));
    BOOST_REQUIRE(ec);
}

BOOST_AUTO_TEST_CASE(bad_parent)
{
    scoped_test_env env;
    path const file = env.make_env_path("dir1/dir2");
    
    path const existing = env.make_env_path("existing");
    env.create_dir(existing);
    
    {
        std::error_code ec;
        BOOST_REQUIRE(not create_directory(file, existing, ec));
        BOOST_REQUIRE(ec);
        BOOST_REQUIRE(not is_directory(env.make_env_path("dir1")));
    }
    {
        BOOST_REQUIRE_THROW(create_directory(file, existing), filesystem_error);
    }
}

BOOST_AUTO_TEST_CASE(bad_existing_test)
{
    scoped_test_env env;
    path const file = env.make_env_path("dir1");
    path const existing = env.make_env_path("existing");
    
    {
        std::error_code ec;
        BOOST_REQUIRE(not create_directory(file, existing, ec));
        BOOST_REQUIRE(ec);
        BOOST_REQUIRE(not is_directory(file));
    }
    {
        BOOST_REQUIRE_THROW(create_directory(file, existing), filesystem_error);
    }
}

BOOST_AUTO_TEST_CASE(existing_file_test)
{
    scoped_test_env env;
    path const file = env.make_env_path("dir1");
    path const existing = env.make_env_path("existing");
    
    env.create_file(existing);
    
    /// Set the permissions to somthing non-default.
    file_status existing_st = status(existing);
    BOOST_REQUIRE(existing_st.permissions() != perms::owner_all);
    permissions(existing, perms::owner_all);
    
    std::error_code ec;
    BOOST_REQUIRE(create_directory(file, existing, ec));
    BOOST_REQUIRE(not ec);
    
    file_status st = status(file);
    BOOST_REQUIRE(is_directory(st));
    BOOST_REQUIRE(st.permissions() == perms::owner_all);
}

BOOST_AUTO_TEST_SUITE_END()