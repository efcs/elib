#define BOOST_TEST_MODULE Main
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include <elib/filesystem.hpp>
#include <system_error>
#include <cstdint>
#include "../static_test_helper.hpp"
using namespace elib::fs;

constexpr const std::uintmax_t bad_size = static_cast<std::uintmax_t>(-1);

BOOST_AUTO_TEST_SUITE(elib_filesystem_static_space_test_suite)

BOOST_AUTO_TEST_CASE(dne_test)
{
    const path file = make_static_env_path("dne");
    
    {
        std::error_code ec;
        space_info info = space(file, ec);
        BOOST_REQUIRE(ec);
        BOOST_CHECK(info.capacity == bad_size);
        BOOST_CHECK(info.free == bad_size);
        BOOST_CHECK(info.available == bad_size);
    }
    {
        BOOST_REQUIRE_THROW(space(file), filesystem_error);
    }
}

BOOST_AUTO_TEST_CASE(file_test)
{
    const path file = make_static_env_path("empty_file");
    
    std::error_code ec;
    space_info info = space(file, ec);
    BOOST_REQUIRE(not ec);
    BOOST_CHECK(info.capacity > 0);
    BOOST_CHECK(info.free > 0 && info.free < info.capacity);
    BOOST_CHECK(info.available > 0 && info.available < info.capacity);
}

BOOST_AUTO_TEST_SUITE_END()