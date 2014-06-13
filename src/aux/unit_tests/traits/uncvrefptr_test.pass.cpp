// REQUIRES: ELIB_AUX_SOURCE, ELIB_BOOST_TEST
#define BOOST_TEST_MODULE Main
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include <elib/aux/traits/uncvrefptr.hpp>
#include <elib/aux/traits/is_same.hpp>
#include <elib/aux/static_assert.hpp>
using namespace elib::aux;


BOOST_AUTO_TEST_SUITE(elib_aux_traits_uncvrefptr_test_suite)

BOOST_AUTO_TEST_CASE(uncvrefptr_test)
{
    ELIB_STATIC_ASSERT(is_same<uncvrefptr<void>, void>::value);
    ELIB_STATIC_ASSERT(is_same<uncvrefptr<const int>, int>::value);
    ELIB_STATIC_ASSERT(is_same<uncvrefptr<volatile int>, int>::value);
    ELIB_STATIC_ASSERT(is_same<uncvrefptr<const volatile int>, int>::value);
    ELIB_STATIC_ASSERT(is_same<uncvrefptr<int &>, int>::value);
    ELIB_STATIC_ASSERT(is_same<uncvrefptr<int &&>, int>::value);
    ELIB_STATIC_ASSERT(is_same<uncvrefptr<int const &>, int>::value);
    ELIB_STATIC_ASSERT(is_same<uncvrefptr<int volatile &>, int>::value);
    ELIB_STATIC_ASSERT(is_same<uncvrefptr<int const volatile &>, int>::value);
    ELIB_STATIC_ASSERT(is_same<uncvrefptr<int const &&>, int>::value);
    ELIB_STATIC_ASSERT(is_same<uncvrefptr<int volatile &&>, int>::value);
    ELIB_STATIC_ASSERT(is_same<uncvrefptr<int const volatile &&>, int>::value);
    
    ELIB_STATIC_ASSERT(is_same<uncvrefptr<void>, void>::value);
    ELIB_STATIC_ASSERT(is_same<uncvrefptr<void*>, void>::value);
    ELIB_STATIC_ASSERT(is_same<uncvrefptr<const int>, int>::value);
    ELIB_STATIC_ASSERT(is_same<uncvrefptr<volatile int>, int>::value);
    ELIB_STATIC_ASSERT(is_same<uncvrefptr<const volatile int>, int>::value);
    ELIB_STATIC_ASSERT(is_same<uncvrefptr<int *>, int>::value);
    ELIB_STATIC_ASSERT(is_same<uncvrefptr<int const *>, int>::value);
    ELIB_STATIC_ASSERT(is_same<uncvrefptr<int volatile *>, int>::value);
    ELIB_STATIC_ASSERT(is_same<uncvrefptr<int const volatile*>, int>::value);
    
    ELIB_STATIC_ASSERT(is_same<uncvrefptr<int const* const>, int>::value);
    ELIB_STATIC_ASSERT(is_same<uncvrefptr<int const volatile* const volatile>, int>::value);
    
    BOOST_CHECK(true);
}

BOOST_AUTO_TEST_CASE(uncvrefptr_all_test)
{
    ELIB_STATIC_ASSERT(is_same<uncvrefptr_all<void>, void>::value);
    ELIB_STATIC_ASSERT(is_same<uncvrefptr_all<const int>, int>::value);
    ELIB_STATIC_ASSERT(is_same<uncvrefptr_all<volatile int>, int>::value);
    ELIB_STATIC_ASSERT(is_same<uncvrefptr_all<const volatile int>, int>::value);
    ELIB_STATIC_ASSERT(is_same<uncvrefptr_all<int &>, int>::value);
    ELIB_STATIC_ASSERT(is_same<uncvrefptr_all<int &&>, int>::value);
    ELIB_STATIC_ASSERT(is_same<uncvrefptr_all<int const &>, int>::value);
    ELIB_STATIC_ASSERT(is_same<uncvrefptr_all<int volatile &>, int>::value);
    ELIB_STATIC_ASSERT(is_same<uncvrefptr_all<int const volatile &>, int>::value);
    ELIB_STATIC_ASSERT(is_same<uncvrefptr_all<int const &&>, int>::value);
    ELIB_STATIC_ASSERT(is_same<uncvrefptr_all<int volatile &&>, int>::value);
    ELIB_STATIC_ASSERT(is_same<uncvrefptr_all<int const volatile &&>, int>::value);
    
    ELIB_STATIC_ASSERT(is_same<uncvrefptr_all<void>, void>::value);
    ELIB_STATIC_ASSERT(is_same<uncvrefptr_all<void*>, void>::value);
    ELIB_STATIC_ASSERT(is_same<uncvrefptr_all<const int>, int>::value);
    ELIB_STATIC_ASSERT(is_same<uncvrefptr_all<volatile int>, int>::value);
    ELIB_STATIC_ASSERT(is_same<uncvrefptr_all<const volatile int>, int>::value);
    ELIB_STATIC_ASSERT(is_same<uncvrefptr_all<int *>, int>::value);
    ELIB_STATIC_ASSERT(is_same<uncvrefptr_all<int const *>, int>::value);
    ELIB_STATIC_ASSERT(is_same<uncvrefptr_all<int volatile *>, int>::value);
    ELIB_STATIC_ASSERT(is_same<uncvrefptr_all<int const volatile*>, int>::value);
    
    ELIB_STATIC_ASSERT(is_same<uncvrefptr_all<int const* const>, int>::value);
    ELIB_STATIC_ASSERT(is_same<uncvrefptr_all<int const volatile* const volatile>, int>::value);
    
    ELIB_STATIC_ASSERT(is_same<uncvrefptr_all<int const* const>, int>::value);
    ELIB_STATIC_ASSERT(is_same<uncvrefptr_all<int const volatile* const volatile>, int>::value);
    
    ELIB_STATIC_ASSERT(is_same<uncvrefptr_all<int* const * volatile * const volatile>, int>::value);
    ELIB_STATIC_ASSERT(is_same<uncvrefptr_all<int const volatile********>, int>::value);
    ELIB_STATIC_ASSERT(is_same<uncvrefptr_all<int const* volatile *&>, int>::value);
    
    BOOST_CHECK(true);
}

BOOST_AUTO_TEST_SUITE_END()
