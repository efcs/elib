#define BOOST_TEST_MODULE Main
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include <elib/aux/anything.hpp>
#include <elib/aux/declval.hpp>
#include <elib/aux/enable_if.hpp>
#include <elib/aux/static_assert.hpp>

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


BOOST_AUTO_TEST_SUITE(elib_aux_anything_test_suite)

BOOST_AUTO_TEST_CASE(ctor_test)
{
    ELIB_STATIC_ASSERT(test_ctor<empty>());
    ELIB_STATIC_ASSERT(test_ctor<empty const>());
    ELIB_STATIC_ASSERT(test_ctor<empty &>());
    ELIB_STATIC_ASSERT(test_ctor<empty const &>());
    ELIB_STATIC_ASSERT(test_ctor<empty *>());
    ELIB_STATIC_ASSERT(test_ctor<empty const *>());
    ELIB_STATIC_ASSERT(test_ctor<empty[]>());
    ELIB_STATIC_ASSERT(test_ctor<const empty[]>());
    BOOST_CHECK(true);
}

BOOST_AUTO_TEST_CASE(convert_test)
{
    // TODO GCC fails on this
    ELIB_STATIC_ASSERT(test_convert<empty>());
    ELIB_STATIC_ASSERT(test_convert<empty &>());
    //ELIB_STATIC_ASSERT(test_convert<empty &&>());
    BOOST_CHECK(true);
}

BOOST_AUTO_TEST_SUITE_END()