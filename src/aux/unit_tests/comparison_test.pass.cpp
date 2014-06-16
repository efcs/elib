// REQUIRES: ELIB_AUX_SOURCE
#include <elib/aux/integral_constant.hpp>
#include <elib/aux/comparison.hpp>
#include "rapid-cxx-test.hpp"

using namespace elib;

TEST_SUITE(elib_aux_comparison_test_suite)

TEST_CASE(equal_to_true_test)
{
    TEST_STATIC_ASSERT(
        aux::equal_to<aux::int_<1>, aux::long_<1>>::value
      );
    TEST_CHECK(true);
}

TEST_CASE(equal_to_false_test)
{
    TEST_STATIC_ASSERT(
        not aux::equal_to<aux::int_<0>, aux::long_<1>>::value
      );
    TEST_CHECK(true);
}

TEST_CASE(not_equal_to_true_test)
{
    TEST_STATIC_ASSERT(
        aux::not_equal_to<aux::int_<1>, aux::long_<0>>::value
      );
    TEST_CHECK(true);
}

TEST_CASE(not_equal_to_false_test)
{
    TEST_STATIC_ASSERT(
        not aux::not_equal_to<aux::int_<1>, aux::long_<1>>::value
      );
    TEST_CHECK(true);
}

TEST_CASE(less_true_test)
{
    TEST_STATIC_ASSERT(
        aux::less<aux::int_<0>, aux::long_<1>>::value
      );
    TEST_CHECK(true);
}

TEST_CASE(less_false_equal_test)
{
    TEST_STATIC_ASSERT(
        not aux::less<aux::int_<1>, aux::long_<1>>::value
      );
    TEST_CHECK(true);
}

TEST_CASE(less_false_greater_test)
{
    TEST_STATIC_ASSERT(
        not aux::less<aux::int_<2>, aux::long_<1>>::value
      );
    TEST_CHECK(true);
}

TEST_CASE(less_equal_true_test)
{
    TEST_STATIC_ASSERT(
        aux::less_equal<aux::int_<0>, aux::long_<1>>::value
      );
    TEST_CHECK(true);
}

TEST_CASE(less_equal_true_equal_test)
{
    TEST_STATIC_ASSERT(
        aux::less_equal<aux::int_<1>, aux::long_<1>>::value
      );
    TEST_CHECK(true);
}

TEST_CASE(less_equal_false_greater_test)
{
    TEST_STATIC_ASSERT(
        not aux::less_equal<aux::int_<2>, aux::long_<1>>::value
      );
    TEST_CHECK(true);
}

TEST_CASE(greater_true_test)
{
    TEST_STATIC_ASSERT(
        aux::greater<aux::int_<1>, aux::long_<0>>::value
      );
    TEST_CHECK(true);
}

TEST_CASE(greater_false_equal_test)
{
    TEST_STATIC_ASSERT(
        not aux::greater<aux::int_<1>, aux::long_<1>>::value
      );
    TEST_CHECK(true);
}

TEST_CASE(greater_false_greater_test)
{
    TEST_STATIC_ASSERT(
        not aux::greater<aux::int_<0>, aux::long_<1>>::value
      );
    TEST_CHECK(true);
}

TEST_CASE(greater_equal_true_test)
{
    TEST_STATIC_ASSERT(
        aux::greater_equal<aux::int_<1>, aux::long_<0>>::value
      );
    TEST_CHECK(true);
}

TEST_CASE(greater_equal_true_equal_test)
{
    TEST_STATIC_ASSERT(
        aux::greater_equal<aux::int_<1>, aux::long_<1>>::value
      );
    TEST_CHECK(true);
}

TEST_CASE(greater_equal_false_greater_test)
{
    TEST_STATIC_ASSERT(
        not aux::greater_equal<aux::int_<0>, aux::long_<1>>::value
      );
    TEST_CHECK(true);
}

TEST_SUITE_END()