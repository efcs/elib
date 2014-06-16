// REQUIRES: ELIB_AUX_SOURCE
#include <elib/aux/type_pair.hpp>
#include <elib/aux/traits/is_same.hpp>
#include "rapid-cxx-test.hpp"

using namespace elib;

TEST_SUITE(elib_aux_type_pair_test_suite)

TEST_CASE(type_test)
{
    using pair = aux::type_pair<int, void>;
    static_assert(
        aux::is_same<pair::type, pair>::value
      , "pair::type == pair"
      );
}

TEST_CASE(first_test)
{
    using pair = aux::type_pair<int, void>;
    static_assert(
        aux::is_same<pair::first, int>::value
      , "pair::first == int"
      );
    static_assert(
        aux::is_same<aux::first_t<pair>, int>::value
      , "first_t<pair> == int"
      );
}

TEST_CASE(second_test)
{
    using pair = aux::type_pair<int, void>;
    static_assert(
        aux::is_same<pair::second, void>::value
      , "pair::second == int"
      );
    static_assert(
        aux::is_same<aux::second_t<pair>, void>::value
      , "second_t<pair> == int"
      );
}

TEST_SUITE_END()