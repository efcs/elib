// REQUIRES: ELIB_SOURCE, ELIB_BOOST_TEST
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE Main
#include <boost/test/unit_test.hpp>

#include <elib/optional.hpp>
#include <elib/aux/traits/is_same.hpp>
#include <string>
using opt = elib::optional<std::string>;

BOOST_AUTO_TEST_SUITE(elib_optional_make_optional_string_test_suite)

BOOST_AUTO_TEST_CASE(const_lvalue_test)
{
    std::string const s = "hello";
    auto o = elib::make_optional(s);
    
    static_assert(elib::aux::is_same<decltype(o), opt>::value, "must be same");
    
    BOOST_REQUIRE(o.good());
    BOOST_CHECK(o.value() == s);
}

BOOST_AUTO_TEST_CASE(rvalue_test)
{
    std::string s = "hello";
    auto o = elib::make_optional(static_cast<std::string &&>(s));
    
    static_assert(elib::aux::is_same<decltype(o), opt>::value, "must be same");
    
    BOOST_REQUIRE(o.good());
    BOOST_CHECK(o.value() == "hello");
}

BOOST_AUTO_TEST_SUITE_END()