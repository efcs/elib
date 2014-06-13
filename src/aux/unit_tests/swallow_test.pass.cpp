// REQUIRES: ELIB_AUX_SOURCE, ELIB_BOOST_TEST
#define BOOST_TEST_MODULE Main
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include <elib/aux/swallow.hpp>

using namespace elib;

BOOST_AUTO_TEST_SUITE(elib_aux_swallow_test_suite)

BOOST_AUTO_TEST_CASE(swallow_test)
{
    // check that signatures are well formed
    aux::swallow();
    aux::swallow(int{0});
    int x = 0;
    aux::swallow(x, nullptr);
    BOOST_CHECK(true);
}

BOOST_AUTO_TEST_SUITE_END()