// REQUIRES: ELIB_SOURCE
#include <elib/optional.hpp>
#include <string>
#include "rapid-cxx-test.hpp"
using opt = elib::optional<std::string>;

TEST_SUITE(elib_optional_string_swap_function_test_suite)

TEST_CASE(both_empty_swap_test)
{
    opt o1;
    opt o2;
    swap(o1, o2);
    TEST_CHECK(not o1.good() && not o2.good());
}

TEST_CASE(lhs_empty_rhs_not_empty_swap_test)
{
    std::string const s = "hello";
    opt o1;
    opt o2(s);
    swap(o1, o2);
    TEST_REQUIRE(o1.good() && not o2.good());
    TEST_CHECK(o1.value() == s);
}

TEST_CASE(rhs_empty_lhs_not_empty_swap_test)
{
    std::string const s = "hello";
    opt o1(s);
    opt o2;
    swap(o1, o2);
    TEST_REQUIRE(not o1.good() && o2.good());
    TEST_CHECK(o2.value() == s);
}

TEST_CASE(both_non_empty_swap_test)
{
    std::string const s1 = "opt1";
    std::string const s2 = "opt2";
    opt o1(s1);
    opt o2(s2);
    swap(o1, o2);
    TEST_REQUIRE(o1.good() && o2.good());
    TEST_CHECK(o1.value() == s2);
    TEST_CHECK(o2.value() == s1);
}

TEST_SUITE_END()