// REQUIRES: ELIB_AUX_SOURCE
#include <elib/aux/traits/is_incomplete.hpp>
#include "rapid-cxx-test.hpp"
using namespace elib::aux;

struct incomplete_type;
struct complete_type {};

TEST_SUITE(elib_aux_traits_is_incomplete_test_suite)

TEST_CASE(incomplete_type_test)
{
    TEST_STATIC_ASSERT(is_incomplete<incomplete_type>::value);
    TEST_STATIC_ASSERT(not is_incomplete<complete_type>::value);
    TEST_STATIC_ASSERT(is_incomplete<void>::value);
}

TEST_SUITE_END()