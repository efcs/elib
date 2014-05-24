#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include <elib/aux/traits/is_unpackable.hpp>
#include <elib/aux/static_assert.hpp>
#include <tuple>
#include <utility> /* for std::pair */
using namespace elib::aux;

struct dummy_type {};

BOOST_AUTO_TEST_SUITE(is_unpackable_test_suite)

BOOST_AUTO_TEST_CASE(void_test)
{
    ELIB_STATIC_ASSERT(not is_unpackable<void>::value);
    BOOST_CHECK(true);
}

BOOST_AUTO_TEST_CASE(void_pointer_test)
{
    ELIB_STATIC_ASSERT(not is_unpackable<void*>::value);
    BOOST_CHECK(true);
}

BOOST_AUTO_TEST_CASE(tuple_test)
{
    ELIB_STATIC_ASSERT(is_unpackable<std::tuple<int, long, std::pair<int, int>>>::value);
    BOOST_CHECK(true);
}

BOOST_AUTO_TEST_CASE(pair_test)
{
    ELIB_STATIC_ASSERT(is_unpackable<std::pair<int, long>>::value);
    BOOST_CHECK(true);
}

BOOST_AUTO_TEST_CASE(dummy_test)
{
    ELIB_STATIC_ASSERT(not is_unpackable<dummy_type>::value);
    BOOST_CHECK(true);
}

BOOST_AUTO_TEST_SUITE_END()