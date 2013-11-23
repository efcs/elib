#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

// get helper definitions
#include "mp_test_config.hpp"
#include <elib/mp/arithmetic.hpp>

#if ELIB_MP_BOOST_MPL_TESTS
# include <boost/mpl/arithmetic.hpp>
# endif                                              // ELIB_MP_BOOST_MPL_TESTS

#include <elib/pragma.hpp>

#include <type_traits>
#include <limits>




/* 
 * NOTE: most test cases are in add_test
 *  including test cases dealing with mixed arithmetic
 *  The other functions are tested minimally 
 * 
 * NOTE: elib and boost handle arithmetic operations very differently
 * so it is not possible to test against boost
 */
BOOST_AUTO_TEST_SUITE(mp_arithmetic_test_suite)

// Turn off C++11 narrowing error for clang
// since we want to actually test narrowing conversions
ELIB_PRAGMA_IGNORE_CXX11_NARROWING()

//-------------------------------- negate --------------------------------// 

  BOOST_AUTO_TEST_CASE(negate_test)
  {
    // bool
    {
      CHECK_INTC(e::negate<true_>, int, -1);
      CHECK_INTC(e::negate<false_>, int, 0);
    }
    // char
    {
      CHECK_INTC(e::negate<min_char_>
        , decltype(-min_char_::value)
        , -min_char_::value
      );
    
      CHECK_INTC(e::negate<max_char_>
        , decltype(- max_char_::value )
        , -max_char_::value
      );
    }
    // int
    {
      SAME_INTC(e::negate<INT(0)>, INT(0));
      SAME_INTC(e::negate<INT(1)>, INT(-1));
      SAME_INTC(e::negate<INT(-1)>, INT(1));
      SAME_INTC(e::negate<INT(10)>, INT(-10));
      
      CHECK_INTC(e::negate<max_int_>, int, (-max_int_::value));
      // We cannot check min_int_ since -min_int_::value is not a 
      // constant expression
    }
    // unsigned
    {
      SAME_INTC(e::negate<UINT(0)>, UINT(0));
      SAME_INTC(e::negate<UINT(1)>, UINT(-1));
      SAME_INTC(e::negate<UINT(-1)>, UINT(1));
      
      CHECK_INTC(e::negate<max_uint_>, uint, (-max_uint_::value));
      CHECK_INTC(e::negate<min_uint_>, uint, (-min_uint_::value));
    }
    // long
    {
      CHECK_INTC(e::negate<max_long_>, long, -max_long_::value);
      // cannot check min_long_ see note above
    }
  }                                                           // negate_test

//-------------------------------- add --------------------------------// 
  
  BOOST_AUTO_TEST_CASE(add_test)
  {
    using e::add;
  // NON-MIXED //
    //bool
    {      
      using E1 = add<false_, false_>;
      SAME_INTC(E1, INT(0));
      
      using E2 = add<true_, false_>;
      SAME_INTC(E2, INT(1));
      
      using E3 = add<true_, true_>;
      SAME_INTC(E3, INT(2));
      
      using E4 = add<true_, true_, true_, true_, true_
        , false_, false_, false_, false_, false_
        , true_, true_, true_, true_, true_
      >;
      SAME_INTC(E4, INT(10));
    }
    // int
    {
      using E1 = add<INT(0), INT(0)>;
      SAME_INTC(E1, INT(0));
      
      using E2 = add<INT(0), INT(1)>;
      SAME_INTC(E2, INT(1));
      
      using E3 = add<INT(500), INT(500)>;
      SAME_INTC(E3, INT(1000));
      
    // check negative numbers
      using E4 = add<INT(-1), INT(-1)>;
      SAME_INTC(E4, INT(-2));
      
      using E5 = add<INT(-1), INT(1)>;
      SAME_INTC(E5, INT(0));
    }
    // uint
    {
      using E1 = add<UINT(0), UINT(0)>;
      SAME_INTC(E1, UINT(0));
      
      using E2 = add<UINT(1), UINT(1)>;
      SAME_INTC(E2, UINT(2));
      
      using E3 = add<UINT(-1), UINT(0)>;
      SAME_INTC(E3, UINT(((uint)-1) + ((uint)0)));
      
      using E4 = add<UINT(-1), UINT(-1)>;
      SAME_INTC(E4, UINT(((uint)-1) + ((uint)-1)));
    }
  // MIXED //
    // bool - int
    {
      using E1 = add<false_, INT(1)>;
      SAME_INTC(E1, INT(1));
      
      using E2 = add<true_, INT(0)>;
      SAME_INTC(E2, INT(1));
      
      using E3 = add<INT(0), false_>;
      SAME_INTC(E3, INT(0));
    }
    // unsigned - int
    {
      using E1 = add<INT(0), UINT(0)>;
      SAME_INTC(E1, UINT(0));
      
      using E2 = add<INT(-1), UINT(1)>;
      SAME_INTC(E2, UINT(0));
      
      using E3 = add<UINT(1), INT(1)>;
      SAME_INTC(E3, UINT(2));
      
      using E4 = add<INT(-1), INT(-1), INT(-1), INT(-1), INT(-1)
                    , UINT(1), UINT(1), UINT(1), UINT(1), UINT(1)
                    , INT(-1), INT(-1), INT(-1), INT(-1), INT(-1)
                  >;
      SAME_INTC(E4, UINT(-5));
    }
    // int - long
    {
      using E1 = add<INT(0), LONG(0)>;
      SAME_INTC(E1, LONG(0));
      
      using E2 = add<LONG(0), INT(0)>;
      SAME_INTC(E2, E1);
      
      using E3 = add<INT(100), LONG(-100)>;
      SAME_INTC(E3, LONG(0));
      
      using E4 = add<LONG(-10), INT(20)>;
      SAME_INTC(E4, LONG(10));
    }
  }                                                         // add_test
  
