// REQUIRES: ELIB_SOURCE
#include <elib/optional.hpp>
#include <elib/aux/traits/is_same.hpp>
#include <string>
#include "rapid-cxx-test.hpp"

using opt = elib::optional<std::string>;

TEST_SUITE(elib_optional_make_optional_string_test_suite)

TEST_CASE(const_lvalue_test)
{
    std::string const s = "hello";
    auto o = elib::make_optional(s);
    
    static_assert(elib::aux::is_same<decltype(o), opt>::value, "must be same");
    
    TEST_REQUIRE(o.good());
    TEST_CHECK(o.value() == s);
}

TEST_CASE(rvalue_test)
{
    std::string s = "hello";
    auto o = elib::make_optional(static_cast<std::string &&>(s));
    
    static_assert(elib::aux::is_same<decltype(o), opt>::value, "must be same");
    
    TEST_REQUIRE(o.good());
    TEST_CHECK(o.value() == "hello");
}

TEST_SUITE_END()