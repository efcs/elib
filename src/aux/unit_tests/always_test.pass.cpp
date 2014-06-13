// REQUIRES: ELIB_AUX_SOURCE, ELIB_BOOST_TEST
#define BOOST_TEST_MODULE Main
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include <elib/aux/always.hpp>
#include <elib/aux/traits/is_same.hpp>

using namespace elib;

BOOST_AUTO_TEST_SUITE(elib_aux_always_test_suite)

BOOST_AUTO_TEST_CASE(always_true_test)
{
    static_assert(
        aux::always<>::value
      , "must be true"
      );
    
    BOOST_CHECK(true);
}

BOOST_AUTO_TEST_CASE(never_true_test)
{
    static_assert(
        not aux::never<>::value
      , "must never be true"
      );
    
    BOOST_CHECK(true);
}

BOOST_AUTO_TEST_CASE(always_void_test)
{
    static_assert(
        aux::is_same<aux::always_void<>, void>::value
      , "must be void"
      );
    BOOST_CHECK(true);
}


BOOST_AUTO_TEST_SUITE_END()