//-------------------------------- subtract --------------------------------// 
  BOOST_AUTO_TEST_CASE(subtract_test)
  {
    using e::subtract;
    // NON-MIXED //
    // bool/bool
    {
      using E1 = subtract<false_, false_>;
      SAME_INTC(E1, INT(0));
      
      using E2 = subtract<INT(1), INT(0)>;
      SAME_INTC(E2, INT(1));
      
      using E3 = subtract<INT(0), INT(1)>;
      SAME_INTC(E3, INT(-1));
      
      // test associativity
      using E4 = subtract<INT(0), INT(1), INT(2)>;
      SAME_INTC(E4, INT(0-1-2));
      
      using E5 = subtract<INT(0), INT(1), INT(2), INT(3)>;
      SAME_INTC(E5, INT(0-1-2-3));
      
      using E6 = subtract<INT(0), INT(1), INT(2), INT(3), INT(4)>;
      SAME_INTC(E6, INT(0-1-2-3-4));
      
      using E7 = subtract<INT(0), INT(1), INT(2), INT(3), INT(4), INT(5)>;
      SAME_INTC(E7, INT(0-1-2-3-4-5));
      
      using E8 = subtract<INT(0), INT(1), INT(2), INT(3), INT(4), INT(5)
                        , INT(6)>;
      SAME_INTC(E8, INT(0-1-2-3-4-5-6));
      
      using E9 = subtract<INT(0), INT(1), INT(2), INT(3), INT(4), INT(5)
                        , INT(6), INT(7)>;
      SAME_INTC(E9, INT(0-1-2-3-4-5-6-7));
      
      using E10 = subtract<INT(5), INT(4), INT(3), INT(2), INT(1)>;
      SAME_INTC(E10, INT(5-4-3-2-1));
    }
    // unsigned
    {
      using E1 = subtract<UINT(0), UINT(0)>;
      SAME_INTC(E1, UINT(0));
      
      using E2 = subtract<UINT(0), UINT(1)>;
      SAME_INTC(E2, UINT(-1));
      
      using E3 = subtract<UINT(2), UINT(1)>;
      SAME_INTC(E3, UINT(1));
    }
    // no tests for long
  // MIXED //
    {
      using E1 = subtract<false_, INT(1)>;
      SAME_INTC(E1, INT(-1));
      
      using E2 = subtract<true_, INT(0)>;
      SAME_INTC(E2, INT(1));
      
      using E3 = subtract<CHAR(1), INT(2)>;
      SAME_INTC(E3, INT(-1));
      
      using E4 = subtract<INT(10), CHAR(5)>;
      SAME_INTC(E4, INT(5));
      
      using E5 = subtract<CHAR(5), LONG(10)>;
      SAME_INTC(E5, LONG(-5));
      
      using E6 = subtract<LONG(0), CHAR(1)>;
      SAME_INTC(E6, LONG(-1));
      
      using E7 = subtract<false_, CHAR(1), INT(2), LONG(3)>;
      SAME_INTC(E7, LONG(0-1-2-3));
      
      using E8 = subtract<LONG(0), INT(1), CHAR(2), true_>;
      SAME_INTC(E8, LONG(0-1-2-1));
      
      using E9 = subtract<LONG(4), INT(3), CHAR(2), true_>;
      SAME_INTC(E9, LONG(4-3-2-1));
    }
  }                                                         // subtract_test
  
