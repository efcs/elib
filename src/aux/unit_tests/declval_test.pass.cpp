// REQUIRES: ELIB_AUX
#include <elib/aux/declval.hpp>
#include <elib/aux/traits/is_same.hpp>
#include "rapid-cxx-test.hpp"

using namespace elib;

TEST_SUITE(elib_aux_declval_test_suite)

TEST_CASE(rvalue_test)
{
    using T = decltype(elib::declval<int>());
    static_assert(
        aux::is_same<T, int &&>::value
      , "T == int &&"
      );
    TEST_CHECK(true);
}

TEST_CASE(lvalue_test)
{
    using T = decltype(elib::declval<int &>());
    static_assert(
        aux::is_same<T, int &>::value
      , "T == int &"
      );
    TEST_CHECK(true);
}

TEST_CASE(const_rvalue_test)
{
    using T = decltype(elib::declval<int const>());
    static_assert(
        aux::is_same<T, int const &&>::value
      , "T == int const &&"
      );
    TEST_CHECK(true);
}

TEST_CASE(const_lvalue_test)
{
    using T = decltype(elib::declval<int const &>());
    static_assert(
        aux::is_same<T, int const &>::value
      , "T == int const &"
      );
    TEST_CHECK(true);
}

TEST_SUITE_END()