#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include "mp_test_config.hpp"
#include <elib/mp/metafunctions.hpp>

#if ELIB_MP_BOOST_MLP_TESTS
# // type selection
# include <boost/mpl/if.hpp>
# include <boost/mpl/eval_if.hpp>
# //invoke
# include <boost/mpl/apply.hpp>
# include <boost/mpl/apply_wrap.hpp>
# include <boost/mpl/unpack_args.hpp> 
# // composition & arguments
# include <boost/mpl/placeholders.hpp>
# include <boost/mpl/lambda.hpp>
# include <boost/mpl/bind.hpp>
# include <boost/mpl/quote.hpp>
# include <boost/mpl/arg.hpp>
# include <boost/mpl/protect.hpp>
# // metafunctions
# include <boost/mpl/arithmetic.hpp>
# include <boost/mpl/comparisons.hpp>
# include <boost/mpl/logical.hpp>
# include <boost/mpl/bitwise.hpp>
# // misc
# include <boost/mpl/identity.hpp>
# include <boost/mpl/always.hpp>
# include <boost/mpl/min.hpp>
# include <boost/mpl/max.hpp>
# include <boost/mpl/sizeof.hpp>
# endif                                              // ELIB_MP_BOOST_MLP_TESTS


#include <elib/pragma.hpp>

// Turn off C++11 narrowing error for clang
// to test with narrowing conversions
ELIB_PRAGMA_IGNORE_CXX11_NARROWING()

/* Metafunction Groups
 *    Type Selection
 *    Argument Binding & Composition
 *    Invocation
 *    Arithmetic
 *    Comparison
 *    Logical
 *    Bitwise
 *    Misc (other)
 */
BOOST_AUTO_TEST_SUITE(mp_metafunctions_test_suite)

////////////////////////////////////////////////////////////////////////////////
//                                Type Selection
////////////////////////////////////////////////////////////////////////////////

  //-------------------------------- if & if_c --------------------------------// 
  BOOST_AUTO_TEST_CASE(if_test)
  {
    using E1 = typename e::if_<true_, good, bad>::type;
    using E2 = e::if_t<false_, bad, good>;
    using E3 = typename e::if_c<true, good, bad>::type;
    using E4 = e::if_c_t<false, bad, good>;
    
    GOOD_TYPE(E1);
    GOOD_TYPE(E2);
    GOOD_TYPE(E3);
    GOOD_TYPE(E4);
  }                                                         // if_test
  
  //-------------------------------- eval_if --------------------------------// 
  BOOST_AUTO_TEST_CASE(eval_if_test)
  {
    using E1 = typename e::eval_if<true_, e::identity<good>, e::na>::type;
    using E2 = e::eval_if_t<false_, e::na, e::identity<good>>;
    using E3 = typename e::eval_if_c<true, e::identity<good>, e::na>::type;
    using E4 = e::eval_if_c_t<false, e::na, e::identity<good>>;
    
    GOOD_TYPE(E1);
    GOOD_TYPE(E2);
    GOOD_TYPE(E3);
    GOOD_TYPE(E4);
  }                                                         // eval_if_test

