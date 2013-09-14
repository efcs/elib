#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include <elib/enumeration/operators.h>
#include <elib/enumeration/enum_cast.h>
#undef NDEBUG
#include <elib/debug/dprint.h>


enum class t_all {
    none = 0,
    one = 1,
    two = 2,
    three = 3,
    four = 4,
    five = 5,
    six = 6,
    seven = 7,
    eight = 8,
    nine = 9,
    ten = 10
};

enum class t_arith {
    none = 0,
    one = 1,
    two = 2,
    three = 3,
    four = 4,
    five = 5,
    six = 6,
    seven = 7,
    eight = 8,
    nine = 9,
    ten = 10
};

enum class t_arith_m {
    none = 0,
    one = 1,
    two = 2,
    three = 3,
    four = 4,
    five = 5,
    six = 6,
    seven = 7,
    eight = 8,
    nine = 9,
    ten = 10
};

enum class t_logic {
    none = 0,
    one = 1,
    two = 2,
    three = 3,
    four = 4,
    five = 5,
    six = 6,
    seven = 7,
    eight = 8,
    nine = 9,
    ten = 10
};

enum class t_logic_m {
    none = 0,
    one = 1,
    two = 2,
    three = 3,
    four = 4,
    five = 5,
    six = 6,
    seven = 7,
    eight = 8,
    nine = 9,
    ten = 10
};

enum class t_bit {
    none = 0,
    one = 1,
    two = 2,
    three = 3,
    four = 4,
    five = 5,
    six = 6,
    seven = 7,
    eight = 8,
    nine = 9,
    ten = 10
};

enum class t_bit_m {
    none = 0,
    one = 1,
    two = 2,
    three = 3,
    four = 4,
    five = 5,
    six = 6,
    seven = 7,
    eight = 8,
    nine = 9,
    ten = 10
};

namespace elib {
namespace enumeration {
  
//
// t_all
//
    
template <>
struct allow_arithmetic_operators<t_all> : public std::true_type
{ };
    
template <>
struct allow_logical_operators<t_all> : public std::true_type
{ };

template <>
struct allow_bitwise_operators<t_all> : public std::true_type
{ };

template <>
struct allow_mixed_arithmetic_operators<t_all> : public std::true_type
{ };

template <>
struct allow_mixed_logical_operators<t_all> : public std::true_type
{ };

template <>
struct allow_mixed_bitwise_operators<t_all> : public std::true_type
{ };

//
//  t_arith && t_arith_m
//

template <>
struct allow_arithmetic_operators<t_arith> : public std::true_type
{ };

template <>
struct allow_mixed_arithmetic_operators<t_arith_m> : public std::true_type
{ };


//
//  t_logic && t_logic_m
//

template <>
struct allow_logical_operators<t_logic> : public std::true_type
{ };

template <>
struct allow_mixed_logical_operators<t_logic_m> : public std::true_type
{ };


//
//  t_bit && t_bit_m
//

template <>
struct allow_bitwise_operators<t_bit> : public std::true_type
{ };

template <>
struct allow_mixed_bitwise_operators<t_bit_m> : public std::true_type
{ };


} /* namespace enumeration */
} /* namespace elib */


namespace en = elib::enumeration;


BOOST_AUTO_TEST_SUITE(enumeration_operators_test_suite)

BOOST_AUTO_TEST_CASE(check_t_all)
{
    // suppress boost warning
    BOOST_REQUIRE(true);
    static_assert(en::allow_arithmetic_operators<t_all>::value, "");
    static_assert(en::allow_mixed_arithmetic_operators<t_all>::value, "");
    static_assert(en::detail::is_arithmetic_allowed<t_all>::value, "");
    static_assert(en::detail::is_mixed_arithmetic_allowed<t_all>::value, "");
    
    static_assert(en::allow_logical_operators<t_all>::value, "");
    static_assert(en::allow_mixed_logical_operators<t_all>::value, "");
    static_assert(en::detail::is_logical_allowed<t_all>::value, "");
    static_assert(en::detail::is_mixed_logical_allowed<t_all>::value, "");
    
    static_assert(en::allow_bitwise_operators<t_all>::value, "");
    static_assert(en::allow_mixed_bitwise_operators<t_all>::value, "");
    static_assert(en::detail::is_bitwise_allowed<t_all>::value, "");
    static_assert(en::detail::is_mixed_bitwise_allowed<t_all>::value, "");
}

