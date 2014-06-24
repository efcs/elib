// REQUIRES: ELIB_AUX
#include <elib/aux/swallow.hpp>
#include "rapid-cxx-test.hpp"

using namespace elib;

TEST_SUITE(elib_aux_swallow_test_suite)

TEST_CASE(swallow_test)
{
    // check that signatures are well formed
    aux::swallow();
    aux::swallow(int{0});
    int x = 0;
    aux::swallow(x, nullptr);
    TEST_CHECK(true);
}

TEST_SUITE_END()