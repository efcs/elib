#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include <elib/filesystem.hpp>
#include <system_error>
#include <cstdint>
#include "../dynamic_test_helper.hpp"
using namespace elib::fs;

constexpr const std::uintmax_t bad_count = static_cast<std::uintmax_t>(-1);

BOOST_AUTO_TEST_SUITE(elib_filesystem_dynamic_hard_link_count_test_suite)

BOOST_AUTO_TEST_CASE(dne_test)
{
    scoped_test_env env;
    path const file = env.make_env_path("dne");
    
    {
        std::error_code ec;
        std::uintmax_t count = hard_link_count(file, ec);
        BOOST_REQUIRE(ec);
        BOOST_CHECK(count == bad_count);
    }
    {
        BOOST_REQUIRE_THROW(hard_link_count(file), filesystem_error);
    }
}

BOOST_AUTO_TEST_CASE(basic_test)
{
    scoped_test_env env;
    path const file = env.make_env_path("file1");
    env.create_file(file);
    
    std::error_code ec;
    std::uintmax_t count = hard_link_count(file, ec);
    BOOST_REQUIRE(not ec);
    BOOST_REQUIRE(count == 1);
    
    path const link = env.make_env_path("link1");
    env.create_hardlink(file, link);
    
    count = hard_link_count(file, ec);
    BOOST_REQUIRE(not ec);
    BOOST_CHECK(count == 2);
}

BOOST_AUTO_TEST_SUITE_END()