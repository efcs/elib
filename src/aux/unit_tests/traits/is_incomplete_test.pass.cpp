// REQUIRES: ELIB_AUX_SOURCE, ELIB_BOOST_TEST
#define BOOST_TEST_MODULE Main
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include <elib/aux/traits/is_incomplete.hpp>
#include <elib/aux/static_assert.hpp>
using namespace elib::aux;

struct incomplete_type;
struct complete_type {};

BOOST_AUTO_TEST_SUITE(elib_aux_traits_is_incomplete_test_suite)

BOOST_AUTO_TEST_CASE(incomplete_type_test)
{
    ELIB_STATIC_ASSERT(is_incomplete<incomplete_type>::value);
    ELIB_STATIC_ASSERT(not is_incomplete<complete_type>::value);
    ELIB_STATIC_ASSERT(is_incomplete<void>::value);
    BOOST_CHECK(true);
}

BOOST_AUTO_TEST_SUITE_END()