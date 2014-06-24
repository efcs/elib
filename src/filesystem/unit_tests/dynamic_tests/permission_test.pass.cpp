// REQUIRES: ELIB_FILESYSTEM, ELIB_PYTHON_EXECUTABLE
#include <elib/config.hpp>
#include <elib/filesystem.hpp>
#include <system_error>
#include <sys/stat.h>
#include <fcntl.h>
#include "../dynamic_test_helper.hpp"
#include "rapid-cxx-test.hpp"



using namespace elib::fs;

TEST_SUITE(elib_filesystem_dynamic_permission_test_suite)

TEST_CASE(dne_test)
{
    scoped_test_env env;
    const path file = env.make_env_path("dne");
    
    {
        std::error_code ec;
        permissions(file, perms::none, ec);
        TEST_REQUIRE(ec);
        
        ec.clear();
        permissions(file, perms::none, ec);
        TEST_REQUIRE(ec);
    }
    {
        TEST_REQUIRE_THROW(filesystem_error, permissions(file, perms::none));
        TEST_REQUIRE_THROW(filesystem_error, permissions(file, perms::none));
    }
}

TEST_CASE(replace_permissions_test)
{
    scoped_test_env env;
    const path file = env.make_env_path("file1");
    env.create_file(file);
    
    std::error_code ec;
    
    permissions(file, perms::group_all, ec);
    TEST_REQUIRE(not ec);
    
    file_status st = status(file);
    TEST_REQUIRE(st.permissions() == perms::group_all);
    
    permissions(file, perms::owner_all, ec);
    TEST_REQUIRE(not ec);
    
    st = status(file);
    TEST_REQUIRE(st.permissions() == perms::owner_all);
}

TEST_CASE(add_permissions_test)
{
    scoped_test_env env;
    const path file = env.make_env_path("file1");
    env.create_file(file);
    
    std::error_code ec;
    
    permissions(file, perms::group_all, ec);
    TEST_REQUIRE(not ec);
    
    file_status st = status(file);
    TEST_REQUIRE(st.permissions() == perms::group_all);
    
    permissions(file, perms::owner_all|perms::add_perms, ec);
    TEST_REQUIRE(not ec);
    
    st = status(file);
    TEST_REQUIRE(st.permissions() == (perms::owner_all | perms::group_all));
}

TEST_CASE(remove_permissions_test)
{
    scoped_test_env env;
    const path file = env.make_env_path("file1");
    env.create_file(file);
    
    std::error_code ec;
    
    permissions(file, perms::owner_all | perms::group_all, ec);
    TEST_REQUIRE(not ec);
    
    file_status st = status(file);
    TEST_REQUIRE(st.permissions() == (perms::owner_all | perms::group_all));
    
    permissions(file, perms::group_all|perms::remove_perms, ec);
    TEST_REQUIRE(not ec);
    
    st = status(file);
    TEST_REQUIRE(st.permissions() == perms::owner_all);
}

// linux doesn't support permissions on symlinks
#if defined(AT_SYMLINK_NOFOLLOW) && defined(AT_FDCWD) && \
   !defined(ELIB_CONFIG_LINUX) && !defined(ELIB_CONFIG_CYGWIN)
TEST_CASE(not_follow_symlink_test)
{
    scoped_test_env env;
    path const real_file = env.make_env_path("real_file");
    path const file = env.make_env_path("sym");
    
    env.create_file(real_file, 42);
    env.create_symlink(real_file, file);
    
    TEST_REQUIRE_NO_THROW(permissions(real_file, perms::all));
    
    perms const pm = perms::owner_all;
    std::error_code ec;
    permissions(file, pm, ec);
    TEST_REQUIRE(not ec);
        
    auto rst = status(real_file);
    auto lst = symlink_status(file);
    TEST_CHECK(rst.permissions() == perms::all);
    TEST_CHECK(lst.permissions() == pm);
}
# endif 

TEST_CASE(follow_symlink_test)
{
    scoped_test_env env;
    path const real_file = env.make_env_path("real_file");
    path const file = env.make_env_path("sym");
    
    env.create_file(real_file, 42);
    env.create_symlink(real_file, file);
    
    TEST_REQUIRE_NO_THROW(permissions(real_file, perms::group_all|perms::owner_all));
    
#if !defined(ELIB_CONFIG_LINUX)
    auto before_lst = symlink_status(file);
#endif
    
    perms const pm = perms::owner_all;
    std::error_code ec;
    permissions(file, pm|perms::resolve_symlinks, ec);
    TEST_REQUIRE(not ec);
        
    auto rst = status(real_file);
    auto lst = symlink_status(file);
    TEST_CHECK(rst.permissions() == pm);
    
/// On linux a symlinks permissions are always 0777 (perms::all)
#if !defined(ELIB_CONFIG_LINUX)
    TEST_CHECK(lst.permissions() == before_lst.permissions());
# else /* LINUX */
    TEST_CHECK(lst.permissions() == perms::all);
#endif
}

TEST_SUITE_END()