BOOST_AUTO_TEST_CASE(check_t_arith)
{
    // suppress boost warning
    BOOST_REQUIRE(true);
    static_assert(en::allow_arithmetic_operators<t_arith>::value, "");
    static_assert(! en::allow_mixed_arithmetic_operators<t_arith>::value, "");
    static_assert(en::detail::is_arithmetic_allowed<t_arith>::value, "");
    static_assert(! en::detail::is_mixed_arithmetic_allowed<t_arith>::value, "");
    
    static_assert(! en::allow_logical_operators<t_arith>::value, "");
    static_assert(! en::allow_mixed_logical_operators<t_arith>::value, "");
    static_assert(! en::detail::is_logical_allowed<t_arith>::value, "");
    static_assert(! en::detail::is_mixed_logical_allowed<t_arith>::value, "");
    
    static_assert(! en::allow_bitwise_operators<t_arith>::value, "");
    static_assert(! en::allow_mixed_bitwise_operators<t_arith>::value, "");
    static_assert(! en::detail::is_bitwise_allowed<t_arith>::value, "");
    static_assert(! en::detail::is_mixed_bitwise_allowed<t_arith>::value, "");
    
//
// t_arith_m
//
    
    static_assert(! en::allow_arithmetic_operators<t_arith_m>::value, "");
    static_assert(en::allow_mixed_arithmetic_operators<t_arith_m>::value, "");
    static_assert(en::detail::is_arithmetic_allowed<t_arith_m>::value, "");
    static_assert(en::detail::is_mixed_arithmetic_allowed<t_arith_m>::value, "");
    
    static_assert(! en::allow_logical_operators<t_arith_m>::value, "");
    static_assert(! en::allow_mixed_logical_operators<t_arith_m>::value, "");
    static_assert(! en::detail::is_logical_allowed<t_arith_m>::value, "");
    static_assert(! en::detail::is_mixed_logical_allowed<t_arith_m>::value, "");
    
    static_assert(! en::allow_bitwise_operators<t_arith_m>::value, "");
    static_assert(! en::allow_mixed_bitwise_operators<t_arith_m>::value, "");
    static_assert(! en::detail::is_bitwise_allowed<t_arith_m>::value, "");
    static_assert(! en::detail::is_mixed_bitwise_allowed<t_arith_m>::value, "");
    
    int lhs, rhs, expect;
    t_arith_m lhs_e, rhs_e, lhs_ret, ret, mret1, mret2, mlhs_ret;
    
    for (int i=0; i < 10; ++i) {
        lhs = i;
        lhs_e = static_cast<t_arith_m>(lhs);
    
        expect = +lhs;
        ret = +lhs_e;
        BOOST_CHECK(en::base_enum_cast(ret) == expect);
        
        expect = -lhs;
        ret = -lhs_e;
        BOOST_CHECK(en::base_enum_cast(ret) == expect);
        
        lhs = i;
        lhs_e = static_cast<t_arith_m>(lhs);
        expect = ++lhs;
        ret = ++lhs_e;
        BOOST_CHECK(en::base_enum_cast(ret) == expect);
        BOOST_CHECK(en::base_enum_cast(lhs_e) == lhs);
        
        lhs = i;
        lhs_e = static_cast<t_arith_m>(lhs);
        expect = lhs++;
        ret = lhs_e++;
        BOOST_CHECK(en::base_enum_cast(ret) == expect);
        BOOST_CHECK(en::base_enum_cast(lhs_e) == lhs);
        
        lhs = i;
        lhs_e = static_cast<t_arith_m>(lhs);
        expect = --lhs;
        ret = --lhs_e;
        BOOST_CHECK(en::base_enum_cast(ret) == expect);
        BOOST_CHECK(en::base_enum_cast(lhs_e) == lhs);
        
        lhs = i;
        lhs_e = static_cast<t_arith_m>(lhs);
        expect = lhs--;
        ret = lhs_e--;
        BOOST_CHECK(en::base_enum_cast(ret) == expect);
        BOOST_CHECK(en::base_enum_cast(lhs_e) == lhs);
        
    }
    
    for (int i=0; i <= 10; ++i) {
        for (int j=0; j <= 10; ++j) {
            lhs = i;
            rhs = j;
            lhs_e = static_cast<t_arith_m>(lhs);
            rhs_e = static_cast<t_arith_m>(rhs);
            
            expect = lhs + rhs;
            ret = lhs_e + rhs_e;
            mret1 = lhs_e + rhs;
            mret2 = lhs + rhs_e;
            lhs_ret = lhs_e;
            lhs_ret += rhs_e;
            mlhs_ret = lhs_e;
            mlhs_ret += rhs;
            BOOST_CHECK(en::base_enum_cast(ret) == expect);
            BOOST_CHECK(en::base_enum_cast(mret1) == expect);
            BOOST_CHECK(en::base_enum_cast(mret2) == expect);
            BOOST_CHECK(en::base_enum_cast(lhs_ret) == expect);
            BOOST_CHECK(en::base_enum_cast(mlhs_ret) == expect);
            
            expect = lhs - rhs;
            ret = lhs_e - rhs_e;
            mret1 = lhs_e - rhs;
            mret2 = lhs - rhs_e;
            lhs_ret = lhs_e;
            lhs_ret -= rhs_e;
            mlhs_ret = lhs_e;
            mlhs_ret -= rhs;
            BOOST_CHECK(en::base_enum_cast(ret) == expect);
            BOOST_CHECK(en::base_enum_cast(mret1) == expect);
            BOOST_CHECK(en::base_enum_cast(mret2) == expect);
            BOOST_CHECK(en::base_enum_cast(lhs_ret) == expect);
            BOOST_CHECK(en::base_enum_cast(mlhs_ret) == expect);
            
            if (rhs != 0) {
                expect = lhs / rhs;
                ret = lhs_e / rhs_e;
                mret1 = lhs_e / rhs;
                mret2 = lhs / rhs_e;
                lhs_ret = lhs_e;
                lhs_ret /= rhs_e;
                mlhs_ret = lhs_e;
                mlhs_ret /= rhs;
                BOOST_CHECK(en::base_enum_cast(ret) == expect);
                BOOST_CHECK(en::base_enum_cast(mret1) == expect);
                BOOST_CHECK(en::base_enum_cast(mret2) == expect);
                BOOST_CHECK(en::base_enum_cast(lhs_ret) == expect);
                BOOST_CHECK(en::base_enum_cast(mlhs_ret) == expect);
                
                expect = lhs % rhs;
                ret = lhs_e % rhs_e;
                mret1 = lhs_e % rhs;
                mret2 = lhs % rhs_e;
                lhs_ret = lhs_e;
                lhs_ret %= rhs_e;
                mlhs_ret = lhs_e;
                mlhs_ret %= rhs;
                BOOST_CHECK(en::base_enum_cast(ret) == expect);
                BOOST_CHECK(en::base_enum_cast(mret1) == expect);
                BOOST_CHECK(en::base_enum_cast(mret2) == expect);
                BOOST_CHECK(en::base_enum_cast(lhs_ret) == expect);
                BOOST_CHECK(en::base_enum_cast(mlhs_ret) == expect);
            }
            
            expect = lhs * rhs;
            ret = lhs_e * rhs_e;
            mret1 = lhs_e * rhs;
            mret2 = lhs * rhs_e;
            lhs_ret = lhs_e;
            lhs_ret *= rhs_e;
            mlhs_ret = lhs_e;
            mlhs_ret *= rhs;
            BOOST_CHECK(en::base_enum_cast(ret) == expect);
            BOOST_CHECK(en::base_enum_cast(mret1) == expect);
            BOOST_CHECK(en::base_enum_cast(mret2) == expect);
            BOOST_CHECK(en::base_enum_cast(lhs_ret) == expect);
            BOOST_CHECK(en::base_enum_cast(mlhs_ret) == expect);
        }
    }
   
}

