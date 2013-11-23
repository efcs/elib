/* 
 * Test elib::mp against boost::mpl
 *
 * For the most part, these tests are nothing more
 * than running simple input against both elib and boost
 * 
 * Testing against boost may be poor style, 
 * but it is an easy way to catch obvious errors.
 * 
 * More complete testing is done in the
 * standalone versions of these tests
 */
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

// contains the namespace definitions
// ie namespace e and namespace b
// as well as OPT_BOOST macro
#include "mp_test_config.hpp"

#include <elib/mp/config.hpp>
#include <elib/mp/types.hpp>
#include <elib/mp/compose.hpp>
#include <elib/mp/invoke.hpp>
#include <elib/mp/detail/is_placeholder.hpp>

#if ELIB_MP_BOOST_MPL_TESTS
  //invoke
# include <boost/mpl/apply.hpp>
# include <boost/mpl/apply_wrap.hpp>
# include <boost/mpl/unpack_args.hpp> 
  // composition & arguments
# include <boost/mpl/placeholders.hpp>
# include <boost/mpl/lambda.hpp>
# include <boost/mpl/bind.hpp>
# include <boost/mpl/quote.hpp>
# include <boost/mpl/arg.hpp>
# include <boost/mpl/protect.hpp>
#endif                                              // ELIB_MP_BOOST_MPL_TESTS

#include <vector> /* used as a test class */
#include <iostream>



////////////////////////////////////////////////////////////////////////////////
//                            Test Cases                                          
////////////////////////////////////////////////////////////////////////////////

/* 
 * apply_wrap goes first, since it has no other dependancies.
 * The general order is
 * 
 * - apply_wrap
 * ---- Composition & Args -----
 * - args / placeholders
 * - bind
 * - quote
 * - protect
 * - lambda (depends on all above)
 * ---- Invocation ------
 * - apply (depends on lambda)
 * 
 */
BOOST_AUTO_TEST_SUITE(mp_compose_invoke_test_suite)

