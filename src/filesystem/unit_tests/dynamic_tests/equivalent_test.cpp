#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include <elib/filesystem.hpp>
#include <system_error>
#include "../dynamic_test_helper.hpp"
using namespace elib::fs;

BOOST_AUTO_TEST_SUITE(elib_filesystem_dynamic_equivalent_test_suite)

BOOST_AUTO_TEST_CASE(both_dne_test)
{
    scoped_test_env env;
    path const p1 = make_env_path("dne1");
    path const p2 = make_env_path("dne2");
    
    {
        std::error_code ec;
        BOOST_REQUIRE(not equivalent(p1, p2, ec));
        BOOST_REQUIRE(not ec);
    }
    {
        bool ret{};
        BOOST_REQUIRE_NO_THROW(ret = equivalent(p1, p2));
        BOOST_REQUIRE(not ret);
    }
}

BOOST_AUTO_TEST_CASE(one_dne_test)
{
    scoped_test_env env;
    path const p1 = make_env_path("file1");
    path const p2 = make_env_path("dne2");
    python_create_file(p1);
    
    {
        std::error_code ec;
        BOOST_REQUIRE(not equivalent(p1, p2, ec));
        BOOST_REQUIRE(ec);
    }
    {
        BOOST_REQUIRE_THROW(equivalent(p1, p2), filesystem_error);
    }
}

BOOST_AUTO_TEST_CASE(not_equiv_both_exist)
{
    scoped_test_env env;
    path const p1 = make_env_path("file1");
    path const p2 = make_env_path("dir1");
    python_create_file(p1);
    python_create_dir(p2);
    
    {
        std::error_code ec;
        BOOST_REQUIRE(not equivalent(p1, p2, ec));
        BOOST_REQUIRE(not ec);
    }
    {
        bool ret{};
        BOOST_REQUIRE_NO_THROW(ret = equivalent(p1, p2));
        BOOST_REQUIRE(not ret);
    }
}

BOOST_AUTO_TEST_CASE(same_file_test)
{
    scoped_test_env env;
    path const p1 = make_env_path("file1");
    path const p2 = make_env_path("file1");
    python_create_file(p1);
    
    {
        std::error_code ec;
        BOOST_REQUIRE(equivalent(p1, p2, ec));
        BOOST_REQUIRE(not ec);
    }
    {
        bool ret{};
        BOOST_REQUIRE_NO_THROW(ret = equivalent(p1, p2));
        BOOST_REQUIRE(ret);
    } 
}

BOOST_AUTO_TEST_CASE(symlink_test)
{
    scoped_test_env env;
    path const p1 = make_env_path("file1");
    path const p2 = make_env_path("sym1");
    python_create_file(p1);
    python_create_symlink(p1, p2);
    
    {
        std::error_code ec;
        BOOST_REQUIRE(equivalent(p1, p2, ec));
        BOOST_REQUIRE(not ec);
    }
    {
        bool ret{};
        BOOST_REQUIRE_NO_THROW(ret = equivalent(p1, p2));
        BOOST_REQUIRE(ret);
    }
}

BOOST_AUTO_TEST_CASE(hardlink_test)
{
    scoped_test_env env;
    path const p1 = make_env_path("file1");
    path const p2 = make_env_path("link1");
    python_create_file(p1);
    python_create_hardlink(p1, p2);
    
    {
        std::error_code ec;
        BOOST_REQUIRE(equivalent(p1, p2, ec));
        BOOST_REQUIRE(not ec);
    }
    {
        bool ret;
        BOOST_REQUIRE_NO_THROW(ret = equivalent(p1, p2));
        BOOST_REQUIRE(ret);
    }
}

BOOST_AUTO_TEST_CASE(different_paths_same_file_test)
{
    scoped_test_env env;
    path const p1 = make_env_path("file1");
    path const p2 = test_env_path / "../test_env/./file1";
    python_create_file(p1);
    python_create_dir(p2);
    
    {
        std::error_code ec;
        BOOST_REQUIRE(equivalent(p1, p2, ec));
        BOOST_REQUIRE(not ec);
    }
    {
        bool ret;
        BOOST_REQUIRE_NO_THROW(ret = equivalent(p1, p2));
        BOOST_REQUIRE(ret);
    }
}

BOOST_AUTO_TEST_CASE(two_symlinks_to_same_file_test)
{
    scoped_test_env env;
    path const real_file = make_env_path("real_file");
    path const p1 = make_env_path("sym1");
    path const p2 = make_env_path("sym2");
    python_create_file(real_file);
    python_create_symlink(real_file, p1);
    python_create_symlink(real_file, p2);
    
    {
        std::error_code ec;
        BOOST_REQUIRE(equivalent(p1, p2, ec));
        BOOST_REQUIRE(not ec);
    }
    {
        bool ret;
        BOOST_REQUIRE_NO_THROW(ret = equivalent(p1, p2));
        BOOST_REQUIRE(ret);
    }
}

BOOST_AUTO_TEST_SUITE_END()