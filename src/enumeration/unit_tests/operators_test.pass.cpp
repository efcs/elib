// REQUIRES: ELIB_ENUMERATION_SOURCE
#include <elib/enumeration/cast.hpp>
#include <elib/enumeration/operators.hpp>
#include "test/helper.hpp"

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

TEST_CASE(enumeration_operators_test_suite)
{
        
    // bitmask_test)
    {
        // operator ~
        {
            TEST_ASSERT(~Bitmask::none == static_cast<Bitmask>(~0));
            TEST_ASSERT(~Bitmask::one == static_cast<Bitmask>(~1));
        }
        // operator &
        {
            TEST_ASSERT((Bitmask::none & Bitmask::none) == Bitmask::none);
            TEST_ASSERT((Bitmask::one & Bitmask::one) == Bitmask::one);
            TEST_ASSERT((Bitmask::three & Bitmask::two) == Bitmask::two);
        }
        // operator |
        {
            TEST_ASSERT((Bitmask::none | Bitmask::none) == Bitmask::none);
            TEST_ASSERT((Bitmask::one | Bitmask::one) == Bitmask::one);
            TEST_ASSERT((Bitmask::none | Bitmask::one) == Bitmask::one);
            TEST_ASSERT((Bitmask::none | Bitmask::one | Bitmask::two) == Bitmask::three);
        }
        // operator ^
        {
            TEST_ASSERT((Bitmask::none ^ Bitmask::none) == Bitmask::none);
            TEST_ASSERT((Bitmask::one ^ Bitmask::none) == Bitmask::one);
            TEST_ASSERT((Bitmask::one ^ Bitmask::two) == Bitmask::three);
            TEST_ASSERT((Bitmask::three ^ Bitmask::one) == Bitmask::two);
        }
        // operator &=
        {
            Bitmask b(Bitmask::none);
            b &= Bitmask::none;
            TEST_ASSERT(b == Bitmask::none);
            b &= Bitmask::one;
            TEST_ASSERT(b == Bitmask::none);
            b = Bitmask::one;
            b &= Bitmask::three;
            TEST_ASSERT(b == Bitmask::one);
        }
        // operator |=
        {
            Bitmask b(Bitmask::none);
            b |= Bitmask::none;
            TEST_ASSERT(b == Bitmask::none);
            b |= Bitmask::one;
            TEST_ASSERT(b == Bitmask::one);
            b |= Bitmask::two;
            TEST_ASSERT(b == Bitmask::three);
        }
        // operator ^=
        {
            Bitmask b(Bitmask::none);
            b ^= Bitmask::none;
            TEST_ASSERT(b == Bitmask::none);
            b ^= Bitmask::one;
            TEST_ASSERT(b == Bitmask::one);
            b ^= Bitmask::two;
            TEST_ASSERT(b == Bitmask::three);
            b ^= Bitmask::three;
            TEST_ASSERT(b == Bitmask::none);
        }
    }

    // arithmetic_test)
    {
        // prefix increment
        {
            Arith a(Arith::none);
            ++a;
            TEST_ASSERT(a == Arith::one);
        }
        // postfix increment
        {
            Arith a(Arith::none);
            Arith cp = a++;
            TEST_ASSERT(cp == Arith::none);
            TEST_ASSERT(a == Arith::one);
        }
        // prefix decrement
        {
            Arith a(Arith::two);
            --a;
            TEST_ASSERT(a == Arith::one);
        }
        // postfix decrement
        {
            Arith a(Arith::two);
            Arith cp = a--;
            TEST_ASSERT(cp == Arith::two);
            TEST_ASSERT(a == Arith::one);
        }
        // unary plus
        {
            Arith a(Arith::one);
            TEST_ASSERT( +a == a );
        }
        // unary minus
        {
            Arith a(Arith::one);
            TEST_ASSERT(underlying_cast(-a) == -1);
        }
        // binary plus
        {
            TEST_ASSERT((Arith::none + Arith::none) == Arith::none);
            TEST_ASSERT((Arith::none + Arith::one) == Arith::one);
            TEST_ASSERT((Arith::one + Arith::two) == Arith::three);
        }
        // binary minus
        {
            TEST_ASSERT((Arith::none - Arith::none) == Arith::none);
            TEST_ASSERT((Arith::one - Arith::none) == Arith::one);
            TEST_ASSERT((Arith::three - Arith::two) == Arith::one);
            TEST_ASSERT((Arith::two - Arith::three) == static_cast<Arith>(-1));
        }
        // multiple
        {
            TEST_ASSERT((Arith::none * Arith::none) == Arith::none);
            TEST_ASSERT((Arith::none * Arith::one) == Arith::none);
            TEST_ASSERT((Arith::one * Arith::two) == Arith::two);
            TEST_ASSERT((Arith::two * Arith::three) == static_cast<Arith>(6));
        }
        // divide
        {
            TEST_ASSERT((Arith::none / Arith::one) == Arith::none);
            TEST_ASSERT((Arith::one / Arith::one) == Arith::one);
            TEST_ASSERT((Arith::two / Arith::one) == Arith::two);
            TEST_ASSERT((static_cast<Arith>(4) / Arith::two) == Arith::two);
        }
        // mod
        {
            TEST_ASSERT((Arith::none % Arith::one) == Arith::none);
            TEST_ASSERT((Arith::one % Arith::one) == Arith::none);
            TEST_ASSERT((Arith::two % Arith::one) == Arith::none);
            TEST_ASSERT((Arith::three % Arith::two) == Arith::one);
        }
        // compound add
        {
            Arith a(Arith::none);
            a += Arith::none;
            TEST_ASSERT(a == Arith::none);
            a += Arith::one;
            TEST_ASSERT(a == Arith::one);
            a += Arith::two;
            TEST_ASSERT(a == Arith::three);
        }
        // compound subtract
        {
            Arith a(Arith::three);
            a -= Arith::none;
            TEST_ASSERT(a == Arith::three);
            a -= Arith::one;
            TEST_ASSERT(a == Arith::two);
            a -= Arith::two;
            TEST_ASSERT(a == Arith::none);
            a -= Arith::one;
            TEST_ASSERT(a == static_cast<Arith>(-1));
        }
        // compound multiple
        {
            Arith a(Arith::none);
            a *= Arith::none;
            TEST_ASSERT(a == Arith::none);
            a *= Arith::one;
            TEST_ASSERT(a == Arith::none);
            a = Arith::one;
            a *= Arith::one;
            TEST_ASSERT(a == Arith::one);
            a *= Arith::two;
            TEST_ASSERT(a == Arith::two);
            a *= Arith::two;
            TEST_ASSERT(a == static_cast<Arith>(4));
        }
        // compound divide
        {
            Arith a(Arith::none);
            a /= Arith::one;
            TEST_ASSERT(a == Arith::none);
            a = Arith::two;
            a /= Arith::one;
            TEST_ASSERT(a == Arith::two);
            a /= Arith::two;
            TEST_ASSERT(a == Arith::one);
        }
        // compound mod
        {
            Arith a(Arith::none);
            a %= Arith::one;
            TEST_ASSERT(a == Arith::none);
            a = Arith::three;
            a %= Arith::two;
            TEST_ASSERT(a == Arith::one);
        }
    }

    // logical_test)
    {
        // operator !
        {
            TEST_ASSERT(! Logic::none);
            TEST_ASSERT(not (!Logic::one));
        }
        // equal
        {
            TEST_ASSERT(Logic::one == 1);
            TEST_ASSERT(0 == Logic::none);
            TEST_ASSERT(not (Logic::one == 2));
            TEST_ASSERT(not (1 == Logic::none));
        }
        // not equal
        {
            TEST_ASSERT(Logic::none != 2);
            TEST_ASSERT(1 != Logic::two);
            TEST_ASSERT(not (Logic::one != 1));
            TEST_ASSERT(not (0 != Logic::none));
        }
        // less than
        {
            TEST_ASSERT(Logic::none < 1);
            TEST_ASSERT(1 < Logic::two);
            TEST_ASSERT(not (Logic::one < 1));
            TEST_ASSERT(not (1 < Logic::none));
        }
        // greater than
        {
            TEST_ASSERT(Logic::two > 1);
            TEST_ASSERT(1 > Logic::none);
            TEST_ASSERT(not (Logic::none > 0));
            TEST_ASSERT(not (1 > Logic::two));
        }
        // less equal
        {
            TEST_ASSERT(Logic::two <= 3);
            TEST_ASSERT(Logic::two <= 2);
            TEST_ASSERT(0 <= Logic::one);
            TEST_ASSERT(0 <= Logic::none);
            TEST_ASSERT(not (Logic::three <= 2));
            TEST_ASSERT(not (1 <= Logic::none));
        }
        // greater equal
        {
            TEST_ASSERT(Logic::one >= 0);
            TEST_ASSERT(Logic::one >= 1);
            TEST_ASSERT(2 >= Logic::none);
            TEST_ASSERT(2 >= Logic::two);
            TEST_ASSERT(not (Logic::one >= 2));
            TEST_ASSERT(not (1 >= Logic::two));
        }
        
    }
}