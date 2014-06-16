// REQUIRES: ELIB_AUX_SOURCE
#include <elib/aux/traits/has_value.hpp>
#include "rapid-cxx-test.hpp"
using namespace elib::aux;

struct empty {};
struct type_value { using value = int; };
struct void_value { using value = void; };

struct with_value { static constexpr int value = 0; };
constexpr int with_value::value;

struct with_empty_value { static empty value; };
empty with_empty_value::value;

TEST_SUITE(elib_aux_traits_has_value_test_suite)

TEST_CASE(has_value_test)
{
    TEST_STATIC_ASSERT(not has_value<void>::value);
    TEST_STATIC_ASSERT(not has_value<empty>::value);
    TEST_STATIC_ASSERT(not has_value<type_value>::value);
    TEST_STATIC_ASSERT(not has_value<void_value>::value);
    TEST_STATIC_ASSERT(has_value<with_value>::value);
    TEST_STATIC_ASSERT(has_value<with_empty_value>::value);
}

TEST_SUITE_END()