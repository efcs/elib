// REQUIRES: ELIB_FILESYSTEM_SOURCE
#define BOOST_TEST_MODULE Main
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include <elib/filesystem.hpp>
#include <system_error>
#include "../dynamic_test_helper.hpp"
using namespace elib::fs;


BOOST_AUTO_TEST_SUITE(elib_filesystem_dynamic_copy_symlink_test_suite)

BOOST_AUTO_TEST_CASE(dne_test)
{
    scoped_test_env env;
    path const file = env.make_env_path("dne");
    path const to = env.make_env_path("to");
    
    {
        std::error_code ec;
        copy_symlink(file, to, ec);
        BOOST_REQUIRE(ec);
    }
    {
        BOOST_REQUIRE_THROW(copy_symlink(file, to), filesystem_error);
    }
}

BOOST_AUTO_TEST_CASE(already_exists_test)
{
    scoped_test_env env;
    path const real_file = env.make_env_path("real_file");
    path const file = env.make_env_path("dne");
    path const to = env.make_env_path("to");
    env.create_file(real_file);
    env.create_symlink(real_file, file);
    env.create_file(to);
    
    std::error_code ec;
    copy_symlink(file, to, ec);
    BOOST_REQUIRE(ec);
    BOOST_REQUIRE(not is_symlink(to) && is_regular_file(to));
}

BOOST_AUTO_TEST_CASE(symlink_to_file_test)
{
    scoped_test_env env;
    path const real_file = env.make_env_path("real_file");
    path const file = env.make_env_path("dne");
    path const to = env.make_env_path("to");
    env.create_file(real_file);
    env.create_symlink(real_file, file);
    
    std::error_code ec;
    copy_symlink(file, to, ec);
    BOOST_REQUIRE(not ec);
    BOOST_REQUIRE(is_symlink(to) && equivalent(to, real_file));
}

BOOST_AUTO_TEST_CASE(symlink_to_dir_test)
{
    scoped_test_env env;
    path const real_file = env.make_env_path("real_file");
    path const file = env.make_env_path("dne");
    path const to = env.make_env_path("to");
    env.create_dir(real_file);
    env.create_symlink(real_file, file);
    
    std::error_code ec;
    copy_symlink(file, to, ec);
    BOOST_REQUIRE(not ec);
    BOOST_REQUIRE(is_symlink(to) && equivalent(to, real_file));
}

BOOST_AUTO_TEST_CASE(non_symlink_test)
{
    scoped_test_env env;
    path const file = env.make_env_path("file1");
    path const to = env.make_env_path("to");
    env.create_file(file);
    
    {
        std::error_code ec;
        copy_symlink(file, to, ec);
        BOOST_REQUIRE(ec);
        BOOST_CHECK(not exists(to));
    }
    {
        BOOST_REQUIRE_THROW(copy_symlink(file, to), filesystem_error);
        BOOST_CHECK(not exists(to));
    }
}

BOOST_AUTO_TEST_SUITE_END()