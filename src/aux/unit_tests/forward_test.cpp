#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include <elib/aux.hpp>

using namespace elib;

struct dummy {};

BOOST_AUTO_TEST_SUITE(aux_forward_test_suite)

/// Coverage test
BOOST_AUTO_TEST_CASE(aux_forward_value)
{
    elib::forward<dummy>(dummy{});
    static_assert(
        aux::is_rvalue_reference<decltype(elib::forward<dummy>(dummy{}))>::value
      , "Must return an rvalue"
    );
    BOOST_CHECK(true);    
}

/// Coverage test
BOOST_AUTO_TEST_CASE(aux_forward_ref)
{
    dummy d;
    elib::forward<dummy &>(d);
    static_assert(
        aux::is_lvalue_reference<decltype(elib::forward<dummy &>(d))>::value
      , "Must return an lvalue"
    );
    BOOST_CHECK(true);    
}






BOOST_AUTO_TEST_SUITE_END()