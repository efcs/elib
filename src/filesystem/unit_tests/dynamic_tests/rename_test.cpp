#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include <elib/filesystem.hpp>
#include <system_error>
#include "../dynamic_test_helper.hpp"
using namespace elib::fs;

BOOST_AUTO_TEST_SUITE(elib_filesystem_dynamic_rename_test_suite)

BOOST_AUTO_TEST_CASE(rename_dne_file_test)
{
    scoped_test_env env;
    path const file = env.make_env_path("file1");
    path const to = env.make_env_path("file2");
    
    BOOST_REQUIRE(not exists(file));
    
    // with error code
    {
        std::error_code ec;
        rename(file, to, ec);
        BOOST_REQUIRE(ec);
    }
    // no error code
    {
        BOOST_REQUIRE_THROW(rename(file, to), filesystem_error);
    }
}

BOOST_AUTO_TEST_CASE(rename_file_test)
{
    scoped_test_env env;
    path const file = env.make_env_path("file1");
    path const to = env.make_env_path("file2");
    
    env.create_file(file);
    BOOST_REQUIRE(exists(file) && not exists(to));
    
    // with error code
    {
        std::error_code ec;
        rename(file, to, ec);
        BOOST_REQUIRE(not ec);
        BOOST_REQUIRE(not exists(file));
        BOOST_REQUIRE(is_regular_file(to));
    }
    // without error code in reverse
    {
        BOOST_REQUIRE_NO_THROW(rename(to, file));
        BOOST_REQUIRE(not exists(to));
        BOOST_REQUIRE(is_regular_file(file));
    }
}

BOOST_AUTO_TEST_CASE(rename_empty_directory_test)
{
    scoped_test_env env;
    path const file = env.make_env_path("dir1");
    path const to = env.make_env_path("dir2");
    
    env.create_dir(file);
    BOOST_REQUIRE(is_directory(file) && not exists(to));
    
    // with error code
    {
        std::error_code ec;
        rename(file, to, ec);
        BOOST_REQUIRE(not ec);
        BOOST_REQUIRE(not exists(file));
        BOOST_REQUIRE(is_directory(to));
    }
    // without error code in reverse
    {
        BOOST_REQUIRE_NO_THROW(rename(to, file));
        BOOST_REQUIRE(not exists(to));
        BOOST_REQUIRE(is_directory(file));
    }
}

BOOST_AUTO_TEST_CASE(rename_same_file_test)
{
    scoped_test_env env;
    path const file = env.make_env_path("file1");
    path const to = env.make_env_path("file1");
    
    env.create_file(file);
    BOOST_REQUIRE(is_regular_file(file));
    
    // with error code
    {
        std::error_code ec;
        rename(file, to, ec);
        BOOST_REQUIRE(not ec);
        BOOST_REQUIRE(is_regular_file(file));
    }
    // without error code in reverse
    {
        BOOST_REQUIRE_NO_THROW(rename(to, file));
        BOOST_REQUIRE(is_regular_file(file));
    }
}

BOOST_AUTO_TEST_CASE(rename_same_dir_test)
{
    scoped_test_env env;
    path const file = env.make_env_path("dir1");
    path const to = env.make_env_path("dir1");
    
    env.create_dir(file);
    BOOST_REQUIRE(is_directory(file));
    
    // with error code
    {
        std::error_code ec;
        rename(file, to, ec);
        BOOST_REQUIRE(not ec);
        BOOST_REQUIRE(is_directory(file));
    }
    // without error code in reverse
    {
        BOOST_REQUIRE_NO_THROW(rename(to, file));
        BOOST_REQUIRE(is_directory(file));
    }
}

BOOST_AUTO_TEST_CASE(rename_to_existing_file_with_error_code_test)
{
    scoped_test_env env;
    path const file = env.make_env_path("file1");
    path const to = env.make_env_path("file2");
    
    // create with size 42
    env.create_file(file, 42);
    // create removed file with size 1
    env.create_file(to, 1);
    
    BOOST_REQUIRE(is_regular_file(file) && file_size(file) == 42);
    BOOST_REQUIRE(is_regular_file(to) && file_size(to) == 1);
    
    std::error_code ec;
    rename(file, to, ec);
    BOOST_REQUIRE(not ec);
    BOOST_REQUIRE(not exists(file));
    BOOST_REQUIRE(is_regular_file(to) && file_size(to) == 42);
}

BOOST_AUTO_TEST_CASE(rename_to_existing_file_without_error_code_test)
{
    scoped_test_env env;
    path const file = env.make_env_path("file1");
    path const to = env.make_env_path("file2");
    
    // create with size 42
    env.create_file(file, 42);
    // create removed file with size 1
    env.create_file(to, 1);
    
    BOOST_REQUIRE(is_regular_file(file) && file_size(file) == 42);
    BOOST_REQUIRE(is_regular_file(to) && file_size(to) == 1);
    
    BOOST_REQUIRE_NO_THROW(rename(file, to));
    BOOST_REQUIRE(not exists(file));
    BOOST_REQUIRE(is_regular_file(to) && file_size(to) == 42);
}

BOOST_AUTO_TEST_CASE(rename_to_existing_empty_dir_with_error_code_test)
{
    scoped_test_env env;
    path const file = env.make_env_path("dir1");
    path const nested_file = file / "file1";
    path const to = env.make_env_path("file2");
    
    // create with size 42
    env.create_dir(file);
    env.create_file(nested_file, 42);
    env.create_dir(to);
    
    BOOST_REQUIRE(is_directory(file) && not is_empty(file));
    BOOST_REQUIRE(is_directory(to) && is_empty(to));
    
    std::error_code ec;
    rename(file, to, ec);
    BOOST_REQUIRE(not ec);
    BOOST_REQUIRE(not exists(file));
    BOOST_REQUIRE(is_directory(to) && not is_empty(to));
}

BOOST_AUTO_TEST_CASE(rename_to_existing_empty_dir_without_error_code_test)
{
    scoped_test_env env;
    path const file = env.make_env_path("dir1");
    path const nested_file = file / "file1";
    path const to = env.make_env_path("file2");
    
    // create with size 42
    env.create_dir(file);
    env.create_file(nested_file, 42);
    env.create_dir(to);
    
    BOOST_REQUIRE(is_directory(file) && not is_empty(file));
    BOOST_REQUIRE(is_directory(to) && is_empty(to));
    
    BOOST_REQUIRE_NO_THROW(rename(file, to));
    BOOST_REQUIRE(not exists(file));
    BOOST_REQUIRE(is_directory(to) && not is_empty(to));
}

BOOST_AUTO_TEST_CASE(rename_symlink_with_error_code_test)
{
    scoped_test_env env;
    path const real_file = env.make_env_path("real_file");
    path const file = env.make_env_path("file1");
    path const to = env.make_env_path("file2");
    
    env.create_file(real_file, 42);
    BOOST_REQUIRE(is_regular_file(real_file));
    
    env.create_symlink(real_file, file);
    BOOST_REQUIRE(is_symlink(file) && read_symlink(file) == real_file);
    
    BOOST_REQUIRE(not exists(to));
    
    std::error_code ec;
    rename(file, to, ec);
    BOOST_REQUIRE(not ec);
    BOOST_REQUIRE(not exists(file));
    BOOST_REQUIRE(is_regular_file(real_file));
    BOOST_REQUIRE(is_symlink(to) && read_symlink(to) == real_file);
}

BOOST_AUTO_TEST_SUITE_END()