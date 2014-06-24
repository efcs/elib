// REQUIRES: ELIB_CORE
#include <elib/optional.hpp>
#include <elib/aux/traits/is_same.hpp>
#include "rapid-cxx-test.hpp"

using opt = elib::optional<int>;

TEST_SUITE(elib_optional_make_optional_int_test_suite)

TEST_CASE(const_lvalue_test)
{
    int const x = 1;
    auto o = elib::make_optional(x);
    
    static_assert(elib::aux::is_same<decltype(o), opt>::value, "must be same");
    
    TEST_REQUIRE(o.good());
    TEST_CHECK(o.value() == 1);
}

TEST_CASE(rvalue_test)
{
    int x = 1;
    auto o = elib::make_optional(static_cast<int &&>(x));
    
    static_assert(elib::aux::is_same<decltype(o), opt>::value, "must be same");
    
    TEST_REQUIRE(o.good());
    TEST_CHECK(o.value() == 1);
}

TEST_SUITE_END()