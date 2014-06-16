// REQUIRES: ELIB_AUX_SOURCE
#include <elib/aux/integer_sequence.hpp>
#include <elib/aux/traits/is_same.hpp>
#include "rapid-cxx-test.hpp"

TEST_SUITE(utility_integer_sequence_test_suite)

TEST_CASE(utility_integer_sequence_test)
{
  using namespace elib::aux;
  
  TEST_CHECK((
    is_same<
        make_integer_sequence<int, 0>
      , integer_sequence<int> 
    >::value
  ));

  TEST_CHECK((
    is_same<
        make_index_sequence<5>
      , index_sequence<0, 1, 2, 3, 4>
    >::value
  ));

  TEST_CHECK((
      is_same<
          index_sequence_for<void, void, void, void, void
                           , void, void, void, void, void>
        , make_index_sequence<10> 
      >::value
  ));
}

TEST_SUITE_END()