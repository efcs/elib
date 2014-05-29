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

BOOST_AUTO_TEST_SUITE_END()