////////////////////////////////////////////////////////////////////////////////
//                    Composition & Argument Binding                                             
////////////////////////////////////////////////////////////////////////////////
  
  //-------------------------------- arg & placeholders ---------------------// 
  BOOST_AUTO_TEST_CASE(arg_test)
  {
    using namespace e;
    using E1 = typename apply_wrap< arg<1>, good, bad, bad, bad>::type;
    using E2 = apply_wrap_t< arg<3>, bad, bad, good, bad, bad>;
    using E3 = apply_wrap_t< _2, bad, good>;
    using E4 = apply_wrap_t< _5, bad, bad, bad, bad, good>;
                                     
    GOOD_TYPE(E1);
    GOOD_TYPE(E2);
    GOOD_TYPE(E3);
    GOOD_TYPE(E4);
  }                                                         // arg_test
  
  //-------------------------------- quote --------------------------------// 
  BOOST_AUTO_TEST_CASE(quote_test)
  {
    using namespace e;
    using E1 = e::apply_wrap_t<quote<nested_type>, bad, bad, good>;
    using E2 = e::apply_wrap_t<quote<non_nested_type>, bad, bad, bad>;
    using E2Expect = non_nested_type<bad, bad, bad>;
    GOOD_TYPE(E1);
    SAME_TYPE(E2, E2Expect);
  }                                                         // quote_test
  
  //-------------------------------- bind --------------------------------// 
  BOOST_AUTO_TEST_CASE(bind_test)
  {
    using namespace e;
    
    using E1 = apply_wrap_t<bind<identity_mfc, _1>, good>;
    using E2 = apply_wrap_t<bind<identity_mfc, _3>, bad, bad, good>;
    using E3 = apply_wrap_t<bind<third_mfc, _1, _2, _3>, bad, bad, good, bad>;
    using E4 = apply_wrap_t<bind<third_mfc, _2, _2, _1>, good, bad>;
    GOOD_TYPE(E1);
    GOOD_TYPE(E2);
    GOOD_TYPE(E3);
    GOOD_TYPE(E4);
  }                                                         // bind_test
  
  //-------------------------------- protect --------------------------------// 
  BOOST_AUTO_TEST_CASE(protect_test)
  {
    using namespace e;
    using BindExpr = bind<second_mfc, _1, _2>;
    
    using E1Expr = bind<quote<if_>, _1, _2, BindExpr>;
    using E1 = apply_wrap_t<E1Expr, e::false_, good>;
    
    using E2Expr = bind<quote<if_>, _1, _2, protect<BindExpr>>;
    using E2 = apply_wrap_t<E2Expr, e::false_, good>;
    
    GOOD_TYPE(E1);
    SAME_TYPE(E2, protect<BindExpr>);
  }                                                         // protect_test
  
  //-------------------------------- lambda --------------------------------// 
  BOOST_AUTO_TEST_CASE(lambda_test)
  {
    // non-placeholder expression
    {
      using T1 = int;
      using T2 = first_f<true_, false_>;
      using T3 = add_f<INT(1), INT(1)>;
      
      using E1 = typename e::lambda<T1>::type;
      using E1_ISL = e::is_placeholder_expression<T1>;
      SAME_TYPE(E1, T1);
      CHECK_VALUE(E1_ISL, false);
      
      using E2 = e::lambda_t<T2>;
      using E2_ISL = e::is_placeholder_expression<T2>;
      SAME_TYPE(E2, T2);
      CHECK_VALUE(E2_ISL, false);
      
      using E3 = e::lambda_t<T3>;
      using E3_ISL = e::is_placeholder_expression<T3>;
      SAME_TYPE(E3, T3);
      CHECK_VALUE(E3_ISL, false);
      
      OPT_BOOST(
          using B1 = typename b::lambda<T1>::type;
          using B1_ISL = b::is_lambda_expression<T1>;
          SAME_TYPE(B1, E1);
          SAME_VALUE(B1_ISL, E1_ISL);
          
          using B2 = typename b::lambda<T2>::type;
          using B2_ISL = b::is_lambda_expression<T2>;
          SAME_TYPE(B2, E2);
          SAME_VALUE(B2_ISL, E2_ISL);
          
          using B3 = typename b::lambda<T3>::type;
          using B3_ISL = b::is_lambda_expression<T3>;
          SAME_TYPE(B3, E3);
          SAME_VALUE(B3_ISL, E3_ISL);
      )
    }
    // placeholder tests
    {
      using E_ = e::lambda_t<e::_1>;
      using E_ISL = e::is_placeholder_expression<e::_1>;
      using E = e::apply_wrap_t<E_, true_, false_>;
      SAME_TYPE(E, true_);
      BOOST_CHECK(E_ISL::value);
      
      OPT_BOOST(
          using B_ = typename b::lambda<b::_1>::type;
          using B_ISL = b::is_lambda_expression<b::_1>;
          using B = typename b::apply_wrap2<
            B_, true_, false_
          >::type;
          SAME_TYPE(B, E);
          SAME_VALUE(B_ISL, E_ISL);
      )
    }
    // placeholder expression tests
    {
      using E_T = first_f<e::_1, false_>;
      using E_L = e::lambda_t< E_T >;
      using E_ISL = e::is_placeholder_expression<E_T>;
      using E = e::apply_wrap_t<E_L, true_>;
      SAME_TYPE(E, true_);
      BOOST_CHECK(E_ISL::value);
      
      OPT_BOOST(
        using B_T = first_f<b::_1, false_>;
        using B_L = typename b::lambda<B_T>::type;
        using B_ISL = b::is_lambda_expression<B_T>;
        using B = typename b::apply_wrap1<B_L, true_>::type;
        SAME_TYPE(B, E);
        SAME_VALUE(B_ISL, E_ISL);
      )
    }
    // nested placeholder expression
    {
      using E_T = first_f<
        first_f<e::_1, e::_2>
        , false_ 
      >;
      using E_L = e::lambda_t<E_T>;
      using E_ISL = e::is_placeholder_expression<E_T>;
      using E = e::apply_wrap_t<E_L, true_, false_>;
      SAME_TYPE(E, true_);
      BOOST_CHECK(E_ISL::value == true);
      
      OPT_BOOST(
        using B_T = first_f<
          first_f<b::_1, b::_2>
          , false_ 
        >;
        using B_L = typename b::lambda<B_T>::type;
        using B_ISL = b::is_lambda_expression<B_T>;
        using B = typename b::apply_wrap2<
          B_L, true_, false_
        >::type;
        SAME_TYPE(B, E);
        SAME_VALUE(B_ISL, E_ISL);
      )
    }
    // protected placeholder
    {
      using E_T = e::protect<e::_1>;
      using E_L = e::lambda_t<E_T>;
      using E_ISL = e::is_placeholder_expression<E_T>;
      using E = e::apply_wrap_t<E_L, true_, false_>;
      // check it hasn't been transformed
      SAME_TYPE(E_L, E_T);
      BOOST_CHECK(E_ISL::value == false);
      // check apply still wor
      SAME_TYPE(E, true_);
      
      OPT_BOOST(
        using B_T = b::protect<b::_1>;
        using B_L = typename b::lambda<B_T>::type;
        using B_ISL = b::is_lambda_expression<B_T>;
        using B = typename b::apply_wrap2<B_L, true_, false_>::type;
        SAME_TYPE(B_T, B_L);
        SAME_VALUE(B_ISL, E_ISL);
        SAME_TYPE(B, E);
      )
    }
    // protected bind expression
    {
      using E_T = e::protect<
        e::bind<first_mfc, e::_1, e::_2>
      >;
      using E_L = e::lambda_t<E_T>;
      using E_ISL = e::is_placeholder_expression<E_T>;
      using E = e::apply_wrap_t<E_L, true_, false_>;
      SAME_TYPE(E_L, E_T);
      BOOST_CHECK(E_ISL::value == false);
      SAME_TYPE(E, true_);
      
      OPT_BOOST(
        using B_T = b::protect<
          b::bind2<first_mfc, b::_1, b::_2>
        >;
        using B_L = typename b::lambda<B_T>::type;
        using B_ISL = b::is_lambda_expression<B_T>;
        using B = typename b::apply_wrap2<B_L, true_, false_>::type;
        SAME_TYPE(B_T, B_L);
        SAME_VALUE(B_ISL, E_ISL);
        SAME_TYPE(E, B);
      )
    }
    // protected nested placeholder expression
    {
      using E_T = first_f<
        e::protect<
          e::bind<first_mfc, e::_1, e::_2>
        >
        , false_ 
      >;
      using E_L = e::lambda_t<E_T>;
      using E_ISL = e::is_placeholder_expression<E_T>;
      SAME_TYPE(E_L, E_T);
      BOOST_CHECK(E_ISL::value == false);
      
      OPT_BOOST(
        using B_T = first_f<
          b::protect<
            b::bind2<first_mfc, b::_1, b::_2>
          >
          , false_ 
        >;
        using B_L = typename b::lambda<B_T>::type;
        using B_ISL = b::is_lambda_expression<B_T>;
        SAME_TYPE(B_L, B_T);
        SAME_VALUE(E_ISL, B_ISL);
      )
    }
     // generic protect
    {
      using E_T = e::protect<true_>;
      using E_L = e::lambda_t<E_T>;
      using E_ISL = e::is_placeholder_expression<E_T>;
      SAME_TYPE(E_L, E_T);
      BOOST_CHECK(E_ISL::value == false);
      
      OPT_BOOST(
        using B_T = b::protect<true_>;
        using B_L = typename b::lambda<B_T>::type;
        using B_ISL = b::is_lambda_expression<B_T>;
        SAME_TYPE(B_T, B_L);
        SAME_VALUE(B_ISL, E_ISL);
      )
    }
    // lambda-lambda test
    {
      using E_T = e::lambda< first_f<e::_1, e::_2> >;
      using E_L = e::lambda_t<E_T>;
      using E_ISL = e::is_placeholder_expression<E_T>;
      using E = e::apply_wrap_t<E_L, true_, false_>;
      SAME_TYPE(E, true_);
      BOOST_CHECK(E_ISL::value == true);
      
      OPT_BOOST(
        using B_T = b::lambda< first_f<b::_1, b::_2> >;
        using B_L = typename b::lambda< B_T >::type;
        using B_ISL = b::is_lambda_expression<B_T>;
        using B = typename b::apply_wrap2<B_L, true_, false_>::type;
        SAME_TYPE(B, E);
        SAME_VALUE(B_ISL, E_ISL);
      )
    }
  }                                                              // lambda_test
  
