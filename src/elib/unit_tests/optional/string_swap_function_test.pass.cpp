// REQUIRES: ELIB_SOURCE, ELIB_BOOST_TEST
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE Main
#include <boost/test/unit_test.hpp>

#include <elib/optional.hpp>
#include <string>
using opt = elib::optional<std::string>;

BOOST_AUTO_TEST_SUITE(elib_optional_string_swap_function_test_suite)

BOOST_AUTO_TEST_CASE(both_empty_swap_test)
{
    opt o1;
    opt o2;
    swap(o1, o2);
    BOOST_CHECK(not o1.good() && not o2.good());
}

BOOST_AUTO_TEST_CASE(lhs_empty_rhs_not_empty_swap_test)
{
    std::string const s = "hello";
    opt o1;
    opt o2(s);
    swap(o1, o2);
    BOOST_REQUIRE(o1.good() && not o2.good());
    BOOST_CHECK(o1.value() == s);
}

BOOST_AUTO_TEST_CASE(rhs_empty_lhs_not_empty_swap_test)
{
    std::string const s = "hello";
    opt o1(s);
    opt o2;
    swap(o1, o2);
    BOOST_REQUIRE(not o1.good() && o2.good());
    BOOST_CHECK(o2.value() == s);
}

BOOST_AUTO_TEST_CASE(both_non_empty_swap_test)
{
    std::string const s1 = "opt1";
    std::string const s2 = "opt2";
    opt o1(s1);
    opt o2(s2);
    swap(o1, o2);
    BOOST_REQUIRE(o1.good() && o2.good());
    BOOST_CHECK(o1.value() == s2);
    BOOST_CHECK(o2.value() == s1);
}

BOOST_AUTO_TEST_SUITE_END()