// REQUIRES: ELIB_FILESYSTEM_SOURCE
#include <elib/filesystem.hpp>
#include <system_error>
#include "../dynamic_test_helper.hpp"
#include "rapid-cxx-test.hpp"
using namespace elib::fs;


TEST_SUITE(elib_filesystem_dynamic_read_symlink_test_suite)

TEST_CASE(symlink_test)
{
    scoped_test_env env;
    const path file = env.make_env_path("file1");
    const path sym = env.make_env_path("sym1");
    env.create_file(file);
    env.create_symlink(file, sym);
    // with error code
    {
        std::error_code ec;
        path ret = read_symlink(sym, ec);
        TEST_REQUIRE(not ec);
        TEST_REQUIRE(ret == file);
    }
    // no error code
    {
        path ret;
        TEST_REQUIRE_NO_THROW(ret = read_symlink(sym));
        TEST_REQUIRE(ret == file);
    }
}

TEST_SUITE_END()
