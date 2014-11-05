// REQUIRES: ELIB_AUX
#include <elib/aux/no_decay.hpp>
#include <elib/aux/traits/is_same.hpp>
#include "rapid-cxx-test.hpp"

using namespace elib;

TEST_SUITE(elib_aux_no_decay_test_suite)

TEST_CASE(type_test)
{
    static_assert(
        aux::is_same<typename aux::no_decay<int[]>::type, int[]>::value
      , "int[] and int[] must be the same"
      );
    
    TEST_CHECK(true);
}

TEST_SUITE_END()