BOOST_AUTO_TEST_CASE(check_t_logic)
{
    // suppress boost warning
    BOOST_REQUIRE(true);
    static_assert(! en::allow_arithmetic_operators<t_logic>::value, "");
    static_assert(! en::allow_mixed_arithmetic_operators<t_logic>::value, "");
    static_assert(! en::detail::is_arithmetic_allowed<t_logic>::value, "");
    static_assert(! en::detail::is_mixed_arithmetic_allowed<t_logic>::value, "");
    
    static_assert(en::allow_logical_operators<t_logic>::value, "");
    static_assert(! en::allow_mixed_logical_operators<t_logic>::value, "");
    static_assert(en::detail::is_logical_allowed<t_logic>::value, "");
    static_assert(! en::detail::is_mixed_logical_allowed<t_logic>::value, "");
    
    static_assert(! en::allow_bitwise_operators<t_logic>::value, "");
    static_assert(! en::allow_mixed_bitwise_operators<t_logic>::value, "");
    static_assert(! en::detail::is_bitwise_allowed<t_logic>::value, "");
    static_assert(! en::detail::is_mixed_bitwise_allowed<t_logic>::value, "");
    
//
// t_logic_m
//
    
    static_assert(! en::allow_arithmetic_operators<t_logic_m>::value, "");
    static_assert(! en::allow_mixed_arithmetic_operators<t_logic_m>::value, "");
    static_assert(! en::detail::is_arithmetic_allowed<t_logic_m>::value, "");
    static_assert(! en::detail::is_mixed_arithmetic_allowed<t_logic_m>::value, "");
    
    static_assert(! en::allow_logical_operators<t_logic_m>::value, "");
    static_assert(en::allow_mixed_logical_operators<t_logic_m>::value, "");
    static_assert(en::detail::is_logical_allowed<t_logic_m>::value, "");
    static_assert(en::detail::is_mixed_logical_allowed<t_logic_m>::value, "");
    
    static_assert(! en::allow_bitwise_operators<t_logic_m>::value, "");
    static_assert(! en::allow_mixed_bitwise_operators<t_logic_m>::value, "");
    static_assert(! en::detail::is_bitwise_allowed<t_logic_m>::value, "");
    static_assert(! en::detail::is_mixed_bitwise_allowed<t_logic_m>::value, "");
    
    t_logic_m lhs_e, rhs_e;
    int  lhs, rhs;
    bool ret, expect, mret1, mret2;
    
    for (int i=0; i <= 10; ++i) {
        lhs = i;
        lhs_e = static_cast<t_logic_m>(lhs);
        ret = !lhs_e;
        expect = static_cast<bool>(! lhs);
        BOOST_CHECK(ret == expect);
    }
    
    for (int i=0; i <= 10; ++i) {
        for (int j=0; j <= 10; ++j) {
            lhs = i;
            rhs = j;
            lhs_e = static_cast<t_logic_m>(lhs);
            rhs_e = static_cast<t_logic_m>(rhs);
            ret = lhs_e && rhs_e;
            mret1 = lhs_e && rhs;
            mret2 = lhs && rhs_e;
            expect = static_cast<bool>(lhs && rhs);
            BOOST_CHECK(ret == expect);
            BOOST_CHECK(mret1 == expect);
            BOOST_CHECK(mret2 == expect);
            
            lhs = i;
            rhs = j;
            lhs_e = static_cast<t_logic_m>(lhs);
            rhs_e = static_cast<t_logic_m>(rhs);
            ret = lhs_e || rhs_e;
            mret1 = lhs_e || rhs;
            mret2 = lhs || rhs_e;
            expect = static_cast<bool>(lhs || rhs);
            BOOST_CHECK(ret == expect);
            BOOST_CHECK(mret1 == expect);
            BOOST_CHECK(mret2 == expect);
        }
    }
}


