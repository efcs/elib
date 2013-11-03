#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>


BOOST_AUTO_TEST_SUITE(test_asan_test_suite)


BOOST_AUTO_TEST_CASE(test_asan_use_after_free)
{
  
  int *x = new int;
  *x = 3;
  delete x;
  
  BOOST_CHECK(true);
  
  int y = *x;
  x = nullptr;
  ((void)y);
}



BOOST_AUTO_TEST_SUITE_END()
