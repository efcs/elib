#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include <elib/filesystem.hpp>
#include <system_error>
#include "../static_test_helper.hpp"
using namespace elib::fs;


BOOST_AUTO_TEST_SUITE(elib_filesystem_static_current_path_test_suite)

BOOST_AUTO_TEST_CASE(set_and_get_test)
{
    const path curr_path = current_path();
    
    std::error_code ec;
    current_path(test_root, ec);
    BOOST_REQUIRE(not ec);
    
    BOOST_CHECK(current_path() == test_root);
    
    BOOST_REQUIRE_NO_THROW(current_path(elib_root));
    BOOST_CHECK(current_path() == elib_root);
    
    BOOST_REQUIRE_NO_THROW(current_path(curr_path));
    BOOST_CHECK(current_path() == curr_path);
}

BOOST_AUTO_TEST_CASE(bad_set_test)
{
    const path curr_path = current_path();
    
    const path new_path = make_static_env_path("dne");
    std::error_code ec;
    current_path(new_path, ec);
    BOOST_REQUIRE(ec);
    BOOST_CHECK(current_path() == curr_path);
    
    current_path(curr_path);
}

BOOST_AUTO_TEST_SUITE_END()