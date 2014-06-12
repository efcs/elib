// REQUIRES: ELIB_SOURCE, ELIB_BOOST_TEST
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE Main
#include <boost/test/unit_test.hpp>

#include <elib/optional.hpp>
using opt = elib::optional<int>;

BOOST_AUTO_TEST_SUITE(elib_optional_int_swap_function_test_suite)

BOOST_AUTO_TEST_CASE(both_empty_swap_test)
{
    opt o1;
    opt o2;
    swap(o1, o2);
    BOOST_CHECK(not o1.good() && not o2.good());
}

BOOST_AUTO_TEST_CASE(lhs_empty_rhs_not_empty_swap_test)
{
    opt o1;
    opt o2(1);
    swap(o1, o2);
    BOOST_REQUIRE(o1.good() && not o2.good());
    BOOST_CHECK(o1.value() == 1);
}

BOOST_AUTO_TEST_CASE(rhs_empty_lhs_not_empty_swap_test)
{
    opt o1(1);
    opt o2;
    swap(o1, o2);
    BOOST_REQUIRE(not o1.good() && o2.good());
    BOOST_CHECK(o2.value() == 1);
}

BOOST_AUTO_TEST_CASE(both_non_empty_swap_test)
{
    opt o1(1);
    opt o2(2);
    swap(o1, o2);
    BOOST_REQUIRE(o1.good() && o2.good());
    BOOST_CHECK(o1.value() == 2);
    BOOST_CHECK(o2.value() == 1);
}

BOOST_AUTO_TEST_SUITE_END()