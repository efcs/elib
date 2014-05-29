#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include <elib/filesystem.hpp>
#include <system_error>
#include "../dynamic_test_helper.hpp"
using namespace elib::fs;

BOOST_AUTO_TEST_SUITE(elib_filesystem_dynamic_copy_test_test_suite)

BOOST_AUTO_TEST_CASE(from_dne_test)
{
    scoped_test_env env;
    path const file = make_env_path("dne");
    path const to = make_env_path("dne2");
    
    {
        std::error_code ec;
        copy(file, to, ec);
        BOOST_REQUIRE(ec);
    }
    {
        BOOST_REQUIRE_THROW(copy(file, to), filesystem_error);
    }
}

BOOST_AUTO_TEST_CASE(equivalent_test)
{
    scoped_test_env env;
    path const file = make_env_path("file1");
    python_create_file(file);
    
    std::error_code ec;
    copy(file, file, ec);
    BOOST_REQUIRE(ec);
}

BOOST_AUTO_TEST_CASE(from_is_other)
{
    scoped_test_env env;
    path const file = make_env_path("file1");
    path const to = make_env_path("file2");
    python_create_socket(file);
    
    std::error_code ec;
    copy(file, to, ec);
    BOOST_REQUIRE(ec);
}

BOOST_AUTO_TEST_CASE(to_is_other)
{
    scoped_test_env env;
    path const file = make_env_path("file1");
    path const to = make_env_path("file2");
    python_create_file(file);
    python_create_socket(to);
    
    std::error_code ec;
    copy(file, to, ec);
    BOOST_REQUIRE(ec);
}

BOOST_AUTO_TEST_CASE(directory_to_regular_file_test)
{
    scoped_test_env env;
    path const file = make_env_path("file1");
    path const to = make_env_path("file2");
    python_create_dir(file);
    python_create_file(to);
    
    std::error_code ec;
    copy(file, to, ec);
    BOOST_REQUIRE(ec);
}

BOOST_AUTO_TEST_CASE(skip_symlinks_test)
{
    scoped_test_env env;
    path const real_file = make_env_path("real_file");
    path const file = make_env_path("sym1");
    path const to = make_env_path("to");
    
    python_create_file(real_file);
    python_create_symlink(real_file, file);
    
    std::error_code ec;
    copy(file, to, copy_options::skip_symlinks, ec);
    BOOST_CHECK(not ec);
    BOOST_REQUIRE(not exists(to));
}

BOOST_AUTO_TEST_CASE(copy_symlink_test)
{
    scoped_test_env env;
    path const real_file = make_env_path("real_file");
    path const file = make_env_path("sym1");
    path const to = make_env_path("to");
    
    python_create_file(real_file);
    python_create_symlink(real_file, file);
    
    std::error_code ec;
    copy(file, to, copy_options::create_symlinks, ec);
    BOOST_CHECK(not ec);
    BOOST_REQUIRE(is_symlink(to));
    BOOST_REQUIRE(read_symlink(to) == real_file);
}

BOOST_AUTO_TEST_CASE(copy_symlink_to_exists_test)
{
    scoped_test_env env;
    path const real_file = make_env_path("real_file");
    path const file = make_env_path("sym1");
    path const to = make_env_path("to");
    
    python_create_file(real_file);
    python_create_symlink(real_file, file);
    python_create_file(to);
    
    std::error_code ec;
    copy(file, to, copy_options::create_symlinks, ec);
    BOOST_CHECK(ec);
    BOOST_REQUIRE(not is_symlink(to));
    BOOST_REQUIRE(is_regular_file(to));
}

BOOST_AUTO_TEST_CASE(directory_only_regular_file_test)
{
    scoped_test_env env;
    path const file = make_env_path("file1");
    path const to = make_env_path("to");
    
    python_create_file(file);
    
    std::error_code ec;
    copy(file, to, copy_options::directories_only, ec);
    BOOST_REQUIRE(not ec);
    BOOST_REQUIRE(not exists(to));
}

BOOST_AUTO_TEST_CASE(regular_file_create_symlinks_test)
{
    scoped_test_env env;
    path const file = make_env_path("file1");
    path const to = make_env_path("to");
    
    python_create_file(file);
    
    std::error_code ec;
    copy(file, to, copy_options::create_symlinks, ec);
    BOOST_CHECK(not ec);
    BOOST_REQUIRE(is_symlink(to));
    BOOST_REQUIRE(read_symlink(to) == file);
}

BOOST_AUTO_TEST_CASE(regular_file_create_hard_link_test)
{
    scoped_test_env env;
    path const file = make_env_path("file1");
    path const to = make_env_path("to");
    
    python_create_file(file);
    
    std::error_code ec;
    copy(file, to, copy_options::create_hard_links, ec);
    BOOST_CHECK(not ec);
    BOOST_CHECK(is_regular_file(to));
    BOOST_REQUIRE(hard_link_count(file) == 2);
}

BOOST_AUTO_TEST_CASE(regular_file_copy_to_dir)
{
    scoped_test_env env;
    path const file = make_env_path("file1");
    path const to_dir = make_env_path("dir1");
    path const to = to_dir / "file1";
    
    python_create_file(file);
    python_create_dir(to_dir);
    
    std::error_code ec;
    copy(file, to_dir, ec);
    BOOST_CHECK(not ec);
    BOOST_CHECK(is_regular_file(to));
}

BOOST_AUTO_TEST_CASE(regular_file_copy)
{
    scoped_test_env env;
    path const file = make_env_path("file");
    path const to = make_env_path("to");
    
    python_create_file(file);
    
    std::error_code ec;
    copy(file, to, ec);
    BOOST_REQUIRE(not ec);
    BOOST_REQUIRE(is_regular_file(to));
}


BOOST_AUTO_TEST_SUITE_END()