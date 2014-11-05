// REQUIRES: ELIB_FILESYSTEM, ELIB_PYTHON_EXECUTABLE
#include <elib/filesystem.hpp>
#include <system_error>
#include "../dynamic_test_helper.hpp"
#include "rapid-cxx-test.hpp"
using namespace elib::fs;

TEST_SUITE(elib_filesystem_dynamic_copy_test_test_suite)

TEST_CASE(from_dne_test)
{
    scoped_test_env env;
    path const file = env.make_env_path("dne");
    path const to = env.make_env_path("dne2");
    
    {
        std::error_code ec;
        copy(file, to, ec);
        TEST_REQUIRE(ec);
    }
    {
        TEST_REQUIRE_THROW(filesystem_error, copy(file, to));
    }
}

TEST_CASE(equivalent_test)
{
    scoped_test_env env;
    path const file = env.make_env_path("file1");
    env.create_file(file);
        
    {
        std::error_code ec;
        copy(file, file, ec);
        TEST_REQUIRE(ec);
    }
    {
        TEST_REQUIRE_THROW(filesystem_error, copy(file, file));
    }
}

TEST_CASE(from_is_other)
{
    scoped_test_env env;
    path const file = env.make_env_path("file1");
    path const to = env.make_env_path("file2");
    env.create_socket(file);
    
    std::error_code ec;
    copy(file, to, ec);
    TEST_REQUIRE(ec);
}

TEST_CASE(to_is_other)
{
    scoped_test_env env;
    path const file = env.make_env_path("file1");
    path const to = env.make_env_path("file2");
    env.create_file(file);
    env.create_socket(to);
    
    std::error_code ec;
    copy(file, to, ec);
    TEST_REQUIRE(ec);
}

TEST_CASE(directory_to_regular_file_test)
{
    scoped_test_env env;
    path const file = env.make_env_path("file1");
    path const to = env.make_env_path("file2");
    env.create_dir(file);
    env.create_file(to);
    
    std::error_code ec;
    copy(file, to, ec);
    TEST_REQUIRE(ec);
}

TEST_CASE(skip_symlinks_test)
{
    scoped_test_env env;
    path const real_file = env.make_env_path("real_file");
    path const file = env.make_env_path("sym1");
    path const to = env.make_env_path("to");
    
    env.create_file(real_file);
    env.create_symlink(real_file, file);
    
    std::error_code ec;
    copy(file, to, copy_options::skip_symlinks, ec);
    TEST_CHECK(not ec);
    TEST_REQUIRE(not exists(to));
}

TEST_CASE(copy_symlink_test)
{
    scoped_test_env env;
    path const real_file = env.make_env_path("real_file");
    path const file = env.make_env_path("sym1");
    path const to = env.make_env_path("to");
    
    env.create_file(real_file);
    env.create_symlink(real_file, file);
    
    std::error_code ec;
    copy(file, to, copy_options::create_symlinks, ec);
    TEST_CHECK(not ec);
    TEST_REQUIRE(is_symlink(to));
    TEST_REQUIRE(read_symlink(to) == real_file);
}

TEST_CASE(copy_symlink_to_exists_test)
{
    scoped_test_env env;
    path const real_file = env.make_env_path("real_file");
    path const file = env.make_env_path("sym1");
    path const to = env.make_env_path("to");
    
    env.create_file(real_file);
    env.create_symlink(real_file, file);
    env.create_file(to);
    
    {
        std::error_code ec;
        copy(file, to, copy_options::create_symlinks, ec);
        TEST_CHECK(ec);
        TEST_REQUIRE(not is_symlink(to));
        TEST_REQUIRE(is_regular_file(to));
    }
    {
        TEST_REQUIRE_THROW(filesystem_error, copy(file, to, copy_options::create_symlinks));
        TEST_REQUIRE(not is_symlink(to));
    }
}

TEST_CASE(directory_only_regular_file_test)
{
    scoped_test_env env;
    path const file = env.make_env_path("file1");
    path const to = env.make_env_path("to");
    
    env.create_file(file);
    
    std::error_code ec;
    copy(file, to, copy_options::directories_only, ec);
    TEST_REQUIRE(not ec);
    TEST_REQUIRE(not exists(to));
}

TEST_CASE(regular_file_create_symlinks_test)
{
    scoped_test_env env;
    path const file = env.make_env_path("file1");
    path const to = env.make_env_path("to");
    
    env.create_file(file);
    
    std::error_code ec;
    copy(file, to, copy_options::create_symlinks, ec);
    TEST_CHECK(not ec);
    TEST_REQUIRE(is_symlink(to));
    TEST_REQUIRE(read_symlink(to) == file);
}

