#define BOOST_TEST_MODULE Main
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>


#include <elib/aux/declval.hpp>
#include <elib/aux/traits/is_same.hpp>

using namespace elib;

BOOST_AUTO_TEST_SUITE(elib_aux_declval_test_suite)

BOOST_AUTO_TEST_CASE(rvalue_test)
{
    using T = decltype(elib::declval<int>());
    static_assert(
        aux::is_same<T, int &&>::value
      , "T == int &&"
      );
    BOOST_CHECK(true);
}

BOOST_AUTO_TEST_CASE(lvalue_test)
{
    using T = decltype(elib::declval<int &>());
    static_assert(
        aux::is_same<T, int &>::value
      , "T == int &"
      );
    BOOST_CHECK(true);
}

BOOST_AUTO_TEST_CASE(const_rvalue_test)
{
    using T = decltype(elib::declval<int const>());
    static_assert(
        aux::is_same<T, int const &&>::value
      , "T == int const &&"
      );
    BOOST_CHECK(true);
}

BOOST_AUTO_TEST_CASE(const_lvalue_test)
{
    using T = decltype(elib::declval<int const &>());
    static_assert(
        aux::is_same<T, int const &>::value
      , "T == int const &"
      );
    BOOST_CHECK(true);
}

BOOST_AUTO_TEST_SUITE_END()