// REQUIRES: ELIB_CORE
#include <elib/optional.hpp>
#include "rapid-cxx-test.hpp"

using opt = elib::optional<int>;

TEST_SUITE(elib_optional_int_swap_function_test_suite)

TEST_CASE(both_empty_swap_test)
{
    opt o1;
    opt o2;
    swap(o1, o2);
    TEST_CHECK(not o1.good() && not o2.good());
}

TEST_CASE(lhs_empty_rhs_not_empty_swap_test)
{
    opt o1;
    opt o2(1);
    swap(o1, o2);
    TEST_REQUIRE(o1.good() && not o2.good());
    TEST_CHECK(o1.value() == 1);
}

TEST_CASE(rhs_empty_lhs_not_empty_swap_test)
{
    opt o1(1);
    opt o2;
    swap(o1, o2);
    TEST_REQUIRE(not o1.good() && o2.good());
    TEST_CHECK(o2.value() == 1);
}

TEST_CASE(both_non_empty_swap_test)
{
    opt o1(1);
    opt o2(2);
    swap(o1, o2);
    TEST_REQUIRE(o1.good() && o2.good());
    TEST_CHECK(o1.value() == 2);
    TEST_CHECK(o2.value() == 1);
}

TEST_SUITE_END()