BOOST_AUTO_TEST_CASE(check_t_bit)
{
    // suppress boost warning
    BOOST_REQUIRE(true);
    
    
    
    static_assert(! en::allow_arithmetic_operators<t_bit>::value, "");
    static_assert(! en::allow_mixed_arithmetic_operators<t_bit>::value, "");
    static_assert(! en::detail::is_arithmetic_allowed<t_bit>::value, "");
    static_assert(! en::detail::is_mixed_arithmetic_allowed<t_bit>::value, "");
    
    static_assert(! en::allow_logical_operators<t_bit>::value, "");
    static_assert(! en::allow_mixed_logical_operators<t_bit>::value, "");
    static_assert(! en::detail::is_logical_allowed<t_bit>::value, "");
    static_assert(! en::detail::is_mixed_logical_allowed<t_bit>::value, "");
    
    static_assert(en::allow_bitwise_operators<t_bit>::value, "");
    static_assert(! en::allow_mixed_bitwise_operators<t_bit>::value, "");
    static_assert(en::detail::is_bitwise_allowed<t_bit>::value, "");
    static_assert(! en::detail::is_mixed_bitwise_allowed<t_bit>::value, "");
    
    
//
// t_bit_m
//
    
    static_assert(! en::allow_arithmetic_operators<t_bit_m>::value, "");
    static_assert(! en::allow_mixed_arithmetic_operators<t_bit_m>::value, "");
    static_assert(! en::detail::is_arithmetic_allowed<t_bit_m>::value, "");
    static_assert(! en::detail::is_mixed_arithmetic_allowed<t_bit_m>::value, "");
    
    static_assert(! en::allow_logical_operators<t_bit_m>::value, "");
    static_assert(! en::allow_mixed_logical_operators<t_bit_m>::value, "");
    static_assert(! en::detail::is_logical_allowed<t_bit_m>::value, "");
    static_assert(! en::detail::is_mixed_logical_allowed<t_bit_m>::value, "");
    
    static_assert(! en::allow_bitwise_operators<t_bit_m>::value, "");
    static_assert(en::allow_mixed_bitwise_operators<t_bit_m>::value, "");
    static_assert(en::detail::is_bitwise_allowed<t_bit_m>::value, "");
    static_assert(en::detail::is_mixed_bitwise_allowed<t_bit_m>::value, "");
    
    t_bit_m lhs_e, rhs_e, ret, mret1, mret2, lhs_ret, mlhs_ret;
    int lhs, rhs, expect;
    
    for (int i=0; i <= 10; ++i) {
        lhs = i;
        lhs_e = static_cast<t_bit_m>(lhs);
        expect = ~lhs;
        ret = ~lhs_e;
        BOOST_CHECK(en::base_enum_cast(ret) == expect);
    }
    
    for (int i=0; i <=10; ++i) {
        for (int j=0; j <= 10; ++j) {
            lhs = i;
            rhs = j;
            lhs_e = static_cast<t_bit_m>(lhs);
            rhs_e = static_cast<t_bit_m>(rhs);
            
            expect = lhs & rhs;
            ret = lhs_e & rhs_e;
            mret1 = lhs_e & rhs;
            mret2 = lhs & rhs_e;
            lhs_ret = lhs_e;
            lhs_ret &= rhs_e;
            mlhs_ret = lhs_e;
            mlhs_ret &= rhs;
            BOOST_CHECK(en::base_enum_cast(ret) == expect);
            BOOST_CHECK(en::base_enum_cast(mret1) == expect);
            BOOST_CHECK(en::base_enum_cast(mret2) == expect);
            BOOST_CHECK(en::base_enum_cast(lhs_ret) == expect);
            BOOST_CHECK(en::base_enum_cast(mlhs_ret) == expect);
            
            expect = lhs | rhs;
            ret = lhs_e | rhs_e;
            mret1 = lhs_e | rhs;
            mret2 = lhs | rhs_e;
            lhs_ret = lhs_e;
            lhs_ret |= rhs_e;
            mlhs_ret = lhs_e;
            mlhs_ret |= rhs;
            BOOST_CHECK(en::base_enum_cast(ret) == expect);
            BOOST_CHECK(en::base_enum_cast(mret1) == expect);
            BOOST_CHECK(en::base_enum_cast(mret2) == expect);
            BOOST_CHECK(en::base_enum_cast(lhs_ret) == expect);
            BOOST_CHECK(en::base_enum_cast(mlhs_ret) == expect);
            
            expect = lhs ^ rhs;
            ret = lhs_e ^ rhs_e;
            mret1 = lhs_e ^ rhs;
            mret2 = lhs ^ rhs_e;
            lhs_ret = lhs_e;
            lhs_ret ^= rhs_e;
            mlhs_ret = lhs_e;
            mlhs_ret ^= rhs;
            BOOST_CHECK(en::base_enum_cast(ret) == expect);
            BOOST_CHECK(en::base_enum_cast(mret1) == expect);
            BOOST_CHECK(en::base_enum_cast(mret2) == expect);
            BOOST_CHECK(en::base_enum_cast(lhs_ret) == expect);
            BOOST_CHECK(en::base_enum_cast(mlhs_ret) == expect);
            
        }
    }
    
    
}

BOOST_AUTO_TEST_SUITE_END()