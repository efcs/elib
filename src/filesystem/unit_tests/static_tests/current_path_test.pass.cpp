// REQUIRES: ELIB_FILESYSTEM
#include <elib/filesystem.hpp>
#include <system_error>
#include "../static_test_helper.hpp"
#include "rapid-cxx-test.hpp"
using namespace elib::fs;


TEST_SUITE(elib_filesystem_static_current_path_test_suite)

TEST_CASE(set_and_get_test)
{
    const path curr_path = current_path();
    
    std::error_code ec;
    current_path(ELIB_FILESYSTEM_UNIT_TEST_PATH, ec);
    TEST_REQUIRE(not ec);
    
    TEST_CHECK(current_path() == ELIB_FILESYSTEM_UNIT_TEST_PATH);
    
    TEST_REQUIRE_NO_THROW(current_path(ELIB_ROOT_PATH));
    TEST_CHECK(current_path() == ELIB_ROOT_PATH);
    
    TEST_REQUIRE_NO_THROW(current_path(curr_path));
    TEST_CHECK(current_path() == curr_path);
}

TEST_CASE(bad_set_test)
{
    const path curr_path = current_path();
    
    const path new_path = make_static_env_path("dne");
    {
        std::error_code ec;
        current_path(new_path, ec);
        TEST_REQUIRE(ec);
        TEST_CHECK(current_path() == curr_path);
    }
    {
        TEST_REQUIRE_THROW(filesystem_error,  current_path(new_path));
    }
        
    current_path(curr_path);
}

TEST_SUITE_END()