// REQUIRES: ELIB_AUX_SOURCE
#include <elib/aux/integral_constant.hpp>
#include <elib/aux/traits/is_same.hpp>
#include <type_traits>
#include "rapid-cxx-test.hpp"

using namespace elib;

TEST_SUITE(elib_aux_integral_constant_test_suite)


TEST_CASE(int_zero_test)
{
    using T = aux::integral_constant<int, 0>;
    TEST_STATIC_ASSERT(aux::is_same<T, T::type>::value);
    TEST_STATIC_ASSERT(aux::is_same<int, T::value_type>::value);
    TEST_STATIC_ASSERT(T::value == 0);
    
    T v;
    int x = v;
    TEST_CHECK(x == 0);
    TEST_CHECK(v() == 0);
}

TEST_CASE(int_one_test)
{
    using T = aux::integral_constant<int, 1>;
    TEST_STATIC_ASSERT(aux::is_same<T, T::type>::value);
    TEST_STATIC_ASSERT(aux::is_same<int, T::value_type>::value);
    TEST_STATIC_ASSERT(T::value == 1);
    
    T v;
    int x = v;
    TEST_CHECK(x == 1);
    TEST_CHECK(v() == 1);
}

TEST_CASE(int_two_test)
{
    using T = aux::integral_constant<int, 2>;
    TEST_STATIC_ASSERT(aux::is_same<T, T::type>::value);
    TEST_STATIC_ASSERT(aux::is_same<int, T::value_type>::value);
    TEST_STATIC_ASSERT(T::value == 2);
    
    T v;
    int x = v;
    TEST_CHECK(x == 2);
    TEST_CHECK(v() == 2);
}

TEST_CASE(true_type_test)
{
    TEST_STATIC_ASSERT(
        aux::is_same<aux::true_, aux::bool_<true>>::value
      );
    TEST_STATIC_ASSERT(
        aux::is_same<aux::true_, aux::integral_constant<bool, true>>::value
      );
    using T = ELIB_AUTO_INTC(true);
    TEST_STATIC_ASSERT(
        aux::is_same<aux::true_, T>::value
      );
    TEST_CHECK(true);
}

TEST_CASE(false_type_test)
{
    TEST_STATIC_ASSERT(
        aux::is_same<aux::false_, aux::bool_<false>>::value
      );
    TEST_STATIC_ASSERT(
        aux::is_same<aux::false_, aux::integral_constant<bool, false>>::value
      );
    using T = ELIB_AUTO_INTC(false);
    TEST_STATIC_ASSERT(
        aux::is_same<aux::false_, T>::value
      );
    TEST_CHECK(true);
}

// Issue #29
TEST_CASE(convert_ctor_test)
{
    constexpr true_ t(std::true_type);
    TEST_CHECK(true);
}

// Issue #29
TEST_CASE(convert_operator_test)
{
    constexpr std::true_type t = true_{};
    ((void)t);
    TEST_CHECK(true);
}

TEST_SUITE_END()