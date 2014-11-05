// REQUIRES: ELIB_AUX
#include <elib/aux.hpp>
#include "rapid-cxx-test.hpp"

using namespace elib;

struct dummy {};

TEST_SUITE(aux_forward_test_suite)

/// Coverage test
TEST_CASE(aux_forward_value)
{
    elib::forward<dummy>(dummy{});
    static_assert(
        aux::is_rvalue_reference<decltype(elib::forward<dummy>(dummy{}))>::value
      , "Must return an rvalue"
    );
    TEST_CHECK(true);    
}

/// Coverage test
TEST_CASE(aux_forward_ref)
{
    dummy d;
    elib::forward<dummy &>(d);
    static_assert(
        aux::is_lvalue_reference<decltype(elib::forward<dummy &>(d))>::value
      , "Must return an lvalue"
    );
    TEST_CHECK(true);    
}






TEST_SUITE_END()