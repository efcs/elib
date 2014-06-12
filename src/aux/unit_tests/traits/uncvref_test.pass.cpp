#define BOOST_TEST_MODULE Main
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include <elib/aux/traits/uncvref.hpp>
#include <elib/aux/traits/is_same.hpp>
#include <elib/aux/static_assert.hpp>
using namespace elib::aux;

BOOST_AUTO_TEST_SUITE(elib_aux_traits_uncvref_test_suite)

BOOST_AUTO_TEST_CASE(uncvref_test)
{
    ELIB_STATIC_ASSERT(is_same<uncvref<void>, void>::value);
    ELIB_STATIC_ASSERT(is_same<uncvref<void*>, void*>::value);
    ELIB_STATIC_ASSERT(is_same<uncvref<const int>, int>::value);
    ELIB_STATIC_ASSERT(is_same<uncvref<volatile int>, int>::value);
    ELIB_STATIC_ASSERT(is_same<uncvref<const volatile int>, int>::value);
    ELIB_STATIC_ASSERT(is_same<uncvref<int &>, int>::value);
    ELIB_STATIC_ASSERT(is_same<uncvref<int &&>, int>::value);
    ELIB_STATIC_ASSERT(is_same<uncvref<int const &>, int>::value);
    ELIB_STATIC_ASSERT(is_same<uncvref<int volatile &>, int>::value);
    ELIB_STATIC_ASSERT(is_same<uncvref<int const volatile &>, int>::value);
    ELIB_STATIC_ASSERT(is_same<uncvref<int const &&>, int>::value);
    ELIB_STATIC_ASSERT(is_same<uncvref<int volatile &&>, int>::value);
    ELIB_STATIC_ASSERT(is_same<uncvref<int const volatile &&>, int>::value);
    BOOST_CHECK(true);
}

BOOST_AUTO_TEST_SUITE_END()