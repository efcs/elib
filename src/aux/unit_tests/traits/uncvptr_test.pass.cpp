// REQUIRES: ELIB_AUX
#include <elib/aux/traits/uncvptr.hpp>
#include "rapid-cxx-test.hpp"
using namespace elib::aux;

TEST_SUITE(elib_aux_traits_uncvptr_test_suite)

TEST_CASE(uncvptr_test)
{
    TEST_SAME_TYPE(uncvptr<void>, void);
    TEST_SAME_TYPE(uncvptr<void*>, void);
    TEST_SAME_TYPE(uncvptr<const int>, int);
    TEST_SAME_TYPE(uncvptr<volatile int>, int);
    TEST_SAME_TYPE(uncvptr<const volatile int>, int);
    TEST_SAME_TYPE(uncvptr<int *>, int);
    TEST_SAME_TYPE(uncvptr<int const *>, int);
    TEST_SAME_TYPE(uncvptr<int volatile *>, int);
    TEST_SAME_TYPE(uncvptr<int const volatile*>, int);
    
    TEST_SAME_TYPE(uncvptr<int const* const>, int);
    TEST_SAME_TYPE(uncvptr<int const volatile* const volatile>, int);
}

TEST_CASE(uncvptr_all_test)
{
    TEST_SAME_TYPE(uncvptr_all<void>, void);
    TEST_SAME_TYPE(uncvptr_all<void*>, void);
    TEST_SAME_TYPE(uncvptr_all<const int>, int);
    TEST_SAME_TYPE(uncvptr_all<volatile int>, int);
    TEST_SAME_TYPE(uncvptr_all<const volatile int>, int);
    TEST_SAME_TYPE(uncvptr_all<int *>, int);
    TEST_SAME_TYPE(uncvptr_all<int const *>, int);
    TEST_SAME_TYPE(uncvptr_all<int volatile *>, int);
    TEST_SAME_TYPE(uncvptr_all<int const volatile*>, int);
    
    TEST_SAME_TYPE(uncvptr_all<int const* const>, int);
    TEST_SAME_TYPE(uncvptr_all<int const volatile* const volatile>, int);
    
    TEST_SAME_TYPE(uncvptr_all<int* const * volatile * const volatile>, int);
    TEST_SAME_TYPE(uncvptr_all<int const volatile********>, int);
}

TEST_SUITE_END()