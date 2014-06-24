// REQUIRES: ELIB_MP
#include <elib/mp/metafunctions.hpp>
#include <elib/mp/identity.hpp>
#include <elib/mp/pair.hpp>
#include <elib/mp/void.hpp>
#include <elib/aux/integral_constant.hpp>
#include <elib/aux/traits/is_base_of.hpp>
#include <elib/aux/traits/is_same.hpp>
#include "rapid-cxx-test.hpp"

using namespace elib;
using namespace elib::mp;
using namespace elib::mp::placeholders;

struct apply_type_test
{
  using apply = true_;
};

struct apply_empty_test
{
  template <class ...Args>
  using apply = true_;
};

struct apply_arg_test
{
  template <class T>
  using apply = T;
};

template <class T>
struct no_type_test : T
{};


TEST_SUITE(mp_metafunctions_test_suite)

//-------------------------------- if & eval_if -----------------------------// 

  TEST_CASE(mp_if_test)
  {
    TEST_CHECK( if_t<aux::is_same<_1, _1>, true_, false_>() );
    TEST_CHECK( if_t<aux::is_same<_1, _2>, false_, true_>() );
    TEST_CHECK( if_c_t<true, true_, false_>() );
    TEST_CHECK( if_c_t<false, false_, true_>() );
    TEST_CHECK( eval_if_t<aux::is_same<_1, _1>, identity<true_>, identity<false_>>() );
    TEST_CHECK( eval_if_t<false_, identity<false_>, identity<true_>>() );
    TEST_CHECK( eval_if_c_t<true, identity<true_>, void>() );
    TEST_CHECK( eval_if_c_t<false, void, identity<true_>>() );
  }
  
  
//-------------------------------- arg & placeholders -----------------------// 

  TEST_CASE(mp_arg_test)
  {
    TEST_CHECK(_1::apply<true_>::type() );
    TEST_CHECK(_1::apply<true_, void, void>::type() );
    TEST_CHECK(_2::apply<void, true_>::type() );
    TEST_CHECK(_2::apply<void, true_, void, void>::type() );
  }
  
  
//-------------------------------- apply_wrap -------------------------------// 

  TEST_CASE(mp_apply_wrap_test)
  {
    TEST_CHECK( apply_wrap_t< always<true_> >() );
    TEST_CHECK( apply_wrap_t<_1, true_>() );
    TEST_CHECK( apply_wrap_t<_2, false_, true_, void>() );
    TEST_CHECK( apply_wrap_t< apply_type_test >() );
    TEST_CHECK( apply_wrap_t< apply_empty_test >() );
    TEST_CHECK( apply_wrap_t< apply_arg_test, true_>() );
  }
   
//-------------------------------- protect --------------------------------// 

  TEST_CASE(mp_protect_test)
  {
    using NP = protect<void_>;
    TEST_CHECK( aux::is_base_of<void_, NP>::type::value );
    
    using P = protect< bind<void_> >;
    TEST_CHECK( !aux::is_base_of<void_, P>::type::value );
  }                                                         // mp_protect_test
   
//-------------------------------- quote --------------------------------// 
  
  TEST_CASE(mp_quote_test)
  {
    using IQ = quote< identity >;
    using IQA = typename IQ::template apply<true_>::type;
    TEST_CHECK( IQA() );
    
    using NTQ = quote< no_type_test >;
    using NTQA = typename NTQ::template apply<true_>::type;
    TEST_CHECK( NTQA() );
  }                                                         // mp_quote_test
  
//-------------------------------- bind --------------------------------// 
  
  TEST_CASE(mp_bind_test)
  {
    using AQ = quote< add >;
    using TripleFirst = bind< AQ, _1, _1, _1>;
    using AT = apply_wrap_t<TripleFirst, int_<1>, int_<10>>;
    TEST_CHECK( AT() == 3 );
    
    using AddTenSecond = bind<AQ, _2, int_<10> >;
    using BT = apply_wrap_t<AddTenSecond, int_<100>, int_<10>>;
    TEST_CHECK( BT() == 20 );
    
    using Nested = bind<AQ, TripleFirst, int_<10>>;
    using CT = apply_wrap_t<Nested, int_<1>>;
    TEST_CHECK( CT() == 13 );
    
    using Plain = bind<AQ, int_<1>, int_<2>, int_<3>>;
    using DT = apply_wrap_t<Plain>;
    TEST_CHECK( DT() == 6 );
  }                                                         // mp_bind_test
  
//-------------------------------- lambda --------------------------------// 

  TEST_CASE(mp_is_lambda_expr_test)
  {
    using Arg = _1;
    using QuoteExpr = quote< add >;
    using BindExpr = bind< QuoteExpr, int_<1>, int_<1> >;
    using ProtectExpr = protect< BindExpr >;
    using LEBindExpr = bind< QuoteExpr, _1, _2 >;
    using LEProtectExpr = protect< LEBindExpr >;
    using LEExpr = add<_1, _2>;
    using NestedLEExpr = add< add<_1, _2>, int_<42> >;
    using NestedLEExpr2 = add< add< add<_1, _1>, int_<0>>, int_<0>>;
    
    TEST_CHECK( is_lambda_expression<Arg>() );
    TEST_CHECK( !is_lambda_expression<QuoteExpr>() );
    TEST_CHECK( !is_lambda_expression<BindExpr>() );
    TEST_CHECK( !is_lambda_expression<ProtectExpr>() );
    TEST_CHECK( !is_lambda_expression<LEBindExpr>() );
    TEST_CHECK( !is_lambda_expression<LEProtectExpr>() );
    TEST_CHECK( is_lambda_expression<LEExpr>() );
    TEST_CHECK( is_lambda_expression<NestedLEExpr>() );
    TEST_CHECK( is_lambda_expression<NestedLEExpr2>() );
  }                                                   // mp_is_lambda_expr_test

  TEST_CASE(mp_lambda_test)
  {
    using Inc = add<_1, int_<1>>;
    using IncL = lambda<Inc>;
    TEST_CHECK(apply_wrap_t<IncL, int_<1>>() == 2);
    
    using Inc2L = lambda< add<Inc, int_<1>> >;
    TEST_CHECK(apply_wrap_t<Inc2L, int_<40>>() == 42);
    //TODO
  }                                                         // mp_lambda_test
  
//-------------------------------- apply --------------------------------// 

  TEST_CASE(mp_apply_test)
  {
    
  }                                                         // mp_apply_test

TEST_SUITE_END()