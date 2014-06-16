// REQUIRES: ELIB_FILESYSTEM_SOURCE
#include <elib/filesystem.hpp>
#include <system_error>
#include "../dynamic_test_helper.hpp"
#include "rapid-cxx-test.hpp"
using namespace elib::fs;

TEST_SUITE(elib_filesystem_dynamic_equivalent_test_suite)

TEST_CASE(both_dne_test)
{
    scoped_test_env env;
    path const p1 = env.make_env_path("dne1");
    path const p2 = env.make_env_path("dne2");
    
    {
        std::error_code ec;
        TEST_REQUIRE(not equivalent(p1, p2, ec));
        TEST_REQUIRE(not ec);
    }
    {
        bool ret{};
        TEST_REQUIRE_NO_THROW(ret = equivalent(p1, p2));
        TEST_REQUIRE(not ret);
    }
}

TEST_CASE(one_dne_test)
{
    scoped_test_env env;
    path const p1 = env.make_env_path("file1");
    path const p2 = env.make_env_path("dne2");
    env.create_file(p1);
    
    {
        std::error_code ec;
        TEST_REQUIRE(not equivalent(p1, p2, ec));
        TEST_REQUIRE(ec);
    }
    {
        TEST_REQUIRE_THROW(filesystem_error, equivalent(p1, p2));
    }
}

TEST_CASE(not_equiv_both_exist)
{
    scoped_test_env env;
    path const p1 = env.make_env_path("file1");
    path const p2 = env.make_env_path("dir1");
    env.create_file(p1);
    env.create_dir(p2);
    
    {
        std::error_code ec;
        TEST_REQUIRE(not equivalent(p1, p2, ec));
        TEST_REQUIRE(not ec);
    }
    {
        bool ret{};
        TEST_REQUIRE_NO_THROW(ret = equivalent(p1, p2));
        TEST_REQUIRE(not ret);
    }
}

TEST_CASE(same_file_test)
{
    scoped_test_env env;
    path const p1 = env.make_env_path("file1");
    path const p2 = env.make_env_path("file1");
    env.create_file(p1);
    
    {
        std::error_code ec;
        TEST_REQUIRE(equivalent(p1, p2, ec));
        TEST_REQUIRE(not ec);
    }
    {
        bool ret{};
        TEST_REQUIRE_NO_THROW(ret = equivalent(p1, p2));
        TEST_REQUIRE(ret);
    } 
}

TEST_CASE(symlink_test)
{
    scoped_test_env env;
    path const p1 = env.make_env_path("file1");
    path const p2 = env.make_env_path("sym1");
    env.create_file(p1);
    env.create_symlink(p1, p2);
    
    {
        std::error_code ec;
        TEST_REQUIRE(equivalent(p1, p2, ec));
        TEST_REQUIRE(not ec);
    }
    {
        bool ret{};
        TEST_REQUIRE_NO_THROW(ret = equivalent(p1, p2));
        TEST_REQUIRE(ret);
    }
}

TEST_CASE(hardlink_test)
{
    scoped_test_env env;
    path const p1 = env.make_env_path("file1");
    path const p2 = env.make_env_path("link1");
    env.create_file(p1);
    env.create_hardlink(p1, p2);
    
    {
        std::error_code ec;
        TEST_REQUIRE(equivalent(p1, p2, ec));
        TEST_REQUIRE(not ec);
    }
    {
        bool ret{};
        TEST_REQUIRE_NO_THROW(ret = equivalent(p1, p2));
        TEST_REQUIRE(ret);
    }
}

TEST_CASE(different_paths_same_file_test)
{
    scoped_test_env env;
    path const p1 = env.make_env_path("file1");
    path const p2 = env.test_root / ".." / env.test_root.filename() / "./file1";
    env.create_file(p1);
    
    {
        std::error_code ec;
        TEST_REQUIRE(equivalent(p1, p2, ec));
        TEST_REQUIRE(not ec);
    }
    {
        bool ret{};
        TEST_REQUIRE_NO_THROW(ret = equivalent(p1, p2));
        TEST_REQUIRE(ret);
    }
}

TEST_CASE(two_symlinks_to_same_file_test)
{
    scoped_test_env env;
    path const real_file = env.make_env_path("real_file");
    path const p1 = env.make_env_path("sym1");
    path const p2 = env.make_env_path("sym2");
    env.create_file(real_file);
    env.create_symlink(real_file, p1);
    env.create_symlink(real_file, p2);
    
    {
        std::error_code ec;
        TEST_REQUIRE(equivalent(p1, p2, ec));
        TEST_REQUIRE(not ec);
    }
    {
        bool ret{};
        TEST_REQUIRE_NO_THROW(ret = equivalent(p1, p2));
        TEST_REQUIRE(ret);
    }
}

TEST_SUITE_END()