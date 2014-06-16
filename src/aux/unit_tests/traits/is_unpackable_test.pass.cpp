// REQUIRES: ELIB_AUX_SOURCE
#include <elib/aux/traits/is_unpackable.hpp>
#include <tuple>
#include <utility> /* for std::pair */
#include "rapid-cxx-test.hpp"
using namespace elib::aux;

struct dummy_type {};

TEST_SUITE(is_unpackable_test_suite)

TEST_CASE(void_test)
{
    TEST_STATIC_ASSERT(not is_unpackable<void>::value);
}

TEST_CASE(void_pointer_test)
{
    TEST_STATIC_ASSERT(not is_unpackable<void*>::value);
}

TEST_CASE(tuple_test)
{
    TEST_STATIC_ASSERT(is_unpackable<std::tuple<int, long, std::pair<int, int>>>::value);
}

TEST_CASE(pair_test)
{
    TEST_STATIC_ASSERT(is_unpackable<std::pair<int, long>>::value);
}

TEST_CASE(dummy_test)
{
    TEST_STATIC_ASSERT(not is_unpackable<dummy_type>::value);
}

TEST_SUITE_END()