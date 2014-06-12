#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE Main
#include <boost/test/unit_test.hpp>

#include <elib/enumeration/cast.hpp>
#include <elib/enumeration/operators.hpp>

namespace 
{    
    enum class Bitmask
    {
        none, one, two, three
    };
    
    ELIB_ENUMERATION_UNARY_OP(Bitmask, Bitmask, ~)
    ELIB_ENUMERATION_BINARY_OP(Bitmask, Bitmask, Bitmask, &)
    ELIB_ENUMERATION_BINARY_OP(Bitmask, Bitmask, Bitmask, |)
    ELIB_ENUMERATION_BINARY_OP(Bitmask, Bitmask, Bitmask, ^)
    ELIB_ENUMERATION_COMPOUND_OP(Bitmask, Bitmask, &)
    ELIB_ENUMERATION_COMPOUND_OP(Bitmask, Bitmask, |)
    ELIB_ENUMERATION_COMPOUND_OP(Bitmask, Bitmask, ^)
    
    enum class Arith
    {
        none, one, two, three
    };
    
    ELIB_ENUMERATION_PREFIX_OP(Arith, +)
    ELIB_ENUMERATION_SUFFIX_OP(Arith, +)
    ELIB_ENUMERATION_PREFIX_OP(Arith, -)
    ELIB_ENUMERATION_SUFFIX_OP(Arith, -)
    ELIB_ENUMERATION_UNARY_OP(Arith, Arith, +)
    ELIB_ENUMERATION_UNARY_OP(Arith, Arith, -)
    ELIB_ENUMERATION_BINARY_OP(Arith, Arith, Arith, +)
    ELIB_ENUMERATION_BINARY_OP(Arith, Arith, Arith, -)
    ELIB_ENUMERATION_BINARY_OP(Arith, Arith, Arith, *)
    ELIB_ENUMERATION_BINARY_OP(Arith, Arith, Arith, /)
    ELIB_ENUMERATION_BINARY_OP(Arith, Arith, Arith, %)
    ELIB_ENUMERATION_COMPOUND_OP(Arith, Arith, +)
    ELIB_ENUMERATION_COMPOUND_OP(Arith, Arith, -)
    ELIB_ENUMERATION_COMPOUND_OP(Arith, Arith, *)
    ELIB_ENUMERATION_COMPOUND_OP(Arith, Arith, /)
    ELIB_ENUMERATION_COMPOUND_OP(Arith, Arith, %)
    
    enum class Logic
    {
        none, one, two, three
    };
    
    ELIB_ENUMERATION_UNARY_OP(bool, Logic, !)
    ELIB_ENUMERATION_BINARY_OP(bool, Logic, int, ==)
    ELIB_ENUMERATION_BINARY_OP(bool, int, Logic, ==)
    ELIB_ENUMERATION_BINARY_OP(bool, Logic, int, !=)
    ELIB_ENUMERATION_BINARY_OP(bool, int, Logic, !=)
    ELIB_ENUMERATION_BINARY_OP(bool, Logic, int, <)
    ELIB_ENUMERATION_BINARY_OP(bool, int, Logic, <)
    ELIB_ENUMERATION_BINARY_OP(bool, Logic, int, >)
    ELIB_ENUMERATION_BINARY_OP(bool, int, Logic, >)
    ELIB_ENUMERATION_BINARY_OP(bool, Logic, int, <=)
    ELIB_ENUMERATION_BINARY_OP(bool, int, Logic, <=)
    ELIB_ENUMERATION_BINARY_OP(bool, Logic, int, >=)
    ELIB_ENUMERATION_BINARY_OP(bool, int, Logic, >=)
}                                                           // namespace

using elib::enumeration::underlying_cast;

BOOST_AUTO_TEST_SUITE(enumeration_operators_test_suite)

