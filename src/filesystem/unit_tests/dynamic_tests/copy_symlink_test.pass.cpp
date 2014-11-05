// REQUIRES: ELIB_FILESYSTEM, ELIB_PYTHON_EXECUTABLE
#include <elib/filesystem.hpp>
#include <system_error>
#include "../dynamic_test_helper.hpp"
#include "rapid-cxx-test.hpp"
using namespace elib::fs;


TEST_SUITE(elib_filesystem_dynamic_copy_symlink_test_suite)

TEST_CASE(dne_test)
{
    scoped_test_env env;
    path const file = env.make_env_path("dne");
    path const to = env.make_env_path("to");
    
    {
        std::error_code ec;
        copy_symlink(file, to, ec);
        TEST_REQUIRE(ec);
    }
    {
        TEST_REQUIRE_THROW(filesystem_error, copy_symlink(file, to));
    }
}

TEST_CASE(already_exists_test)
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
    TEST_REQUIRE(ec);
    TEST_REQUIRE(not is_symlink(to) && is_regular_file(to));
}

TEST_CASE(symlink_to_file_test)
{
    scoped_test_env env;
    path const real_file = env.make_env_path("real_file");
    path const file = env.make_env_path("dne");
    path const to = env.make_env_path("to");
    env.create_file(real_file);
    env.create_symlink(real_file, file);
    
    std::error_code ec;
    copy_symlink(file, to, ec);
    TEST_REQUIRE(not ec);
    TEST_REQUIRE(is_symlink(to) && equivalent(to, real_file));
}

TEST_CASE(symlink_to_dir_test)
{
    scoped_test_env env;
    path const real_file = env.make_env_path("real_file");
    path const file = env.make_env_path("dne");
    path const to = env.make_env_path("to");
    env.create_dir(real_file);
    env.create_symlink(real_file, file);
    
    std::error_code ec;
    copy_symlink(file, to, ec);
    TEST_REQUIRE(not ec);
    TEST_REQUIRE(is_symlink(to) && equivalent(to, real_file));
}

TEST_CASE(non_symlink_test)
{
    scoped_test_env env;
    path const file = env.make_env_path("file1");
    path const to = env.make_env_path("to");
    env.create_file(file);
    
    {
        std::error_code ec;
        copy_symlink(file, to, ec);
        TEST_REQUIRE(ec);
        TEST_CHECK(not exists(to));
    }
    {
        TEST_REQUIRE_THROW(filesystem_error, copy_symlink(file, to));
        TEST_CHECK(not exists(to));
    }
}

TEST_SUITE_END()