// REQUIRES: ELIB_AUX_SOURCE
#include <elib/aux/traits/uncvref.hpp>
#include "rapid-cxx-test.hpp"
using namespace elib::aux;

TEST_SUITE(elib_aux_traits_uncvref_test_suite)

TEST_CASE(uncvref_test)
{
    TEST_SAME_TYPE(uncvref<void>, void);
    TEST_SAME_TYPE(uncvref<void*>, void*);
    TEST_SAME_TYPE(uncvref<const int>, int);
    TEST_SAME_TYPE(uncvref<volatile int>, int);
    TEST_SAME_TYPE(uncvref<const volatile int>, int);
    TEST_SAME_TYPE(uncvref<int &>, int);
    TEST_SAME_TYPE(uncvref<int &&>, int);
    TEST_SAME_TYPE(uncvref<int const &>, int);
    TEST_SAME_TYPE(uncvref<int volatile &>, int);
    TEST_SAME_TYPE(uncvref<int const volatile &>, int);
    TEST_SAME_TYPE(uncvref<int const &&>, int);
    TEST_SAME_TYPE(uncvref<int volatile &&>, int);
    TEST_SAME_TYPE(uncvref<int const volatile &&>, int);
}

TEST_SUITE_END()