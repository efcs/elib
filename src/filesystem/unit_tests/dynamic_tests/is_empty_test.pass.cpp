// REQUIRES: ELIB_FILESYSTEM_SOURCE
#define BOOST_TEST_MODULE Main
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include <elib/filesystem.hpp>
#include <system_error>
#include "../dynamic_test_helper.hpp"
using namespace elib::fs;

/// NOTE: most test cases are handled in the static tests
BOOST_AUTO_TEST_SUITE(elib_filesystem_dynamic_is_empty_operation_test_suite)

/// Empty directories cannot be tested staticly because of git.
BOOST_AUTO_TEST_CASE(empty_directory_test)
{
    scoped_test_env env;
    const path file = env.make_env_path("empty_dir");
    env.create_dir(file);
    
    // with error code
    {
        std::error_code ec;
        bool ret = is_empty(file, ec);
        BOOST_REQUIRE(not ec);
        BOOST_REQUIRE(ret);
    }
    // without error code
    {
        bool ret = false;
        BOOST_REQUIRE_NO_THROW(ret = is_empty(file));
        BOOST_REQUIRE(ret);
    }
}

BOOST_AUTO_TEST_SUITE_END()