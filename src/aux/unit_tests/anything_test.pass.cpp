// REQUIRES: ELIB_AUX_SOURCE
#include <elib/aux/anything.hpp>
#include <elib/aux/declval.hpp>
#include <elib/aux/enable_if.hpp>
#include "rapid-cxx-test.hpp"


using namespace elib::aux;

struct empty {};

template <
    class T
  , ELIB_ENABLE_IF_VALID_EXPR(anything(declval<T>()))
  >
constexpr bool test_ctor_impl(int) noexcept { return true; }

template <class>
constexpr bool test_ctor_impl(long) noexcept { return false; }

template <class T>
constexpr bool test_ctor() noexcept { return test_ctor_impl<T>(0); }

template <
    class T
  , ELIB_ENABLE_IF_VALID_EXPR(declval<T>() = declval<anything>())
  >
constexpr bool test_convert_impl(int) noexcept { return true; }

template <class>
constexpr bool test_convert_impl(long) noexcept { return false; }

template <class T>
constexpr bool test_convert() noexcept { return test_convert_impl<T>(0); }


TEST_SUITE(elib_aux_anything_test_suite)

TEST_CASE(ctor_test)
{
    TEST_STATIC_ASSERT(test_ctor<empty>());
    TEST_STATIC_ASSERT(test_ctor<empty const>());
    TEST_STATIC_ASSERT(test_ctor<empty &>());
    TEST_STATIC_ASSERT(test_ctor<empty const &>());
    TEST_STATIC_ASSERT(test_ctor<empty *>());
    TEST_STATIC_ASSERT(test_ctor<empty const *>());
    TEST_STATIC_ASSERT(test_ctor<empty[]>());
    TEST_STATIC_ASSERT(test_ctor<const empty[]>());
    TEST_CHECK(true);
}

TEST_CASE(convert_test)
{
    // TODO GCC fails on this
    TEST_STATIC_ASSERT(test_convert<empty>());
    TEST_STATIC_ASSERT(test_convert<empty &>());
    //TEST_STATIC_ASSERT(test_convert<empty &&>());
}

TEST_SUITE_END()