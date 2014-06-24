// REQUIRES: ELIB_AUX
#include <elib/aux/traits/sfinae_common_type.hpp>
#include <elib/aux/traits/has_type.hpp>
#include <type_traits> /* for std::common_type */
#include "rapid-cxx-test.hpp"
using namespace elib::aux;

struct base1 {};
struct base2 {};
struct base3 {};

struct no_common {};

TEST_SUITE(elib_aux_traits_sfinae_common_type_test_suite)

TEST_CASE(same_type_test)
{
    using CT = sfinae_common_type<base1, base1, base1>::type;
    using SCT = std::common_type<base1, base1, base1>::type;
    TEST_SAME_TYPE(CT, SCT);
}

TEST_CASE(integral_common_type_test)
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
    TEST_SAME_TYPE(CT, SCT);
}

TEST_CASE(no_common_type_test)
{
    using CT = sfinae_common_type<base1, base2>;
    TEST_STATIC_ASSERT(not has_type<CT>::value);
}

TEST_SUITE_END()