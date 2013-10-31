#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>


BOOST_AUTO_TEST_SUITE(test_asan_test_suite)

#if 0

BOOST_AUTO_TEST_CASE(test_asan_init)
{
  int *x = new int;
  *x = 3;
  delete x;
  int y = *x;
}
# endif

BOOST_AUTO_TEST_SUITE_END()
