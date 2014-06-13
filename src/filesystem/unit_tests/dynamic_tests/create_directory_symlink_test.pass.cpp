// REQUIRES: ELIB_FILESYSTEM_SOURCE, ELIB_BOOST_TEST
#define BOOST_TEST_MODULE Main
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include <elib/filesystem.hpp>
#include <system_error>
#include "../dynamic_test_helper.hpp"
using namespace elib::fs;


BOOST_AUTO_TEST_SUITE(elib_filesystem_dynamic_create_directory_symlink_test_suite)

BOOST_AUTO_TEST_CASE(dne_test)
{
    scoped_test_env env;
    path const file = env.make_env_path("dne");
    path const to = env.make_env_path("sym1");
    
    // with error code
    std::error_code ec;
    create_directory_symlink(file, to, ec);
    BOOST_REQUIRE(not ec);
    BOOST_REQUIRE(is_symlink(to));
}

BOOST_AUTO_TEST_CASE(dne_no_error_code_test)
{
    scoped_test_env env;
    path const file = env.make_env_path("dne");
    path const to = env.make_env_path("sym1");
    
    // with error code
    BOOST_REQUIRE_NO_THROW(create_directory_symlink(file, to));
    BOOST_REQUIRE(is_symlink(to));
}

BOOST_AUTO_TEST_CASE(file_test)
{
    scoped_test_env env;
    path const file = env.make_env_path("file1");
    path const to = env.make_env_path("sym1");
    
    env.create_file(file);
 
    std::error_code ec;
    create_directory_symlink(file, to, ec);
    BOOST_REQUIRE(not ec);
    BOOST_REQUIRE(is_regular_file(file));
    BOOST_REQUIRE(is_symlink(to));
    BOOST_REQUIRE(read_symlink(to).native() == file.native());
}

BOOST_AUTO_TEST_CASE(directory_test)
{
    scoped_test_env env;
    path const file = env.make_env_path("file1");
    path const to = env.make_env_path("sym1");
    
    env.create_dir(file);
 
    std::error_code ec;
    create_directory_symlink(file, to, ec);
    BOOST_REQUIRE(not ec);
    BOOST_REQUIRE(is_directory(file));
    BOOST_REQUIRE(is_symlink(to));
    BOOST_REQUIRE(read_symlink(to) == file);
}

BOOST_AUTO_TEST_CASE(symlink_test)
{
    scoped_test_env env;
    path const real_file = env.make_env_path("real_file");
    path const file = env.make_env_path("file1");
    path const to = env.make_env_path("sym1");
    
    env.create_file(real_file);
    env.create_symlink(real_file, file);
 
    std::error_code ec;
    create_directory_symlink(file, to, ec);
    BOOST_REQUIRE(not ec);
    BOOST_REQUIRE(is_symlink(to));
    BOOST_REQUIRE(read_symlink(to) == file);
}

BOOST_AUTO_TEST_CASE(already_exists_test)
{
    scoped_test_env env;
    path const file = env.make_env_path("file1");
    path const to = env.make_env_path("file2");
    
    env.create_file(file);
    env.create_file(to);
 
    {
        std::error_code ec;
        create_directory_symlink(file, to, ec);
        BOOST_REQUIRE(ec);
        BOOST_REQUIRE(is_regular_file(to));
    }
    {
        BOOST_REQUIRE_THROW(create_directory_symlink(file, to), filesystem_error);
    }
}

BOOST_AUTO_TEST_SUITE_END()