// REQUIRES: ELIB_AUX_SOURCE
#include <elib/aux/always.hpp>
#include <elib/aux/traits/is_same.hpp>
#include "rapid-cxx-test.hpp"

using namespace elib;

TEST_SUITE(elib_aux_always_test_suite)

TEST_CASE(always_true_test)
{
    static_assert(
        aux::always<>::value
      , "must be true"
      );
    
    TEST_CHECK(true);
}

TEST_CASE(never_true_test)
{
    static_assert(
        not aux::never<>::value
      , "must never be true"
      );
    
    TEST_CHECK(true);
}

TEST_CASE(always_void_test)
{
    static_assert(
        aux::is_same<aux::always_void<>, void>::value
      , "must be void"
      );
    TEST_CHECK(true);
}


TEST_SUITE_END()