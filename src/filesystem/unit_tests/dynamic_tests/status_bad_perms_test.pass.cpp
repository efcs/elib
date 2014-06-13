// REQUIRES: ELIB_FILESYSTEM_SOURCE, ELIB_BOOST_TEST
#define BOOST_TEST_MODULE Main
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include <elib/config.hpp>
#include <elib/filesystem.hpp>
#include <system_error>
#include "../dynamic_test_helper.hpp"
using namespace elib::fs;

BOOST_AUTO_TEST_SUITE(elib_filesystem_dynamic_status_bad_perms_test_suite)

BOOST_AUTO_TEST_CASE(status_bad_perms_test)
{
#if !defined(ELIB_CONFIG_CYGWIN)
    scoped_test_env env;
    path const dir = env.make_env_path("dir1");
    path const file = dir / "file1";
    
    env.create_dir(dir);
    env.create_file(file, 42);
    
    permissions(dir, perms::none);
    
    {
        BOOST_CHECK_THROW(status(file), filesystem_error);
        BOOST_CHECK_THROW(symlink_status(file), filesystem_error);
    }
    {
        std::error_code ec;
        file_status st = status(file, ec);
        BOOST_CHECK(ec);
        BOOST_CHECK(not status_known(st));
    }
    {
        std::error_code ec;
        file_status st = symlink_status(file, ec);
        BOOST_CHECK(ec);
        BOOST_CHECK(not status_known(st));
    }
    
    permissions(dir, perms::all);
#else /* ELIB_CONFIG_CYGWIN */
    BOOST_CHECK(true);
#endif
}

BOOST_AUTO_TEST_SUITE_END()