BOOST_AUTO_TEST_CASE(bitmask_test)
{
    // operator ~
    {
        BOOST_CHECK(~Bitmask::none == static_cast<Bitmask>(~0));
        BOOST_CHECK(~Bitmask::one == static_cast<Bitmask>(~1));
    }
    // operator &
    {
        BOOST_CHECK((Bitmask::none & Bitmask::none) == Bitmask::none);
        BOOST_CHECK((Bitmask::one & Bitmask::one) == Bitmask::one);
        BOOST_CHECK((Bitmask::three & Bitmask::two) == Bitmask::two);
    }
    // operator |
    {
        BOOST_CHECK((Bitmask::none | Bitmask::none) == Bitmask::none);
        BOOST_CHECK((Bitmask::one | Bitmask::one) == Bitmask::one);
        BOOST_CHECK((Bitmask::none | Bitmask::one) == Bitmask::one);
        BOOST_CHECK((Bitmask::none | Bitmask::one | Bitmask::two) == Bitmask::three);
    }
    // operator ^
    {
        BOOST_CHECK((Bitmask::none ^ Bitmask::none) == Bitmask::none);
        BOOST_CHECK((Bitmask::one ^ Bitmask::none) == Bitmask::one);
        BOOST_CHECK((Bitmask::one ^ Bitmask::two) == Bitmask::three);
        BOOST_CHECK((Bitmask::three ^ Bitmask::one) == Bitmask::two);
    }
    // operator &=
    {
        Bitmask b(Bitmask::none);
        b &= Bitmask::none;
        BOOST_CHECK(b == Bitmask::none);
        b &= Bitmask::one;
        BOOST_CHECK(b == Bitmask::none);
        b = Bitmask::one;
        b &= Bitmask::three;
        BOOST_CHECK(b == Bitmask::one);
    }
    // operator |=
    {
        Bitmask b(Bitmask::none);
        b |= Bitmask::none;
        BOOST_CHECK(b == Bitmask::none);
        b |= Bitmask::one;
        BOOST_CHECK(b == Bitmask::one);
        b |= Bitmask::two;
        BOOST_CHECK(b == Bitmask::three);
    }
    // operator ^=
    {
        Bitmask b(Bitmask::none);
        b ^= Bitmask::none;
        BOOST_CHECK(b == Bitmask::none);
        b ^= Bitmask::one;
        BOOST_CHECK(b == Bitmask::one);
        b ^= Bitmask::two;
        BOOST_CHECK(b == Bitmask::three);
        b ^= Bitmask::three;
        BOOST_CHECK(b == Bitmask::none);
    }
}