TEST_CASE(regular_file_create_hard_link_test)
{
    scoped_test_env env;
    path const file = env.make_env_path("file1");
    path const to = env.make_env_path("to");
    
    env.create_file(file);
    
    std::error_code ec;
    copy(file, to, copy_options::create_hard_links, ec);
    TEST_CHECK(not ec);
    TEST_CHECK(is_regular_file(to));
    TEST_REQUIRE(hard_link_count(file) == 2);
}

TEST_CASE(regular_file_copy_to_dir)
{
    scoped_test_env env;
    path const file = env.make_env_path("file1");
    path const to_dir = env.make_env_path("dir1");
    path const to = to_dir / "file1";
    
    
    env.create_file(file, 42);
    create_directory(to_dir);
    TEST_REQUIRE(is_directory(to_dir));
    
    std::error_code ec;
    copy(file, to_dir);
    TEST_CHECK(not ec);
    TEST_CHECK(is_regular_file(to));
}

TEST_CASE(regular_file_copy)
{
    scoped_test_env env;
    path const file = env.make_env_path("file");
    path const to = env.make_env_path("to");
    
    env.create_file(file, 42);
    
    std::error_code ec;
    copy(file, to, ec);
    TEST_REQUIRE(not ec);
    TEST_REQUIRE(is_regular_file(to));
}

TEST_CASE(copy_dir_test)
{
    scoped_test_env env;
    path const dir = env.make_env_path("dir1");
    path const f1 = dir / "file1";
    path const d1 = dir / "dir1";
    path const to = env.make_env_path("to");
    path const to_f1 = to / "file1";
    path const to_d1 = to / "dir1";
    
    env.create_dir(dir);
    env.create_file(f1, 42);
    env.create_dir(d1);
    
    std::error_code ec;
    copy(dir, to, ec);
    TEST_REQUIRE(not ec);
    TEST_REQUIRE(is_directory(to));
    TEST_REQUIRE(is_regular_file(to_f1));
    TEST_REQUIRE(not exists(to_d1));
}

TEST_CASE(copy_dir_recursive_test)
{
    scoped_test_env env;
    path const dir = env.make_env_path("dir1");
    path const f1 = dir / "file1";
    path const d1 = dir / "dir1";
    path const f2 = d1 / "file2";
    path const to = env.make_env_path("to");
    path const to_f1 = to / "file1";
    path const to_d1 = to / "dir1";
    path const to_f2 = to_d1 / "file2";
    
    env.create_dir(dir);
    env.create_file(f1, 42);
    env.create_dir(d1);
    env.create_file(f2, 42);
    
    std::error_code ec;
    copy(dir, to, copy_options::recursive, ec);
    TEST_REQUIRE(not ec);
    TEST_REQUIRE(is_directory(to));
    TEST_REQUIRE(is_regular_file(to_f1));
    TEST_REQUIRE(is_directory(to_d1));
    TEST_REQUIRE(is_regular_file(to_f2));
}

TEST_CASE(copy_dir_recursive_dir_only_test)
{
    scoped_test_env env;
    path const dir = env.make_env_path("dir1");
    path const f1 = dir / "file1";
    path const d1 = dir / "dir1";
    path const f2 = d1 / "file2";
    path const to = env.make_env_path("to");
    path const to_f1 = to / "file1";
    path const to_d1 = to / "dir1";
    path const to_f2 = to_d1 / "file2";
    
    env.create_dir(dir);
    env.create_file(f1, 42);
    env.create_dir(d1);
    env.create_file(f2, 42);
    
    std::error_code ec;
    copy(dir, to, copy_options::recursive | copy_options::directories_only, ec);
    TEST_REQUIRE(not ec);
    TEST_REQUIRE(is_directory(to));
    TEST_REQUIRE(not is_regular_file(to_f1));
    TEST_REQUIRE(is_directory(to_d1));
    TEST_REQUIRE(not is_regular_file(to_f2));
}

TEST_CASE(not_status_known_for_to)
{
    scoped_test_env env;
    path const from = env.make_env_path("from");
    path const to_dir = env.make_env_path("to_dir");
    path const to = to_dir / "to";
    
    env.create_file(from, 42);
    env.create_dir(to_dir);
    
    permissions(to_dir, perms::none);
    
    {
        std::error_code ec;
        copy(from, to, ec);
        TEST_REQUIRE(ec);
    }
    {
        TEST_REQUIRE_THROW(filesystem_error, copy(from, to));
    }
}

TEST_SUITE_END()