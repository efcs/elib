// REQUIRES: ELIB_FILESYSTEM_SOURCE
#include <elib/filesystem.hpp>
#include <system_error>
#include "../static_test_helper.hpp"
#include "rapid-cxx-test.hpp"
using namespace elib::fs;

TEST_SUITE(elib_filesystem_static_unique_path_test_suite)

TEST_CASE(default_model_test)
{
    path p1 = unique_path();
    path p2 = unique_path();
    path p3 = unique_path();
    
    // size of "%%%%-%%%%-%%%%-%%%%"
    TEST_CHECK(p1.native().size() == 19);
    TEST_CHECK(p2.native().size() == 19);
    TEST_CHECK(p2.native().size() == 19);
    
    // Use two paths in case p1 == p2 or p1 == p3.
    TEST_CHECK(p1 != p2 || p1 != p3);
}

TEST_CASE(custom_model_test)
{
    std::error_code ec;
    
    path p1 = unique_path("test-%%%%", ec);
    TEST_REQUIRE(not ec);
    
    path p2 = unique_path("test-%%%%", ec);
    TEST_REQUIRE(not ec);
    
    path p3 = unique_path("test-%%%%", ec);
    TEST_REQUIRE(not ec);
    
    TEST_CHECK(p1.native().size() == 9);
    TEST_CHECK(p2.native().size() == 9);
    TEST_CHECK(p2.native().size() == 9);
    
    // Use two paths in case p1 == p2 or p1 == p3.
    TEST_CHECK(p1 != p2 || p1 != p3);
    TEST_CHECK(p1.native().substr(0, 5) == "test-");
    TEST_CHECK(p2.native().substr(0, 5) == "test-");
    TEST_CHECK(p3.native().substr(0, 5) == "test-");
}

TEST_SUITE_END()