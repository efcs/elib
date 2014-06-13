// REQUIRES: ELIB_AUX_SOURCE, ELIB_BOOST_TEST
#define BOOST_TEST_MODULE Main
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include <elib/aux/traits/sfinae_common_type.hpp>
#include <elib/aux/traits/is_same.hpp>
#include <elib/aux/traits/has_type.hpp>
#include <elib/aux/static_assert.hpp>
#include <type_traits> /* for std::common_type */
using namespace elib::aux;

struct base1 {};
struct base2 {};
struct base3 {};

struct no_common {};

BOOST_AUTO_TEST_SUITE(elib_aux_traits_sfinae_common_type_test_suite)

BOOST_AUTO_TEST_CASE(same_type_test)
{
    using CT = sfinae_common_type<base1, base1, base1>::type;
    using SCT = std::common_type<base1, base1, base1>::type;
    ELIB_STATIC_ASSERT(is_same<CT, SCT>::value);
    BOOST_CHECK(true);
}

BOOST_AUTO_TEST_CASE(integral_common_type_test)
{
    using CT = sfinae_common_type<
            bool, char, signed char, unsigned char
          , short, unsigned short
          , int, unsigned
          , long, unsigned long
          , long long, unsigned long long
          >::type;
     using SCT = std::common_type<
            bool, char, signed char, unsigned char
          , short, unsigned short
          , int, unsigned
          , long, unsigned long
          , long long, unsigned long long
          >::type;
    ELIB_STATIC_ASSERT(is_same<CT, SCT>::value);
    BOOST_CHECK(true);
}

BOOST_AUTO_TEST_CASE(no_common_type_test)
{
    using CT = sfinae_common_type<base1, base2>;
    ELIB_STATIC_ASSERT(not has_type<CT>::value);
    BOOST_CHECK(true);
}

BOOST_AUTO_TEST_SUITE_END()