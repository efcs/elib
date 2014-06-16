// REQUIRES: ELIB_FILESYSTEM_SOURCE
#include <elib/config.hpp>
#include <elib/filesystem.hpp>
#include <system_error>
#include "../dynamic_test_helper.hpp"
#include "rapid-cxx-test.hpp"
using namespace elib::fs;

TEST_SUITE(remove_all_bad_perms_testsuite)

TEST_CASE(remove_all_bad_perms_test)
{
#if defined(ELIB_CONFIG_CYGWIN)
    TEST_UNSUPPORTED();
#endif
    scoped_test_env env;
    path const dir1 = env.make_env_path("dir1");
    path const dir2 = dir1 / "dir2";
    env.create_dir(dir1);
    
    constexpr const std::uintmax_t bad_count = static_cast<std::uintmax_t>(-1);
    
    permissions(dir1, perms::none);
    
    {
        std::error_code ec;
        auto ret = remove_all(dir2, ec);
        TEST_CHECK(ec);
        TEST_CHECK(ret == bad_count);
    }{
        TEST_CHECK_THROW(filesystem_error, remove_all(dir2));
    }
    permissions(dir1, perms::all);
}

TEST_SUITE_END()