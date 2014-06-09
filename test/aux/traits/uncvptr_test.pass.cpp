#define BOOST_TEST_MODULE Main
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include <elib/aux/traits/uncvptr.hpp>
#include <elib/aux/traits/is_same.hpp>
#include <elib/aux/static_assert.hpp>
using namespace elib::aux;

BOOST_AUTO_TEST_SUITE(elib_aux_traits_uncvptr_test_suite)

BOOST_AUTO_TEST_CASE(uncvptr_test)
{
    ELIB_STATIC_ASSERT(is_same<uncvptr<void>, void>::value);
    ELIB_STATIC_ASSERT(is_same<uncvptr<void*>, void>::value);
    ELIB_STATIC_ASSERT(is_same<uncvptr<const int>, int>::value);
    ELIB_STATIC_ASSERT(is_same<uncvptr<volatile int>, int>::value);
    ELIB_STATIC_ASSERT(is_same<uncvptr<const volatile int>, int>::value);
    ELIB_STATIC_ASSERT(is_same<uncvptr<int *>, int>::value);
    ELIB_STATIC_ASSERT(is_same<uncvptr<int const *>, int>::value);
    ELIB_STATIC_ASSERT(is_same<uncvptr<int volatile *>, int>::value);
    ELIB_STATIC_ASSERT(is_same<uncvptr<int const volatile*>, int>::value);
    
    ELIB_STATIC_ASSERT(is_same<uncvptr<int const* const>, int>::value);
    ELIB_STATIC_ASSERT(is_same<uncvptr<int const volatile* const volatile>, int>::value);
    
    BOOST_CHECK(true);
}

BOOST_AUTO_TEST_CASE(uncvptr_all_test)
{
    ELIB_STATIC_ASSERT(is_same<uncvptr_all<void>, void>::value);
    ELIB_STATIC_ASSERT(is_same<uncvptr_all<void*>, void>::value);
    ELIB_STATIC_ASSERT(is_same<uncvptr_all<const int>, int>::value);
    ELIB_STATIC_ASSERT(is_same<uncvptr_all<volatile int>, int>::value);
    ELIB_STATIC_ASSERT(is_same<uncvptr_all<const volatile int>, int>::value);
    ELIB_STATIC_ASSERT(is_same<uncvptr_all<int *>, int>::value);
    ELIB_STATIC_ASSERT(is_same<uncvptr_all<int const *>, int>::value);
    ELIB_STATIC_ASSERT(is_same<uncvptr_all<int volatile *>, int>::value);
    ELIB_STATIC_ASSERT(is_same<uncvptr_all<int const volatile*>, int>::value);
    
    ELIB_STATIC_ASSERT(is_same<uncvptr_all<int const* const>, int>::value);
    ELIB_STATIC_ASSERT(is_same<uncvptr_all<int const volatile* const volatile>, int>::value);
    
    ELIB_STATIC_ASSERT(is_same<uncvptr_all<int* const * volatile * const volatile>, int>::value);
    ELIB_STATIC_ASSERT(is_same<uncvptr_all<int const volatile********>, int>::value);
    
    BOOST_CHECK(true);
}

BOOST_AUTO_TEST_SUITE_END()