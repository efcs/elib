#define BOOST_TEST_MODULE Main
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include <elib/memory/make_unique.hpp>
#include <memory>
#include <string>


BOOST_AUTO_TEST_SUITE(elib_memory_make_unique_test_suite)

BOOST_AUTO_TEST_CASE(make_unique_single_object)
{
    std::unique_ptr<std::string> u = elib::make_unique<std::string>("Hello");
    BOOST_REQUIRE(bool(u));
    BOOST_CHECK(*u == "Hello");
}

BOOST_AUTO_TEST_CASE(make_unique_default_init_single_object)
{
    std::unique_ptr<std::string> u = elib::make_unique_default_init<std::string>();
    BOOST_REQUIRE(bool(u));
    BOOST_CHECK(*u == "");
}

BOOST_AUTO_TEST_CASE(make_unique_array)
{
    std::unique_ptr<int[]> u = elib::make_unique<int[]>(3);
    BOOST_REQUIRE(bool(u));
    BOOST_CHECK(u[0] == 0);
    BOOST_CHECK(u[1] == 0);
    BOOST_CHECK(u[2] == 0);
}

BOOST_AUTO_TEST_CASE(make_unique_default_init_array)
{
    std::unique_ptr<std::string[]> u = 
        elib::make_unique_default_init<std::string[]>(3);
        
    BOOST_REQUIRE(bool(u));
    BOOST_CHECK(u[0] == "");
    BOOST_CHECK(u[1] == "");
    BOOST_CHECK(u[2] == "");
}

BOOST_AUTO_TEST_CASE(make_unique_value_init_array)
{
    std::unique_ptr<int[]> u =
        elib::make_unique_value_init<int[]>(3, 0, 1, 2);
        
    BOOST_REQUIRE(bool(u));
    BOOST_CHECK(u[0] == 0);
    BOOST_CHECK(u[1] == 1);
    BOOST_CHECK(u[2] == 2);
}

BOOST_AUTO_TEST_CASE(make_unique_auto_size_array)
{
    std::unique_ptr<int[]> u = 
        elib::make_unique_auto_size<int[]>(0, 1, 2);
        
    BOOST_REQUIRE(bool(u));
    BOOST_CHECK(u[0] == 0);
    BOOST_CHECK(u[1] == 1);
    BOOST_CHECK(u[2] == 2);
}

BOOST_AUTO_TEST_SUITE_END()