// REQUIRES: ELIB_FILESYSTEM_SOURCE
#include <elib/filesystem.hpp>
#include <system_error>
#include <cstdint>
#include "../dynamic_test_helper.hpp"
#include "rapid-cxx-test.hpp"
using namespace elib::fs;


TEST_SUITE(elib_filesystem_dynamic_remove_all_test_suite)

TEST_CASE(dne_test)
{
    scoped_test_env env;
    path const file = env.make_env_path("dne");
    
    {
        std::error_code ec;
        TEST_REQUIRE(0 == remove_all(file, ec));
        TEST_REQUIRE(not ec);
    }
    {
        TEST_REQUIRE(0 == remove_all(file));
    }
}

TEST_CASE(empty_dir_test)
{
    scoped_test_env env;
    path const file = env.make_env_path("dir1");
    
    env.create_dir(file);
    
    std::error_code ec;
    TEST_REQUIRE(1 == remove_all(file, ec));
    TEST_REQUIRE(not ec);
}

TEST_CASE(file_test)
{
   scoped_test_env env;
    path const file = env.make_env_path("file1");
    
    env.create_file(file);
    
    std::error_code ec;
    TEST_REQUIRE(1 == remove_all(file, ec));
    TEST_REQUIRE(not ec); 
}

TEST_CASE(non_empty_non_recursive_dir_test)
{
    scoped_test_env env;
    path const file = env.make_env_path("dir1");
    path const f1 = file / "f1";
    path const f2 = file / "f2";
    
    env.create_dir(file);
    env.create_file(f1);
    env.create_file(f2);
    
    std::error_code ec;
    TEST_REQUIRE(3 == remove_all(file, ec));
    TEST_REQUIRE(not ec);
}

TEST_CASE(non_empty_recursive_dir_test)
{
    scoped_test_env env;
    path const file = env.make_env_path("dir1");
    path const f1 = file / "f1";
    path const f2 = file / "f2";
    path const dir1 = file / "dir1";
    path const f3 = dir1 / "f3";
    path const f4 = dir1 / "f4";
    
    env.create_dir(file);
    env.create_dir(dir1);
    env.create_file(f1);
    env.create_file(f2);
    env.create_file(f3);
    env.create_file(f4);
    
    std::error_code ec;
    TEST_REQUIRE(6 == remove_all(file, ec));
    TEST_REQUIRE(not ec);
}

TEST_SUITE_END()