#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include "elib/aux.hpp"


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
        make_int_sequence<1>
      , integer_sequence<int, 0>
    >::value
  ));

  BOOST_CHECK((
    is_same<
        make_index_sequence<5>
      , index_sequence<0, 1, 2, 3, 4>
    >::value
  ));
}

BOOST_AUTO_TEST_SUITE_END()