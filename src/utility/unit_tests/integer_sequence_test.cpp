#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include "elib/utility/integer_sequence.hpp"
#include <type_traits>


BOOST_AUTO_TEST_SUITE(utility_integer_seq_test_suite)

BOOST_AUTO_TEST_CASE(utility_integer_seq_test)
{
  using namespace elib;
  using std::is_same;
  
  BOOST_CHECK((
    is_same<
        make_integer_seq<int, 0>
      , integer_seq<int> 
    >::value
  ));

  BOOST_CHECK((
    is_same<
        make_int_seq<1>
      , integer_seq<int, 0>
    >::value
  ));

  BOOST_CHECK((
    is_same<
        make_index_seq<5>
      , index_seq<0, 1, 2, 3, 4>
    >::value
  ));
}

BOOST_AUTO_TEST_SUITE_END()