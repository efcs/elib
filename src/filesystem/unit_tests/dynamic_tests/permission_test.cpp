#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include <elib/config.hpp>
#include <elib/filesystem.hpp>
#include <system_error>
#include "../dynamic_test_helper.hpp"

#include <sys/stat.h>
#include <fcntl.h>

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

// linux doesn't support permissions on symlinks
#if defined(AT_SYMLINK_NOFOLLOW) && defined(AT_FDCWD) && !defined(ELIB_CONFIG_LINUX)
BOOST_AUTO_TEST_CASE(not_follow_symlink_test)
{
    scoped_test_env env;
    path const real_file = make_env_path("real_file");
    path const file = make_env_path("sym");
    
    python_create_file(real_file, 42);
    python_create_symlink(real_file, file);
    
    BOOST_REQUIRE_NO_THROW(permissions(real_file, perms::all));
    
    perms const pm = perms::owner_all;
    std::error_code ec;
    permissions(file, pm, ec);
    BOOST_REQUIRE(not ec);
        
    auto rst = status(real_file);
    auto lst = symlink_status(file);
    BOOST_CHECK(rst.permissions() == perms::all);
    BOOST_CHECK(lst.permissions() == pm);
}
# endif 

BOOST_AUTO_TEST_CASE(follow_symlink_test)
{
    scoped_test_env env;
    path const real_file = make_env_path("real_file");
    path const file = make_env_path("sym");
    
    python_create_file(real_file, 42);
    python_create_symlink(real_file, file);
    
    BOOST_REQUIRE_NO_THROW(permissions(real_file, perms::group_all|perms::owner_all));
    
    perms const pm = perms::owner_all;
    std::error_code ec;
    permissions(file, pm, permissions_options::follow_symlinks, ec);
    BOOST_REQUIRE(not ec);
        
    auto rst = status(real_file);
    auto lst = symlink_status(file);
    BOOST_CHECK(rst.permissions() == pm);
    
/// On linux a symlinks permissions are always 0777 (perms::all)
#if defined(AT_SYMLINK_NOFOLLOW) && defined(AT_FDCWD) && !defined(ELIB_CONFIG_LINUX)
    BOOST_CHECK(lst.permissions() == pm);
#else
    BOOST_CHECK(lst.permissions() == perms::all);
#endif
}

BOOST_AUTO_TEST_SUITE_END()