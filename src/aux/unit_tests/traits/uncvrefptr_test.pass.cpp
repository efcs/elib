// REQUIRES: ELIB_AUX_SOURCE
#include <elib/aux/traits/uncvrefptr.hpp>
#include "rapid-cxx-test.hpp"
using namespace elib::aux;


TEST_SUITE(elib_aux_traits_uncvrefptr_test_suite)

TEST_CASE(uncvrefptr_test)
{
    TEST_SAME_TYPE(uncvrefptr<void>, void);
    TEST_SAME_TYPE(uncvrefptr<const int>, int);
    TEST_SAME_TYPE(uncvrefptr<volatile int>, int);
    TEST_SAME_TYPE(uncvrefptr<const volatile int>, int);
    TEST_SAME_TYPE(uncvrefptr<int &>, int);
    TEST_SAME_TYPE(uncvrefptr<int &&>, int);
    TEST_SAME_TYPE(uncvrefptr<int const &>, int);
    TEST_SAME_TYPE(uncvrefptr<int volatile &>, int);
    TEST_SAME_TYPE(uncvrefptr<int const volatile &>, int);
    TEST_SAME_TYPE(uncvrefptr<int const &&>, int);
    TEST_SAME_TYPE(uncvrefptr<int volatile &&>, int);
    TEST_SAME_TYPE(uncvrefptr<int const volatile &&>, int);
    
    TEST_SAME_TYPE(uncvrefptr<void>, void);
    TEST_SAME_TYPE(uncvrefptr<void*>, void);
    TEST_SAME_TYPE(uncvrefptr<const int>, int);
    TEST_SAME_TYPE(uncvrefptr<volatile int>, int);
    TEST_SAME_TYPE(uncvrefptr<const volatile int>, int);
    TEST_SAME_TYPE(uncvrefptr<int *>, int);
    TEST_SAME_TYPE(uncvrefptr<int const *>, int);
    TEST_SAME_TYPE(uncvrefptr<int volatile *>, int);
    TEST_SAME_TYPE(uncvrefptr<int const volatile*>, int);
    
    TEST_SAME_TYPE(uncvrefptr<int const* const>, int);
    TEST_SAME_TYPE(uncvrefptr<int const volatile* const volatile>, int);
    
    TEST_CHECK(true);
}

TEST_CASE(uncvrefptr_all_test)
{
    TEST_SAME_TYPE(uncvrefptr_all<void>, void);
    TEST_SAME_TYPE(uncvrefptr_all<const int>, int);
    TEST_SAME_TYPE(uncvrefptr_all<volatile int>, int);
    TEST_SAME_TYPE(uncvrefptr_all<const volatile int>, int);
    TEST_SAME_TYPE(uncvrefptr_all<int &>, int);
    TEST_SAME_TYPE(uncvrefptr_all<int &&>, int);
    TEST_SAME_TYPE(uncvrefptr_all<int const &>, int);
    TEST_SAME_TYPE(uncvrefptr_all<int volatile &>, int);
    TEST_SAME_TYPE(uncvrefptr_all<int const volatile &>, int);
    TEST_SAME_TYPE(uncvrefptr_all<int const &&>, int);
    TEST_SAME_TYPE(uncvrefptr_all<int volatile &&>, int);
    TEST_SAME_TYPE(uncvrefptr_all<int const volatile &&>, int);
    
    TEST_SAME_TYPE(uncvrefptr_all<void>, void);
    TEST_SAME_TYPE(uncvrefptr_all<void*>, void);
    TEST_SAME_TYPE(uncvrefptr_all<const int>, int);
    TEST_SAME_TYPE(uncvrefptr_all<volatile int>, int);
    TEST_SAME_TYPE(uncvrefptr_all<const volatile int>, int);
    TEST_SAME_TYPE(uncvrefptr_all<int *>, int);
    TEST_SAME_TYPE(uncvrefptr_all<int const *>, int);
    TEST_SAME_TYPE(uncvrefptr_all<int volatile *>, int);
    TEST_SAME_TYPE(uncvrefptr_all<int const volatile*>, int);
    
    TEST_SAME_TYPE(uncvrefptr_all<int const* const>, int);
    TEST_SAME_TYPE(uncvrefptr_all<int const volatile* const volatile>, int);
    
    TEST_SAME_TYPE(uncvrefptr_all<int const* const>, int);
    TEST_SAME_TYPE(uncvrefptr_all<int const volatile* const volatile>, int);
    
    TEST_SAME_TYPE(uncvrefptr_all<int* const * volatile * const volatile>, int);
    TEST_SAME_TYPE(uncvrefptr_all<int const volatile********>, int);
    TEST_SAME_TYPE(uncvrefptr_all<int const* volatile *&>, int);
}

TEST_SUITE_END()
