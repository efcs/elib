#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>


#include <elib/enumeration/bitwise_operators.h>
#include <elib/enumeration/enum_cast.h>

#undef NDEBUG
#include <elib/debug/dprint.h>

#include <type_traits>

using namespace elib;
using namespace elib::enumeration;
using namespace elib::enumeration::detail;

enum class test_e : int {
    none = 0,
    one = 1,
    one2 = 1,
    two = 2,
    two2 = 2
};


typedef int test_base_t;

struct _test : public enumeration::enum_bitwise_operators<test_e>
{ };

BOOST_AUTO_TEST_SUITE(enumeration_bitwise_operators_test_suite)

BOOST_AUTO_TEST_CASE(enumeration_bitwise_operators_init)
{
    BOOST_CHECK((is_enum_enum<test_e, test_e>::value));
    BOOST_CHECK((! is_enum_enum<int, unsigned>::value));
    BOOST_CHECK((! is_enum_enum<test_e, short>::value));
    BOOST_CHECK((! is_enum_enum<unsigned short, test_e>::value));
    
    BOOST_CHECK((is_enum_integral<test_e, unsigned>::value));
    BOOST_CHECK((! is_enum_integral<char, test_e>::value));
    BOOST_CHECK((! is_enum_integral<test_e, test_e>::value));
    BOOST_CHECK((! is_enum_integral<int, long long>::value));
    
    BOOST_CHECK((is_integral_enum<unsigned long, test_e>::value));
    BOOST_CHECK((! is_integral_enum<test_e, int>::value));
    BOOST_CHECK((! is_integral_enum<test_e, test_e>::value));
    BOOST_CHECK((! is_integral_enum<int, int>::value));
    
}

BOOST_AUTO_TEST_CASE(test_and)
{
    test_e lhs, rhs;
    test_base_t ret, expect;
    
    lhs = test_e::none;
    rhs = test_e::none;
    expect = (0 & 0);
    ret = lhs & rhs;
    BOOST_CHECK(ret == expect);
    
    lhs = test_e::none;
    rhs = test_e::one;
    expect = (0 & 1);
    ret = lhs & rhs;
    BOOST_CHECK(ret == expect);
    
    lhs = test_e::one;
    rhs = test_e::one;
    expect = (1 & 1);
    ret = lhs & rhs;
    
    lhs = test_e::none;
    rhs = test_e::two;
    expect = (0 & 2);
    ret = lhs & rhs;
    BOOST_CHECK(ret == expect);
    
    lhs = test_e::two;
    rhs = test_e::two;
    expect = (2 & 2);
    ret = lhs & rhs;
    BOOST_CHECK(ret == expect);
    
    lhs = test_e::two;
    rhs = test_e::one;
    expect = (1 & 2);
    ret = lhs & rhs;
    BOOST_CHECK(ret == expect);
}

BOOST_AUTO_TEST_CASE(test_or)
{
    test_e lhs, rhs;
    test_base_t ret, expect;
    
    lhs = test_e::none;
    rhs = test_e::none;
    expect = (0 | 0);
    ret = lhs | rhs;
    BOOST_CHECK(ret == expect);
    
    lhs = test_e::none;
    rhs = test_e::one;
    expect = (0 | 1);
    ret = lhs | rhs;
    BOOST_CHECK(ret == expect);
    
    lhs = test_e::one;
    rhs = test_e::one;
    expect = (1 | 1);
    ret = lhs | rhs;
    
    lhs = test_e::none;
    rhs = test_e::two;
    expect = (0 | 2);
    ret = lhs | rhs;
    BOOST_CHECK(ret == expect);
    
    lhs = test_e::two;
    rhs = test_e::two;
    expect = (2 | 2);
    ret = lhs | rhs;
    BOOST_CHECK(ret == expect);
    
    lhs = test_e::two;
    rhs = test_e::one;
    expect = (1 | 2);
    ret = lhs | rhs;
    BOOST_CHECK(ret == expect);
}

BOOST_AUTO_TEST_CASE(test_xor)
{
    test_e lhs, rhs;
    test_base_t ret, expect;
    
    lhs = test_e::none;
    rhs = test_e::none;
    expect = (0 ^ 0);
    ret = lhs ^ rhs;
    BOOST_CHECK(ret == expect);
    
    lhs = test_e::none;
    rhs = test_e::one;
    expect = (0 ^ 1);
    ret = lhs ^ rhs;
    BOOST_CHECK(ret == expect);
    
    lhs = test_e::one;
    rhs = test_e::one;
    expect = (1 ^ 1);
    ret = lhs ^ rhs;
    
    lhs = test_e::none;
    rhs = test_e::two;
    expect = (0 ^ 2);
    ret = lhs ^ rhs;
    BOOST_CHECK(ret == expect);
    
    lhs = test_e::two;
    rhs = test_e::two;
    expect = (2 ^ 2);
    ret = lhs ^ rhs;
    BOOST_CHECK(ret == expect);
    
    lhs = test_e::two;
    rhs = test_e::one;
    expect = (1 ^ 2);
    ret = lhs ^ rhs;
    BOOST_CHECK(ret == expect);
}

BOOST_AUTO_TEST_SUITE_END()