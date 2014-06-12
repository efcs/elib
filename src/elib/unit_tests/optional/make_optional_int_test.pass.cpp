// REQUIRES: ELIB_SOURCE, ELIB_BOOST_TEST
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE Main
#include <boost/test/unit_test.hpp>

#include <elib/optional.hpp>
#include <elib/aux/traits/is_same.hpp>
using opt = elib::optional<int>;

BOOST_AUTO_TEST_SUITE(elib_optional_make_optional_int_test_suite)

BOOST_AUTO_TEST_CASE(const_lvalue_test)
{
    int const x = 1;
    auto o = elib::make_optional(x);
    
    static_assert(elib::aux::is_same<decltype(o), opt>::value, "must be same");
    
    BOOST_REQUIRE(o.good());
    BOOST_CHECK(o.value() == 1);
}

BOOST_AUTO_TEST_CASE(rvalue_test)
{
    int x = 1;
    auto o = elib::make_optional(static_cast<int &&>(x));
    
    static_assert(elib::aux::is_same<decltype(o), opt>::value, "must be same");
    
    BOOST_REQUIRE(o.good());
    BOOST_CHECK(o.value() == 1);
}

BOOST_AUTO_TEST_SUITE_END()