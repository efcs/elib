#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include "mp_test_config.hpp"

#include <elib/mp/iterator.hpp>

#if ELIB_MP_BOOST_MPL_TESTS
# include <boost/mpl/advance.hpp>
# include <boost/mpl/distance.hpp>
# include <boost/mpl/next_prior.hpp>
# include <boost/mpl/deref.hpp>
# include <boost/mpl/iterator_category.hpp>
# endif                                              // ELIB_MP_BOOST_MPL_TESTS

BOOST_AUTO_TEST_SUITE(mp_iterator_test_suite)

//-------------------------------- advance ----------------------------------//
  //TODO
  BOOST_AUTO_TEST_CASE(advance_test)
  {
    BOOST_CHECK(true);
  }                                                         // advance_test
  
//-------------------------------- distance ---------------------------------//
  //TODO
  BOOST_AUTO_TEST_CASE(distance_test)
  {
    BOOST_CHECK(true);
  }                                                         // distance_test
  
//-------------------------------- next_prior -------------------------------//
  //TODO
  BOOST_AUTO_TEST_CASE(next_prior_test)
  {
    BOOST_CHECK(true);
  }                                                         // next_prior_test
  
//-------------------------------- deref ------------------------------------//
  //TODO
  BOOST_AUTO_TEST_CASE(deref_test)
  {
    BOOST_CHECK(true);
  }                                                         // deref_test
  
//-------------------------------- iterator_category ------------------------//
  //TODO
  BOOST_AUTO_TEST_CASE(iterator_category_test)
  {
    BOOST_CHECK(true);
  }                                                   // iterator_category_test

BOOST_AUTO_TEST_SUITE_END()