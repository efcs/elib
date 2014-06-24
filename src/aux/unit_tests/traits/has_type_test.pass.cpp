// REQUIRES: ELIB_AUX
#include <elib/aux/traits/has_type.hpp>
#include "rapid-cxx-test.hpp"
using namespace elib::aux;

struct empty {};
struct with_type { using type = int; };
struct with_void_type { using type = void; };

struct with_value_type { static constexpr int type = 0; };
constexpr int with_value_type::type;

struct with_empty_value_type { static empty type; };
empty with_empty_value_type::type;

TEST_SUITE(elib_aux_traits_has_type_test_suite)

TEST_CASE(has_type_test)
{
    TEST_STATIC_ASSERT(not has_type<void>::value);
    TEST_STATIC_ASSERT(not has_type<empty>::value);
    TEST_STATIC_ASSERT(not has_type<with_value_type>::value);
    TEST_STATIC_ASSERT(not has_type<with_empty_value_type>::value);
    TEST_STATIC_ASSERT(has_type<with_type>::value);
    TEST_STATIC_ASSERT(has_type<with_void_type>::value);
}

TEST_SUITE_END()
