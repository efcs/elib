// REQUIRES: ELIB_AUX_SOURCE, ELIB_BOOST_TEST
#define BOOST_TEST_MODULE Main
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include <elib/aux/no_decay.hpp>
#include <elib/aux/traits/is_same.hpp>

using namespace elib;

BOOST_AUTO_TEST_SUITE(elib_aux_no_decay_test_suite)

BOOST_AUTO_TEST_CASE(type_test)
{
    static_assert(
        aux::is_same<typename aux::no_decay<int[]>::type, int[]>::value
      , "int[] and int[] must be the same"
      );
    
    BOOST_CHECK(true);
}

BOOST_AUTO_TEST_SUITE_END()