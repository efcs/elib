// REQUIRES: ELIB_MEMORY_SOURCE
#include <elib/memory/make_unique.hpp>
#include <memory>
#include <string>

#include "rapid-cxx-test.hpp"


TEST_SUITE(elib_memory_make_unique_test_suite)

TEST_CASE(make_unique_single_object)
{
    std::unique_ptr<std::string> u = elib::make_unique<std::string>("Hello");
    TEST_REQUIRE(bool(u));
    TEST_CHECK(*u == "Hello");
}

TEST_CASE(make_unique_default_init_single_object)
{
    std::unique_ptr<std::string> u = elib::make_unique_default_init<std::string>();
    TEST_REQUIRE(bool(u));
    TEST_CHECK(*u == "");
}

TEST_CASE(make_unique_array)
{
    std::unique_ptr<int[]> u = elib::make_unique<int[]>(3);
    TEST_REQUIRE(bool(u));
    TEST_CHECK(u[0] == 0);
    TEST_CHECK(u[1] == 0);
    TEST_CHECK(u[2] == 0);
}

TEST_CASE(make_unique_default_init_array)
{
    std::unique_ptr<std::string[]> u = 
        elib::make_unique_default_init<std::string[]>(3);
        
    TEST_REQUIRE(bool(u));
    TEST_CHECK(u[0] == "");
    TEST_CHECK(u[1] == "");
    TEST_CHECK(u[2] == "");
}

TEST_CASE(make_unique_value_init_array)
{
    std::unique_ptr<int[]> u =
        elib::make_unique_value_init<int[]>(3, 0, 1, 2);
        
    TEST_REQUIRE(bool(u));
    TEST_CHECK(u[0] == 0);
    TEST_CHECK(u[1] == 1);
    TEST_CHECK(u[2] == 2);
}

TEST_CASE(make_unique_auto_size_array)
{
    std::unique_ptr<int[]> u = 
        elib::make_unique_auto_size<int[]>(0, 1, 2);
        
    TEST_REQUIRE(bool(u));
    TEST_CHECK(u[0] == 0);
    TEST_CHECK(u[1] == 1);
    TEST_CHECK(u[2] == 2);
}

TEST_SUITE_END()