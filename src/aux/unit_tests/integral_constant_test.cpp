#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include <elib/aux/integral_constant.hpp>
#include <elib/aux/static_assert.hpp>
#include <elib/aux/traits/is_same.hpp>

using namespace elib;

BOOST_AUTO_TEST_SUITE(elib_aux_integral_constant_test_suite)


BOOST_AUTO_TEST_CASE(int_zero_test)
{
    using T = aux::integral_constant<int, 0>;
    ELIB_STATIC_ASSERT(aux::is_same<T, T::type>::value);
    ELIB_STATIC_ASSERT(aux::is_same<int, T::value_type>::value);
    ELIB_STATIC_ASSERT(T::value == 0);
    
    T v;
    int x = v;
    BOOST_CHECK(x == 0);
    BOOST_CHECK(v() == 0);
}

BOOST_AUTO_TEST_CASE(int_one_test)
{
    using T = aux::integral_constant<int, 1>;
    ELIB_STATIC_ASSERT(aux::is_same<T, T::type>::value);
    ELIB_STATIC_ASSERT(aux::is_same<int, T::value_type>::value);
    ELIB_STATIC_ASSERT(T::value == 1);
    
    T v;
    int x = v;
    BOOST_CHECK(x == 1);
    BOOST_CHECK(v() == 1);
}

BOOST_AUTO_TEST_CASE(int_two_test)
{
    using T = aux::integral_constant<int, 2>;
    ELIB_STATIC_ASSERT(aux::is_same<T, T::type>::value);
    ELIB_STATIC_ASSERT(aux::is_same<int, T::value_type>::value);
    ELIB_STATIC_ASSERT(T::value == 2);
    
    T v;
    int x = v;
    BOOST_CHECK(x == 2);
    BOOST_CHECK(v() == 2);
}

BOOST_AUTO_TEST_CASE(true_type_test)
{
    ELIB_STATIC_ASSERT(
        aux::is_same<aux::true_, aux::bool_<true>>::value
      );
    ELIB_STATIC_ASSERT(
        aux::is_same<aux::true_, aux::integral_constant<bool, true>>::value
      );
    using T = ELIB_AUTO_INTC(true);
    ELIB_STATIC_ASSERT(
        aux::is_same<aux::true_, T>::value
      );
    BOOST_CHECK(true);
}

BOOST_AUTO_TEST_CASE(false_type_test)
{
    ELIB_STATIC_ASSERT(
        aux::is_same<aux::false_, aux::bool_<false>>::value
      );
    ELIB_STATIC_ASSERT(
        aux::is_same<aux::false_, aux::integral_constant<bool, false>>::value
      );
    using T = ELIB_AUTO_INTC(false);
    ELIB_STATIC_ASSERT(
        aux::is_same<aux::false_, T>::value
      );
    BOOST_CHECK(true);
}

BOOST_AUTO_TEST_SUITE_END()