////////////////////////////////////////////////////////////////////////////////
//                              Invocation                                            
////////////////////////////////////////////////////////////////////////////////
  
  //-------------------------------- apply_wrap -----------------------------//
  BOOST_AUTO_TEST_CASE(apply_wrap_test)
  {
    // Check that these incorrect cases still compile.
    // Only when Type::type is accessed should the compile fail
    // NOTE: SAME_TYPE(x, x) is used to suppres unused warnings
    { 
      using E1 = e::apply_wrap<void_f>; SAME_TYPE(E1, E1);
      using E2 = e::apply_wrap<identity_f<void>>; SAME_TYPE(E2, E2);
      OPT_BOOST(
        using B1 = b::apply_wrap0<void_f>; SAME_TYPE(B1, B1);
        using B2 = b::apply_wrap0<identity_f<void>>; SAME_TYPE(B2, B2);
        using B3 = b::apply_wrap2<first_f<false_, true_>, void, void>; 
        SAME_TYPE(B3, B3);
      )
    }
    { 
      using E = typename e::apply_wrap<void_mfc>::type;
      SAME_TYPE(E, void);
      OPT_BOOST(
        using B = typename b::apply_wrap0<void_mfc>::type;
        SAME_TYPE(B, E);
      )
    }
    {
      using E = e::apply_wrap_t<identity_mfc, true_>;
      SAME_TYPE(E, true_);
      OPT_BOOST(
        using B = typename b::apply_wrap1<identity_mfc, true_>::type;
        SAME_TYPE(B, E);
      )
    }
    {
      using E = e::apply_wrap_t<first_mfc, true_, false_>;
      SAME_TYPE(E, true_);
      OPT_BOOST(
        using B = typename b::apply_wrap2<first_mfc, true_, false_>::type;
        SAME_TYPE(B, E);
      )
    }
    {
      using E = e::apply_wrap_t<add_mfc, INT(0), INT(1)>;
      CHECK_VALUE(E, 1);
      OPT_BOOST(
        using B = typename b::apply_wrap2<add_mfc, INT(0), INT(1)>::type;
        SAME_TYPE(B, E);
      )
    }
  }                                                         // apply_wrap_test
    
  //-------------------------------- apply --------------------------------// 
  //TODO
  BOOST_AUTO_TEST_CASE(apply_test)
  {
    BOOST_CHECK(true); 
  }                                                         // apply_test
  
  //---------------------------- unpack_args --------------------------------// 
  //TODO
  BOOST_AUTO_TEST_CASE(unpack_args_test)
  {
    BOOST_CHECK(true);
  }                                                         // unpack_args_test
  
