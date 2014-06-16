// REQUIRES: ELIB_AUX_SOURCE
#include <elib/aux/none.hpp>
#include "rapid-cxx-test.hpp"

using namespace elib;

TEST_SUITE(elib_aux_none_test_suite)

TEST_CASE(is_none_test)
{
    static_assert(
        aux::is_none<aux::none>::value
      , "must be none"
      );
    
    static_assert(
        not aux::is_none<int>::value
      , "must not be none"
      );
    TEST_CHECK(true);
}

TEST_SUITE_END()