BOOST_AUTO_TEST_CASE(arithmetic_test)
{
    // prefix increment
    {
        Arith a(Arith::none);
        ++a;
        BOOST_CHECK(a == Arith::one);
    }
    // postfix increment
    {
        Arith a(Arith::none);
        Arith cp = a++;
        BOOST_CHECK(cp == Arith::none);
        BOOST_CHECK(a == Arith::one);
    }
    // prefix decrement
    {
        Arith a(Arith::two);
        --a;
        BOOST_CHECK(a == Arith::one);
    }
    // postfix decrement
    {
        Arith a(Arith::two);
        Arith cp = a--;
        BOOST_CHECK(cp == Arith::two);
        BOOST_CHECK(a == Arith::one);
    }
    // unary plus
    {
        Arith a(Arith::one);
        BOOST_CHECK( +a == a );
    }
    // unary minus
    {
        Arith a(Arith::one);
        BOOST_CHECK(underlying_cast(-a) == -1);
    }
    // binary plus
    {
        BOOST_CHECK((Arith::none + Arith::none) == Arith::none);
        BOOST_CHECK((Arith::none + Arith::one) == Arith::one);
        BOOST_CHECK((Arith::one + Arith::two) == Arith::three);
    }
    // binary minus
    {
        BOOST_CHECK((Arith::none - Arith::none) == Arith::none);
        BOOST_CHECK((Arith::one - Arith::none) == Arith::one);
        BOOST_CHECK((Arith::three - Arith::two) == Arith::one);
        BOOST_CHECK((Arith::two - Arith::three) == static_cast<Arith>(-1));
    }
    // multiple
    {
        BOOST_CHECK((Arith::none * Arith::none) == Arith::none);
        BOOST_CHECK((Arith::none * Arith::one) == Arith::none);
        BOOST_CHECK((Arith::one * Arith::two) == Arith::two);
        BOOST_CHECK((Arith::two * Arith::three) == static_cast<Arith>(6));
    }
    // divide
    {
        BOOST_CHECK((Arith::none / Arith::one) == Arith::none);
        BOOST_CHECK((Arith::one / Arith::one) == Arith::one);
        BOOST_CHECK((Arith::two / Arith::one) == Arith::two);
        BOOST_CHECK((static_cast<Arith>(4) / Arith::two) == Arith::two);
    }
    // mod
    {
        BOOST_CHECK((Arith::none % Arith::one) == Arith::none);
        BOOST_CHECK((Arith::one % Arith::one) == Arith::none);
        BOOST_CHECK((Arith::two % Arith::one) == Arith::none);
        BOOST_CHECK((Arith::three % Arith::two) == Arith::one);
    }
    // compound add
    {
        Arith a(Arith::none);
        a += Arith::none;
        BOOST_CHECK(a == Arith::none);
        a += Arith::one;
        BOOST_CHECK(a == Arith::one);
        a += Arith::two;
        BOOST_CHECK(a == Arith::three);
    }
    // compound subtract
    {
        Arith a(Arith::three);
        a -= Arith::none;
        BOOST_CHECK(a == Arith::three);
        a -= Arith::one;
        BOOST_CHECK(a == Arith::two);
        a -= Arith::two;
        BOOST_CHECK(a == Arith::none);
        a -= Arith::one;
        BOOST_CHECK(a == static_cast<Arith>(-1));
    }
    // compound multiple
    {
        Arith a(Arith::none);
        a *= Arith::none;
        BOOST_CHECK(a == Arith::none);
        a *= Arith::one;
        BOOST_CHECK(a == Arith::none);
        a = Arith::one;
        a *= Arith::one;
        BOOST_CHECK(a == Arith::one);
        a *= Arith::two;
        BOOST_CHECK(a == Arith::two);
        a *= Arith::two;
        BOOST_CHECK(a == static_cast<Arith>(4));
    }
    // compound divide
    {
        Arith a(Arith::none);
        a /= Arith::one;
        BOOST_CHECK(a == Arith::none);
        a = Arith::two;
        a /= Arith::one;
        BOOST_CHECK(a == Arith::two);
        a /= Arith::two;
        BOOST_CHECK(a == Arith::one);
    }
    // compound mod
    {
        Arith a(Arith::none);
        a %= Arith::one;
        BOOST_CHECK(a == Arith::none);
        a = Arith::three;
        a %= Arith::two;
        BOOST_CHECK(a == Arith::one);
    }
}

BOOST_AUTO_TEST_CASE(logical_test)
{
    // operator !
    {
        BOOST_CHECK(! Logic::none);
        BOOST_CHECK(not (!Logic::one));
    }
    // equal
    {
        BOOST_CHECK(Logic::one == 1);
        BOOST_CHECK(0 == Logic::none);
        BOOST_CHECK(not (Logic::one == 2));
        BOOST_CHECK(not (1 == Logic::none));
    }
    // not equal
    {
        BOOST_CHECK(Logic::none != 2);
        BOOST_CHECK(1 != Logic::two);
        BOOST_CHECK(not (Logic::one != 1));
        BOOST_CHECK(not (0 != Logic::none));
    }
    // less than
    {
        BOOST_CHECK(Logic::none < 1);
        BOOST_CHECK(1 < Logic::two);
        BOOST_CHECK(not (Logic::one < 1));
        BOOST_CHECK(not (1 < Logic::none));
    }
    // greater than
    {
        BOOST_CHECK(Logic::two > 1);
        BOOST_CHECK(1 > Logic::none);
        BOOST_CHECK(not (Logic::none > 0));
        BOOST_CHECK(not (1 > Logic::two));
    }
    // less equal
    {
        BOOST_CHECK(Logic::two <= 3);
        BOOST_CHECK(Logic::two <= 2);
        BOOST_CHECK(0 <= Logic::one);
        BOOST_CHECK(0 <= Logic::none);
        BOOST_CHECK(not (Logic::three <= 2));
        BOOST_CHECK(not (1 <= Logic::none));
    }
    // greater equal
    {
        BOOST_CHECK(Logic::one >= 0);
        BOOST_CHECK(Logic::one >= 1);
        BOOST_CHECK(2 >= Logic::none);
        BOOST_CHECK(2 >= Logic::two);
        BOOST_CHECK(not (Logic::one >= 2));
        BOOST_CHECK(not (1 >= Logic::two));
    }
    
}

BOOST_AUTO_TEST_SUITE_END()