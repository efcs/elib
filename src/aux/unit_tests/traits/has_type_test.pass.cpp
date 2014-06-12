#define BOOST_TEST_MODULE Main
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include <elib/aux/traits/has_type.hpp>
#include <elib/aux/static_assert.hpp>
using namespace elib::aux;

struct empty {};
struct with_type { using type = int; };
struct with_void_type { using type = void; };

struct with_value_type { static constexpr int type = 0; };
constexpr int with_value_type::type;

struct with_empty_value_type { static empty type; };
empty with_empty_value_type::type;

BOOST_AUTO_TEST_SUITE(elib_aux_traits_has_type_test_suite)

BOOST_AUTO_TEST_CASE(has_type_test)
{
    ELIB_STATIC_ASSERT(not has_type<void>::value);
    ELIB_STATIC_ASSERT(not has_type<empty>::value);
    ELIB_STATIC_ASSERT(not has_type<with_value_type>::value);
    ELIB_STATIC_ASSERT(not has_type<with_empty_value_type>::value);
    ELIB_STATIC_ASSERT(has_type<with_type>::value);
    ELIB_STATIC_ASSERT(has_type<with_void_type>::value);
    BOOST_CHECK(true);
}

BOOST_AUTO_TEST_SUITE_END()
