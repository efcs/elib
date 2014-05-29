#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include <elib/filesystem.hpp>
#include <system_error>
#include "../dynamic_test_helper.hpp"
using namespace elib::fs;

BOOST_AUTO_TEST_SUITE(elib_filesystem_dynamic_permission_test_suite)

BOOST_AUTO_TEST_CASE(dne_test)
{
    scoped_test_env env;
    const path file = make_env_path("dne");
    
    {
        std::error_code ec;
        permissions(file, perms::none, ec);
        BOOST_REQUIRE(ec);
        
        ec.clear();
        permissions(file, perms::none, permissions_options::replace_bits, ec);
        BOOST_REQUIRE(ec);
    }
    {
        BOOST_REQUIRE_THROW(permissions(file, perms::none), filesystem_error);
        BOOST_REQUIRE_THROW(
            permissions(file, perms::none, permissions_options::replace_bits)
          , filesystem_error
          );
    }
}

BOOST_AUTO_TEST_CASE(replace_permissions_test)
{
    scoped_test_env env;
    const path file = make_env_path("file1");
    python_create_file(file);
    
    std::error_code ec;
    
    permissions(file, perms::group_all, ec);
    BOOST_REQUIRE(not ec);
    
    file_status st = status(file);
    BOOST_REQUIRE(st.permissions() == perms::group_all);
    
    permissions(file, perms::owner_all, ec);
    BOOST_REQUIRE(not ec);
    
    st = status(file);
    BOOST_REQUIRE(st.permissions() == perms::owner_all);
}

BOOST_AUTO_TEST_CASE(add_permissions_test)
{
    scoped_test_env env;
    const path file = make_env_path("file1");
    python_create_file(file);
    
    std::error_code ec;
    
    permissions(file, perms::group_all, ec);
    BOOST_REQUIRE(not ec);
    
    file_status st = status(file);
    BOOST_REQUIRE(st.permissions() == perms::group_all);
    
    permissions(file, perms::owner_all, permissions_options::add_bits, ec);
    BOOST_REQUIRE(not ec);
    
    st = status(file);
    BOOST_REQUIRE(st.permissions() == (perms::owner_all | perms::group_all));
}

BOOST_AUTO_TEST_CASE(remove_permissions_test)
{
    scoped_test_env env;
    const path file = make_env_path("file1");
    python_create_file(file);
    
    std::error_code ec;
    
    permissions(file, perms::owner_all | perms::group_all, ec);
    BOOST_REQUIRE(not ec);
    
    file_status st = status(file);
    BOOST_REQUIRE(st.permissions() == (perms::owner_all | perms::group_all));
    
    permissions(file, perms::group_all, permissions_options::remove_bits, ec);
    BOOST_REQUIRE(not ec);
    
    st = status(file);
    BOOST_REQUIRE(st.permissions() == perms::owner_all);
}

BOOST_AUTO_TEST_SUITE_END()