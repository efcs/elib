#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE ELIB_ALL
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(main_test_suite)

BOOST_AUTO_TEST_CASE(main_test)
{
    BOOST_CHECK(true);
}

BOOST_AUTO_TEST_SUITE_END()