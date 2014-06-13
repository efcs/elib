// REQUIRES: ELIB_AUX_SOURCE, ELIB_BOOST_TEST
#define BOOST_TEST_MODULE Main
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include "elib/aux/integer_sequence.hpp"
#include "elib/aux/traits/is_same.hpp"


BOOST_AUTO_TEST_SUITE(utility_integer_sequence_test_suite)

BOOST_AUTO_TEST_CASE(utility_integer_sequence_test)
{
  using namespace elib::aux;
  
  BOOST_CHECK((
    is_same<
        make_integer_sequence<int, 0>
      , integer_sequence<int> 
    >::value
  ));

  BOOST_CHECK((
    is_same<
        make_index_sequence<5>
      , index_sequence<0, 1, 2, 3, 4>
    >::value
  ));

  BOOST_CHECK((
      is_same<
          index_sequence_for<void, void, void, void, void
                           , void, void, void, void, void>
        , make_index_sequence<10> 
      >::value
  ));
}

BOOST_AUTO_TEST_SUITE_END()