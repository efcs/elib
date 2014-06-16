// REQUIRES: ELIB_FILESYSTEM_SOURCE
#include <elib/config.hpp>
#include <elib/filesystem.hpp>
#include <system_error>
#include "../dynamic_test_helper.hpp"
#include "rapid-cxx-test.hpp"
using namespace elib::fs;

TEST_SUITE(elib_filesystem_dynamic_status_bad_perms_test_suite)

TEST_CASE(status_bad_perms_test)
{
#if !defined(ELIB_CONFIG_CYGWIN)
    scoped_test_env env;
    path const dir = env.make_env_path("dir1");
    path const file = dir / "file1";
    
    env.create_dir(dir);
    env.create_file(file, 42);
    
    permissions(dir, perms::none);
    
    {
        TEST_CHECK_THROW(filesystem_error, status(file));
        TEST_CHECK_THROW(filesystem_error, symlink_status(file));
    }
    {
        std::error_code ec;
        file_status st = status(file, ec);
        TEST_CHECK(ec);
        TEST_CHECK(not status_known(st));
    }
    {
        std::error_code ec;
        file_status st = symlink_status(file, ec);
        TEST_CHECK(ec);
        TEST_CHECK(not status_known(st));
    }
    
    permissions(dir, perms::all);
#else /* ELIB_CONFIG_CYGWIN */
    TEST_CHECK(true);
#endif
}

TEST_SUITE_END()