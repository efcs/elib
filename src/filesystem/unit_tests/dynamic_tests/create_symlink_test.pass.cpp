// REQUIRES: ELIB_FILESYSTEM, ELIB_PYTHON_EXECUTABLE
#include <elib/filesystem.hpp>
#include <system_error>
#include "../dynamic_test_helper.hpp"
#include "rapid-cxx-test.hpp"
using namespace elib::fs;

TEST_SUITE(elib_filesystem_dynamic_create_symlink_test_suite)

TEST_CASE(dne_test)
{
    scoped_test_env env;
    path const file = env.make_env_path("dne");
    path const to = env.make_env_path("sym1");
    
    // with error code
    std::error_code ec;
    create_symlink(file, to, ec);
    TEST_REQUIRE(not ec);
    TEST_REQUIRE(is_symlink(to));
}


TEST_CASE(dne_no_error_code_test)
{
    scoped_test_env env;
    path const file = env.make_env_path("dne");
    path const to = env.make_env_path("sym1");
    
    // with error code
    TEST_REQUIRE_NO_THROW(create_symlink(file, to));
    TEST_REQUIRE(is_symlink(to));
}

TEST_CASE(file_test)
{
    scoped_test_env env;
    path const file = env.make_env_path("file1");
    path const to = env.make_env_path("sym1");
    
    env.create_file(file);
 
    std::error_code ec;
    create_symlink(file, to, ec);
    TEST_REQUIRE(not ec);
    TEST_REQUIRE(is_regular_file(file));
    TEST_REQUIRE(is_symlink(to));
    TEST_REQUIRE(read_symlink(to).native() == file.native());
}

TEST_CASE(directory_test)
{
    scoped_test_env env;
    path const file = env.make_env_path("file1");
    path const to = env.make_env_path("sym1");
    
    env.create_dir(file);
 
    std::error_code ec;
    create_symlink(file, to, ec);
    TEST_REQUIRE(not ec);
    TEST_REQUIRE(is_directory(file));
    TEST_REQUIRE(is_symlink(to));
    TEST_REQUIRE(read_symlink(to) == file);
}

TEST_CASE(symlink_test)
{
    scoped_test_env env;
    path const real_file = env.make_env_path("real_file");
    path const file = env.make_env_path("file1");
    path const to = env.make_env_path("sym1");
    
    env.create_file(real_file);
    env.create_symlink(real_file, file);
 
    std::error_code ec;
    create_symlink(file, to, ec);
    TEST_REQUIRE(not ec);
    TEST_REQUIRE(is_symlink(to));
    TEST_REQUIRE(read_symlink(to) == file);
}

TEST_CASE(already_exists_test)
{
    scoped_test_env env;
    path const file = env.make_env_path("file1");
    path const to = env.make_env_path("file2");
    
    env.create_file(file);
    env.create_file(to);
 
    {
        std::error_code ec;
        create_symlink(file, to, ec);
        TEST_REQUIRE(ec);
        TEST_REQUIRE(is_regular_file(to));
    }
    {
        TEST_REQUIRE_THROW(filesystem_error, create_symlink(file, to));
        TEST_REQUIRE(is_regular_file(to));
    }
}

TEST_SUITE_END()