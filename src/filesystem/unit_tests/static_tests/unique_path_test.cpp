#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include <elib/filesystem.hpp>
#include <system_error>
#include "../static_test_helper.hpp"
using namespace elib::fs;

BOOST_AUTO_TEST_SUITE(elib_filesystem_static_unique_path_test_suite)

BOOST_AUTO_TEST_CASE(default_model_test)
{
    path p1 = unique_path();
    path p2 = unique_path();
    path p3 = unique_path();
    
    // size of "%%%%-%%%%-%%%%-%%%%"
    BOOST_CHECK(p1.native().size() == 19);
    BOOST_CHECK(p2.native().size() == 19);
    BOOST_CHECK(p2.native().size() == 19);
    
    // Use two paths in case p1 == p2 or p1 == p3.
    BOOST_CHECK(p1 != p2 || p1 != p3);
}

BOOST_AUTO_TEST_CASE(custom_model_test)
{
    std::error_code ec;
    
    path p1 = unique_path("test-%%%%", ec);
    BOOST_REQUIRE(not ec);
    
    path p2 = unique_path("test-%%%%", ec);
    BOOST_REQUIRE(not ec);
    
    path p3 = unique_path("test-%%%%", ec);
    BOOST_REQUIRE(not ec);
    
    BOOST_CHECK(p1.native().size() == 9);
    BOOST_CHECK(p2.native().size() == 9);
    BOOST_CHECK(p2.native().size() == 9);
    
    // Use two paths in case p1 == p2 or p1 == p3.
    BOOST_CHECK(p1 != p2 || p1 != p3);
    BOOST_CHECK(p1.native().substr(0, 5) == "test-");
    BOOST_CHECK(p2.native().substr(0, 5) == "test-");
    BOOST_CHECK(p3.native().substr(0, 5) == "test-");
}

BOOST_AUTO_TEST_SUITE_END()