//-------------------------------- multiply --------------------------------// 
  BOOST_AUTO_TEST_CASE(multiply_test)
  {
    using e::multiply;
    // NON-MIXED //
    {
      using E1 = multiply<false_, false_>;
      SAME_INTC(E1, INT(0));
      
      using E2 = multiply<CHAR(1), CHAR(0)>;
      SAME_INTC(E2, INT(0));
      
      using E3 = multiply<INT(1), INT(0)>;
      SAME_INTC(E3, INT(0));
      
      using E4 = multiply<UINT(1), UINT(2)>;
      SAME_INTC(E4, UINT(2));
      
      using E5 = multiply<LONG(100), LONG(-10)>;
      SAME_INTC(E5, LONG(-1000));
      
      using E6 = multiply<INT(2), INT(1), INT(5), INT(10000), INT(-10)
                          , INT(0)>;
      SAME_INTC(E6, INT(0));
    }
    // MIXED //
    {
      using E1 = multiply<false_, CHAR(1), INT(100)>;
      SAME_INTC(E1, INT(0));
      
      using E2 = multiply<true_, UINT(10)>;
      SAME_INTC(E2, UINT(10));
      
      using E3 = multiply<true_, CHAR(2), INT(3), UINT(4)>;
      SAME_INTC(E3, UINT(24));
      
      using E4 = multiply<true_, CHAR(2), INT(-3), UINT(4)>;
      SAME_INTC(E4, UINT(-24));
    }
  }                                                         // multiply_test
  
//-------------------------------- divide -----------------------------------// 

  BOOST_AUTO_TEST_CASE(divide_test)
  {
    using e::divide;
    // NON-MIXED //
    {
      using E1 = divide<false_, true_>;
      SAME_INTC(E1, INT(0));
      
      using E2 = divide<CHAR(1), CHAR(1)>;
      SAME_INTC(E2, INT(1));
      
      using E3 = divide<INT(10), INT(5)>;
      SAME_INTC(E3, INT(2));
      
      using E4 = divide<INT(2), INT(-1)>;
      SAME_INTC(E4, INT(-2));
      
      using E5 = divide<UINT(3), UINT(2)>;
      SAME_INTC(E5, UINT(1));
      
      using E6 = divide<LONG(5*4*3), LONG(5), LONG(4)>;
      SAME_INTC(E6, LONG(3));
      
      using E7 = divide<LONG(6*5*4*3), LONG(6), LONG(5), LONG(4)>;
      SAME_INTC(E7, LONG(3));
      
      using E8 = divide<LONG(7*6*5*4*3), LONG(6), LONG(7), LONG(5), LONG(4)>;
      SAME_INTC(E8, LONG(3));
    }
    // MIXED //
    {
      using E1 = divide<false_, CHAR(1)>;
      SAME_INTC(E1, INT(0));
      
      using E2 = divide<true_, CHAR(1), INT(1), LONG(1)>;
      SAME_INTC(E2, LONG(1));
    }
  }                                                           // divide_test
  
//-------------------------------- modulus --------------------------------// 
  BOOST_AUTO_TEST_CASE(modulus_test)
  {
    using e::modulus;
    // NON-MIXED //
    {
      using E1 = modulus<false_, true_>;
      SAME_INTC(E1, INT(0));
      
      using E2 = modulus<CHAR(1), CHAR(1)>;
      SAME_INTC(E2, INT(0));
      
      using E3 = modulus<INT(10), INT(3)>;
      SAME_INTC(E3, INT(1));
      
      using E4 = modulus<UINT(6), UINT(4)>;
      SAME_INTC(E4, UINT(2));
      
      using E5 = modulus<LONG(100), LONG(1000)>;
      SAME_INTC(E5, LONG(100));
      
      using E6 = modulus<INT(-10), INT(3)>;
      SAME_INTC(E6, INT(-1));
      
      using E7 = modulus<LONG(10), LONG(-3)>;
      SAME_INTC(E7, LONG(1));
    }
    // MIXED //
    {
      using E1 = modulus<INT(10), true_>;
      SAME_INTC(E1, INT(0));
      
      using E2 = modulus<UINT(8), CHAR(3)>;
      SAME_INTC(E2, UINT(2));
      
      using E3 = modulus<LONG(10), INT(3)>;
      SAME_INTC(E3, LONG(1));
      
      using E4 = modulus<INT(-5), UINT(2)>;
      SAME_INTC(E4, UINT(1));
    }
  }                                                         // modulus_test
  
BOOST_AUTO_TEST_SUITE_END()