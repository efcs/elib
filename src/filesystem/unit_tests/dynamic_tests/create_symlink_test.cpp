#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include <elib/filesystem.hpp>
#include <system_error>
#include "../dynamic_test_helper.hpp"
using namespace elib::fs;

BOOST_AUTO_TEST_SUITE(elib_filesystem_dynamic_create_symlink_test_suite)

BOOST_AUTO_TEST_CASE(dne_test)
{
    scoped_test_env env;
    path const file = make_env_path("dne");
    path const to = make_env_path("sym1");
    
    // with error code
    std::error_code ec;
    create_symlink(file, to, ec);
    BOOST_REQUIRE(not ec);
    BOOST_REQUIRE(is_symlink(to));
}

BOOST_AUTO_TEST_CASE(dne_no_error_code_test)
{
    scoped_test_env env;
    path const file = make_env_path("dne");
    path const to = make_env_path("sym1");
    
    // with error code
    BOOST_REQUIRE_NO_THROW(create_symlink(file, to));
    BOOST_REQUIRE(is_symlink(to));
}

BOOST_AUTO_TEST_CASE(file_test)
{
    scoped_test_env env;
    path const file = make_env_path("file1");
    path const to = make_env_path("sym1");
    
    python_create_file(file);
 
    std::error_code ec;
    create_symlink(file, to, ec);
    BOOST_REQUIRE(not ec);
    BOOST_REQUIRE(is_regular_file(file));
    BOOST_REQUIRE(is_symlink(to));
    BOOST_REQUIRE(read_symlink(to).native() == file.native());
}

BOOST_AUTO_TEST_CASE(directory_test)
{
    scoped_test_env env;
    path const file = make_env_path("file1");
    path const to = make_env_path("sym1");
    
    python_create_dir(file);
 
    std::error_code ec;
    create_symlink(file, to, ec);
    BOOST_REQUIRE(not ec);
    BOOST_REQUIRE(is_directory(file));
    BOOST_REQUIRE(is_symlink(to));
    BOOST_REQUIRE(read_symlink(to) == file);
}

BOOST_AUTO_TEST_CASE(symlink_test)
{
    scoped_test_env env;
    path const real_file = make_env_path("real_file");
    path const file = make_env_path("file1");
    path const to = make_env_path("sym1");
    
    python_create_file(real_file);
    python_create_symlink(real_file, file);
 
    std::error_code ec;
    create_symlink(file, to, ec);
    BOOST_REQUIRE(not ec);
    BOOST_REQUIRE(is_symlink(to));
    BOOST_REQUIRE(read_symlink(to) == file);
}

BOOST_AUTO_TEST_SUITE_END()