////////////////////////////////////////////////////////////////////////////////
//                              Arithmetic
////////////////////////////////////////////////////////////////////////////////
  
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
      
      CHECK_INTC(e::negate<max_uint_>, unsigned, (-max_uint_::value));
      CHECK_INTC(e::negate<min_uint_>, unsigned, (-min_uint_::value));
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
    // unsigned
    {
      using E1 = add<UINT(0), UINT(0)>;
      SAME_INTC(E1, UINT(0));
      
      using E2 = add<UINT(1), UINT(1)>;
      SAME_INTC(E2, UINT(2));
      
      using E3 = add<UINT(-1), UINT(0)>;
      SAME_INTC(E3, UINT(((unsigned)-1) + ((unsigned)0)));
      
      using E4 = add<UINT(-1), UINT(-1)>;
      SAME_INTC(E4, UINT(((unsigned)-1) + ((unsigned)-1)));
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
  
////////////////////////////////////////////////////////////////////////////////
//                               Comparison                                           
////////////////////////////////////////////////////////////////////////////////
  
  //-------------------------------- equal --------------------------------// 
  BOOST_AUTO_TEST_CASE(equal_test)
  {
    using e::equal;
    using E1 = equal<INT(1), LONG(1)>;
    SAME_INTC(E1, BOOL(true));
    
    using E2 = equal<CHAR(0), UINT(1)>;
    SAME_INTC(E2, BOOL(false));
  }                                                         // equal_test
  
  //-------------------------------- not_equal --------------------------------// 
  BOOST_AUTO_TEST_CASE(not_equal_test)
  {
    using e::not_equal;
    using E1 = not_equal<BOOL(true), LONG(0)>;
    SAME_INTC(E1, BOOL(true));
    
    using E2 = not_equal<CHAR(1), UINT(1)>;
    SAME_INTC(E2, BOOL(false));
  }                                                         // not_equal_test
  
  //-------------------------------- less --------------------------------// 
  BOOST_AUTO_TEST_CASE(less_test)
  {
    using e::less;
    using E1 = less<INT(0), INT(1)>;
    SAME_INTC(E1, BOOL(true));
    
    using E2 = less<BOOL(true), INT(0)>;
    SAME_INTC(E2, BOOL(false));
    
    using E3 = less<CHAR(5), UINT(5)>;
    SAME_INTC(E3, BOOL(false));
  }                                                         // less_test
  
  //-------------------------------- less_equal -----------------------------// 
  BOOST_AUTO_TEST_CASE(less_equal_test)
  {
    using e::less_equal;
    
    using E1 = less_equal<UINT(0), LONG(100)>;
    SAME_INTC(E1, true_);
    
    using E2 = less_equal<CHAR(-1), INT(-1)>;
    SAME_INTC(E2, true_);
    
    using E3 = less_equal<BOOL(true), LONG(0)>;
    SAME_INTC(E3, false_);
  }
  
  //-------------------------------- greater --------------------------------// 
  BOOST_AUTO_TEST_CASE(greater_test)
  {
    using e::greater;
    using E1 = greater<BOOL(true), BOOL(false)>;
    SAME_INTC(E1, true_);
    
    using E2 = greater<UINT(10), CHAR(10)>;
    SAME_INTC(E2, false_);
    
    using E3 = greater<LONG(10), INT(100)>;
    SAME_INTC(E3, false_);
  }                                                         // greater_test
  
  //-------------------------------- greater_equal --------------------------// 
  BOOST_AUTO_TEST_CASE(greater_equal_test)
  {
    using e::greater_equal;
    using E1 = greater_equal<CHAR(10), LONG(1)>;
    SAME_INTC(E1, true_);
    
    using E2 = greater_equal<BOOL(1), INT(1)>;
    SAME_INTC(E2, true_);
    
    using E3 = greater_equal<INT(1), UINT(10)>;
    SAME_INTC(E3, false_);
    
    // INT(-1) in converted to uint before comparisons
    using E4 = greater_equal<UINT(10), INT(-1)>;
    SAME_INTC(E4, false_);
  }                                                       // greater_equal_test
  
////////////////////////////////////////////////////////////////////////////////
//                              Logical                                            
////////////////////////////////////////////////////////////////////////////////
  
  //-------------------------------- not --------------------------------// 
  BOOST_AUTO_TEST_CASE(not_test)
  {
    using e::not_;
    SAME_INTC(not_<true_>, BOOL(false));
    SAME_INTC(not_<false_>, BOOL(true));
    
    SAME_INTC(not_<INT(0)>, BOOL(true));
    SAME_INTC(not_<INT(1)>, BOOL(false));
    SAME_INTC(not_<INT(-1)>, BOOL(false));
  }                                                         // not_test
  
  //-------------------------------- and --------------------------------// 
  BOOST_AUTO_TEST_CASE(and_test)
  {
    using e::and_;
    using E1 = and_<false_, false_>;
    SAME_INTC(E1, BOOL(false));
    using E2 = and_<true_, false_>;
    SAME_INTC(E2, BOOL(false));
    using E3 = and_<false_, true_>;
    SAME_INTC(E3, BOOL(false));
    using E4 = and_<true_, true_>;
    SAME_INTC(E4, BOOL(true));
    
    using E5 = and_<INT(-5), INT(10)>;
    SAME_INTC(E5, BOOL(true));
    using E6 = and_<INT(0), true_>;
    SAME_INTC(E6, BOOL(false));
    
    using E7 = and_<true_, false_, e::na, e::na>;
    SAME_INTC(E7, BOOL(false));
  }                                                         // and_test
  
  //-------------------------------- or --------------------------------// 
  BOOST_AUTO_TEST_CASE(or_test)
  {
    using e::or_;
    using E1 = or_<false_, false_>;
    SAME_INTC(E1, BOOL(false));
    using E2 = or_<true_, false_>;
    SAME_INTC(E2, BOOL(true));
    using E3 = or_<false_, true_>;
    SAME_INTC(E3, BOOL(true));
    using E4 = or_<true_, true_>;
    SAME_INTC(E4, BOOL(true));
    
    using E5 = or_<false_, INT(10)>;
    SAME_INTC(E5, BOOL(true));
    using E6 = or_<INT(0), true_>;
    SAME_INTC(E6, BOOL(true));
    using E7 = or_<CHAR(-1), false_>;
    SAME_INTC(E7, BOOL(true));
    
    using E8 = or_<false_, true_, e::na>;
    SAME_INTC(E8, BOOL(true));
  }                                                         // or_test


////////////////////////////////////////////////////////////////////////////////
//                          Bitwise
////////////////////////////////////////////////////////////////////////////////
  
  //-------------------------------- bitnegate ------------------------------//
  //TODO
  BOOST_AUTO_TEST_CASE(bitnegate_test)
  {
    BOOST_CHECK(true);
  }                                                         // bitnegate_test
  
  //-------------------------------- binand --------------------------------// 
  //TODO
  BOOST_AUTO_TEST_CASE(bitand_test)
  {
    BOOST_CHECK(true);
  }                                                         // bitand_test
  
  //-------------------------------- bitor --------------------------------// 
  //TODO
  BOOST_AUTO_TEST_CASE(bitor_test)
  {
    BOOST_CHECK(true);
  }                                                         // bitor_test
  
  //-------------------------------- left_shift -----------------------------// 
  //TODO
  BOOST_AUTO_TEST_CASE(left_shift_test)
  {
    BOOST_CHECK(true);
  }                                                         // left_shift_test
  
  //-------------------------------- right_shift ----------------------------// 
  //TODO
  BOOST_AUTO_TEST_CASE(right_shift_test)
  {
    BOOST_CHECK(true);
  }                                                         // right_shift_test
  
////////////////////////////////////////////////////////////////////////////////
//                                    Misc                                                 
////////////////////////////////////////////////////////////////////////////////

  //-------------------------------- identity --------------------------------// 
  //TODO
  BOOST_AUTO_TEST_CASE(identity_test)
  {
    BOOST_CHECK(true);
  }                                                         // identity_test  
  
  //-------------------------------- always --------------------------------// 
  //TODO
  BOOST_AUTO_TEST_CASE(always_test)
  {
    BOOST_CHECK(true);
  }                                                         // always_test  
  

  //-------------------------------- min_max --------------------------------// 
  //TODO
  BOOST_AUTO_TEST_CASE(min_max_test)
  {
    BOOST_CHECK(true);
  }                                                         // min_max_test  
  

  //-------------------------------- sizeof --------------------------------// 
  //TODO
  BOOST_AUTO_TEST_CASE(sizeof_test)
  {
    BOOST_CHECK(true);
  }                                                         // sizeof_test  
  


BOOST_AUTO_TEST_SUITE_END()