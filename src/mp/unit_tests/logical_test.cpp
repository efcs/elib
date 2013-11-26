#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include "mp_test_config.hpp"

#include <elib/mp/metafunctions/logical.hpp>


BOOST_AUTO_TEST_SUITE(mp_logical_test_suite)

  //-------------------------------- not --------------------------------// 
  BOOST_AUTO_TEST_CASE(not_test)
  {
    using e::not_;
    SAME_INTC(not_<true_>, BOOL(false));
    SAME_INTC(not_<false_>, BOOL(true));
    
    SAME_INTC(not_<INT(0)>, BOOL(true));
    SAME_INTC(not_<INT(1)>, BOOL(false));
    SAME_INTC(not_<INT(-1)>, BOOL(false));
  }                                                         // not_test
  
  //-------------------------------- and --------------------------------// 
  BOOST_AUTO_TEST_CASE(and_test)
  {
    using e::and_;
    using E1 = and_<false_, false_>;
    SAME_INTC(E1, BOOL(false));
    using E2 = and_<true_, false_>;
    SAME_INTC(E2, BOOL(false));
    using E3 = and_<false_, true_>;
    SAME_INTC(E3, BOOL(false));
    using E4 = and_<true_, true_>;
    SAME_INTC(E4, BOOL(true));
    
    using E5 = and_<INT(-5), INT(10)>;
    SAME_INTC(E5, BOOL(true));
    using E6 = and_<INT(0), true_>;
    SAME_INTC(E6, BOOL(false));
  }                                                         // and_test
  
  //-------------------------------- or --------------------------------// 
  BOOST_AUTO_TEST_CASE(or_test)
  {
    using e::or_;
    using E1 = or_<false_, false_>;
    SAME_INTC(E1, BOOL(false));
    using E2 = or_<true_, false_>;
    SAME_INTC(E2, BOOL(true));
    using E3 = or_<false_, true_>;
    SAME_INTC(E3, BOOL(true));
    using E4 = or_<true_, true_>;
    SAME_INTC(E4, BOOL(true));
    
    using E5 = or_<false_, INT(10)>;
    SAME_INTC(E5, BOOL(true));
    using E6 = or_<INT(0), true_>;
    SAME_INTC(E6, BOOL(true));
    using E7 = or_<CHAR(-1), false_>;
    SAME_INTC(E7, BOOL(true));
  }                                                         // or_test

BOOST_AUTO_TEST_SUITE_END()