//-------------------------------- apply_wrap -------------------------------// 

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
    
  //-------------------------------- arg test --------------------------------// 
  
  BOOST_AUTO_TEST_CASE(arg_test)
  {
    {
      using T1 = e::arg<1>::template apply<true_>::type;
      SAME_TYPE(T1, true_);
      
      using T2 = e::arg<1>::template apply<true_, false_, false_>::type;
      SAME_TYPE(T2, true_);
      
      using T3 = e::arg<2>::template apply<false_, true_>::type;
      SAME_TYPE(T3, true_);
      
      using T4 = e::arg<2>::template apply<false_, true_, false_>::type;
      SAME_TYPE(T4, true_);
      
      using T1 = e::_1::template apply<true_>::type;
      SAME_TYPE(T1, true_);
      
      using T2 = e::_1::template apply<true_, false_, false_>::type;
      SAME_TYPE(T2, true_);
      
      using T3 = e::_2::template apply<false_, true_>::type;
      SAME_TYPE(T3, true_);
      
      using T4 = e::_2::template apply<false_, true_, false_>::type;
      SAME_TYPE(T4, true_);
    }
    {
      using E = e::apply_wrap_t<e::arg<1>, true_, false_>;
      SAME_TYPE(E, true_);
      OPT_BOOST(
        using B = typename b::apply_wrap2<b::arg<1>, true_, false_>::type;
        SAME_TYPE(B, E);
      )
    }
    {
      using E = e::apply_wrap_t<e::_2, false_, true_, false_>;
      SAME_TYPE(E, true_);
      OPT_BOOST(
        using B = typename b::apply_wrap3<b::_2, false_, true_, false_>::type;
        SAME_TYPE(B, E);
      )
    }
    // is_placeholder
    {
      BOOST_CHECK(e::is_placeholder<e::_1>::value);
      BOOST_CHECK(e::is_placeholder<e::_9>::value);
      BOOST_CHECK(e::is_placeholder<void>::value == false);
      BOOST_CHECK(e::is_placeholder<int>::value == false);
    }
  }                                                     // arg_test
  
  //-------------------------------- quote --------------------------------// 
  
  BOOST_AUTO_TEST_CASE(quote_test)
  {
    {
      using E = e::apply_wrap_t<e::quote<identity_f>, true_>;
      SAME_TYPE(E, true_);
      OPT_BOOST(
        using B = typename b::apply_wrap1<b::quote1<identity_f>, true_>::type;
        SAME_TYPE(B, E);
      )
    }
    {
      using E = e::apply_wrap_t<e::quote<first_f>, true_, false_>;
      SAME_TYPE(E, true_);
      OPT_BOOST(
        using B = 
          typename b::apply_wrap2<b::quote2<first_f>, true_, false_>::type;
        SAME_TYPE(B, E);
      )
    }
    // quote with nested type
    {
      using E = e::apply_wrap_t<e::quote<nested_type>, false_, false_, true_>;
      SAME_TYPE(E, true_);
      OPT_BOOST(
        using B = typename b::apply_wrap3<
          b::quote3<nested_type> 
          , false_, false_, true_
        >::type;
        SAME_TYPE(E, B);
      )   
    }
    // quote with no nested ::type
    {
      using E = e::apply_wrap_t<
        e::quote<non_nested_type>
        , true_, true_, true_
      >;
      using Expect = non_nested_type<true_, true_, true_>;
      SAME_TYPE(E, Expect);
      OPT_BOOST(
        using B = typename b::apply_wrap3<
          b::quote3<non_nested_type>
          , true_, true_, true_
        >::type;
        SAME_TYPE(E, B);
      )
    }
    // quote with no nested ::type, default template parameters
    {
      using E = e::apply_wrap_t<e::quote<std::vector>, int>;
      SAME_TYPE(std::vector<int>, E);
      // Boost doesn't handle default parameters nicely
      // So there is boost test for std::vector
    }
  }                                                         // quote_test

  //-------------------------------- bind --------------------------------// 
  
  BOOST_AUTO_TEST_CASE(bind_test)
  {
    // w/o placeholders
    {
      using E = e::apply_wrap_t<
        e::bind<first_mfc, true_, false_>
      >;
      SAME_TYPE(E, true_);
      OPT_BOOST(
        using B = typename b::apply_wrap0<
          b::bind2<first_mfc, true_, false_>
        >::type;
        SAME_TYPE(B, E);
      )
    }
    // w/ 1 placeholder
    {
      using E = e::apply_wrap_t<
        e::bind<second_mfc, false_, e::_1>
        , true_
      >;
      SAME_TYPE(E, true_);
      OPT_BOOST(
        using B = b::apply_wrap1<
          b::bind2<second_mfc, false_, b::_1>
          , true_ 
        >::type;
        SAME_TYPE(E, B);
      )
    }
    // w/ all placeholders
    {
      using E = e::apply_wrap_t<
        e::bind<first_mfc, e::_1, e::_2>
        , true_, false_
      >;
      SAME_TYPE(E, true_);
      OPT_BOOST(
        using B = typename b::apply_wrap2<
          b::bind2<first_mfc, b::_1, b::_2>
          , true_, false_
        >::type;
        SAME_TYPE(B, E);
      )
    }
    // nested bind
    {
      using E1 = e::bind<add_mfc, INT(1), e::_2>;
      using E = e::apply_wrap_t<
        e::bind<add_mfc, e::_1, E1>
        , INT(1), INT(0)
      >;
      SAME_TYPE(E, int_<2>);
      OPT_BOOST(
        using B1 = b::bind2<add_mfc, INT(1), b::_2>;
        using B = typename b::apply_wrap2<
          b::bind2<add_mfc, b::_1, B1>
          , INT(1), INT(0)
        >::type;
        SAME_TYPE(B, E);
      )
    }
  }                                                         // bind_test
  
  //-------------------------------- protect --------------------------------// 
  
  // Unit tests taken from boost documentation
  BOOST_AUTO_TEST_CASE(protect_test)
  {
    using EBind = e::bind<first_mfc, e::_1, e::_2>;
    using EProt = e::protect<EBind>;
    
    OPT_BOOST(
      using BBind = b::bind2<first_mfc, b::_1, b::_2>;
      using BProt = b::protect<BBind>;
    )
    // non-bind expr
    {
      using E = e::apply_wrap_t<
        e::protect<first_mfc>, true_, false_
      >;
      SAME_TYPE(E, true_);
      OPT_BOOST(
        using B = typename b::apply_wrap2<
          e::protect<first_mfc>, true_, false_
        >::type;
        SAME_TYPE(E, B);
      )
    }
    // unprotected bind expression
    {
      // third_mfc selects EBind
      // and calls it with _1, _2
      using ETest = e::bind<
        third_mfc, e::_1, e::_2, EBind
      >;
    
      using E = e::apply_wrap_t<
        ETest, true_, false_
      >;
    
      SAME_TYPE(E, true_);
      
      OPT_BOOST(
        using BTest = b::bind3<
          third_mfc, b::_1, b::_2, BBind
        >;
        
        using B = typename b::apply_wrap2<
          BTest, true_, false_
        >::type;
        
        SAME_TYPE(E, B);
      )
    }
    //protected bind expression
    {
      using ETest = e::bind<third_mfc, e::_1, e::_2, EProt>;
      using E = e::apply_wrap_t<ETest, true_, false_>;
      SAME_TYPE(E, EProt);
      // can't compare against E, but check for similar result
      OPT_BOOST(
        using BTest = b::bind3<third_mfc, b::_1, b::_2, BProt>;
        using B = typename b::apply_wrap2<BTest, true_, false_>::type;
        SAME_TYPE(B, BProt);
      )
    }
  }                                                         // protect_test
  
  //-------------------------------- lambda --------------------------------// 
  
  //TODO
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
  }                                                         // lambda_test
  
  //-------------------------------- apply --------------------------------// 

  //TODO
  BOOST_AUTO_TEST_CASE(apply_test)
  {
    BOOST_CHECK(true);
  }                                                         // apply_test

BOOST_AUTO_TEST_SUITE_END()
