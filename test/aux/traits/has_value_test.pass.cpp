#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include <elib/aux/traits/has_value.hpp>
#include <elib/aux/static_assert.hpp>
using namespace elib::aux;

struct empty {};
struct type_value { using value = int; };
struct void_value { using value = void; };

struct with_value { static constexpr int value = 0; };
constexpr int with_value::value;

struct with_empty_value { static empty value; };
empty with_empty_value::value;

BOOST_AUTO_TEST_SUITE(elib_aux_traits_has_value_test_suite)

BOOST_AUTO_TEST_CASE(has_value_test)
{
    ELIB_STATIC_ASSERT(not has_value<void>::value);
    ELIB_STATIC_ASSERT(not has_value<empty>::value);
    ELIB_STATIC_ASSERT(not has_value<type_value>::value);
    ELIB_STATIC_ASSERT(not has_value<void_value>::value);
    ELIB_STATIC_ASSERT(has_value<with_value>::value);
    ELIB_STATIC_ASSERT(has_value<with_empty_value>::value);
    BOOST_CHECK(true);
}

BOOST_AUTO_TEST_SUITE_END()