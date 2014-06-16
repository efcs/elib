// REQUIRES: ELIB_AUX_SOURCE
#include <elib/aux/type_list.hpp>
#include <elib/aux/traits/is_same.hpp>
#include "rapid-cxx-test.hpp"

using namespace elib;


TEST_SUITE(elib_aux_type_list_test_suite)

TEST_CASE(empty_list_test)
{
    using L = aux::type_list<>;
    TEST_STATIC_ASSERT(
        aux::is_same<L::type, L>::value
      );
    TEST_STATIC_ASSERT(
        L::size::value == 0
      );
    TEST_CHECK(true);
}

TEST_CASE(single_item_list_test)
{
    using L = aux::type_list<void>;
    TEST_STATIC_ASSERT(
        aux::is_same<L::type, L>::value
      );
    TEST_STATIC_ASSERT(
        L::size::value == 1
      );
    TEST_CHECK(true);
}

TEST_CASE(two_item_list_test)
{
    using L = aux::type_list<void, int>;
    TEST_STATIC_ASSERT(
        aux::is_same<L::type, L>::value
      );
    TEST_STATIC_ASSERT(
        L::size::value == 2
      );
    TEST_CHECK(true);
}

TEST_SUITE_END()