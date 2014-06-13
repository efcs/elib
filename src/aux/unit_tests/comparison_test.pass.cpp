// REQUIRES: ELIB_AUX_SOURCE, ELIB_BOOST_TEST
#define BOOST_TEST_MODULE Main
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include <elib/aux/integral_constant.hpp>
#include <elib/aux/comparison.hpp>
#include <elib/aux/static_assert.hpp>

using namespace elib;

BOOST_AUTO_TEST_SUITE(elib_aux_comparison_test_suite)

BOOST_AUTO_TEST_CASE(equal_to_true_test)
{
    ELIB_STATIC_ASSERT(
        aux::equal_to<aux::int_<1>, aux::long_<1>>::value
      );
    BOOST_CHECK(true);
}

BOOST_AUTO_TEST_CASE(equal_to_false_test)
{
    ELIB_STATIC_ASSERT(
        not aux::equal_to<aux::int_<0>, aux::long_<1>>::value
      );
    BOOST_CHECK(true);
}

BOOST_AUTO_TEST_CASE(not_equal_to_true_test)
{
    ELIB_STATIC_ASSERT(
        aux::not_equal_to<aux::int_<1>, aux::long_<0>>::value
      );
    BOOST_CHECK(true);
}

BOOST_AUTO_TEST_CASE(not_equal_to_false_test)
{
    ELIB_STATIC_ASSERT(
        not aux::not_equal_to<aux::int_<1>, aux::long_<1>>::value
      );
    BOOST_CHECK(true);
}

BOOST_AUTO_TEST_CASE(less_true_test)
{
    ELIB_STATIC_ASSERT(
        aux::less<aux::int_<0>, aux::long_<1>>::value
      );
    BOOST_CHECK(true);
}

BOOST_AUTO_TEST_CASE(less_false_equal_test)
{
    ELIB_STATIC_ASSERT(
        not aux::less<aux::int_<1>, aux::long_<1>>::value
      );
    BOOST_CHECK(true);
}

BOOST_AUTO_TEST_CASE(less_false_greater_test)
{
    ELIB_STATIC_ASSERT(
        not aux::less<aux::int_<2>, aux::long_<1>>::value
      );
    BOOST_CHECK(true);
}

BOOST_AUTO_TEST_CASE(less_equal_true_test)
{
    ELIB_STATIC_ASSERT(
        aux::less_equal<aux::int_<0>, aux::long_<1>>::value
      );
    BOOST_CHECK(true);
}

BOOST_AUTO_TEST_CASE(less_equal_true_equal_test)
{
    ELIB_STATIC_ASSERT(
        aux::less_equal<aux::int_<1>, aux::long_<1>>::value
      );
    BOOST_CHECK(true);
}

BOOST_AUTO_TEST_CASE(less_equal_false_greater_test)
{
    ELIB_STATIC_ASSERT(
        not aux::less_equal<aux::int_<2>, aux::long_<1>>::value
      );
    BOOST_CHECK(true);
}

BOOST_AUTO_TEST_CASE(greater_true_test)
{
    ELIB_STATIC_ASSERT(
        aux::greater<aux::int_<1>, aux::long_<0>>::value
      );
    BOOST_CHECK(true);
}

BOOST_AUTO_TEST_CASE(greater_false_equal_test)
{
    ELIB_STATIC_ASSERT(
        not aux::greater<aux::int_<1>, aux::long_<1>>::value
      );
    BOOST_CHECK(true);
}

BOOST_AUTO_TEST_CASE(greater_false_greater_test)
{
    ELIB_STATIC_ASSERT(
        not aux::greater<aux::int_<0>, aux::long_<1>>::value
      );
    BOOST_CHECK(true);
}

BOOST_AUTO_TEST_CASE(greater_equal_true_test)
{
    ELIB_STATIC_ASSERT(
        aux::greater_equal<aux::int_<1>, aux::long_<0>>::value
      );
    BOOST_CHECK(true);
}

BOOST_AUTO_TEST_CASE(greater_equal_true_equal_test)
{
    ELIB_STATIC_ASSERT(
        aux::greater_equal<aux::int_<1>, aux::long_<1>>::value
      );
    BOOST_CHECK(true);
}

BOOST_AUTO_TEST_CASE(greater_equal_false_greater_test)
{
    ELIB_STATIC_ASSERT(
        not aux::greater_equal<aux::int_<0>, aux::long_<1>>::value
      );
    BOOST_CHECK(true);
}

BOOST_AUTO_TEST_SUITE_END()