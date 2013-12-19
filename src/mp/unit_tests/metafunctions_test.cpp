#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include <elib/mp/always.hpp>
#include <elib/mp/apply.hpp>
#include <elib/mp/apply_wrap.hpp>
#include <elib/mp/arg.hpp>
#include <elib/mp/arithmetic.hpp>
#include <elib/mp/bind.hpp>
#include <elib/mp/bitwise.hpp>
#include <elib/mp/comparison.hpp>
#include <elib/mp/identity.hpp>
#include <elib/mp/if.hpp>
#include <elib/mp/integral_constant.hpp>
#include <elib/mp/lambda.hpp>
#include <elib/mp/logical.hpp>
#include <elib/mp/pair.hpp>
#include <elib/mp/protect.hpp>
#include <elib/mp/quote.hpp>
#include <elib/mp/sizeof.hpp>
#include <elib/mp/void.hpp>
#include <elib/mp/same_type.hpp>

#include "mp_test_helper.hpp"

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


BOOST_AUTO_TEST_SUITE(mp_metafunctions_test_suite)

  BOOST_AUTO_TEST_CASE(mp_if_test)
  {
    CHECK( if_t<same_type<_1, _1>, true_, false_>() );
    CHECK( if_t<same_type<_1, _2>, false_, true_>() );
    CHECK( if_c_t<true, true_, false_>() );
    CHECK( if_c_t<false, false_, true_>() );
    CHECK( eval_if_t<same_type<_1, _1>, identity<true_>, identity<false_>>() );
    CHECK( eval_if_t<false_, identity<false_>, identity<true_>>() );
    CHECK( eval_if_c_t<true, identity<true_>, void>() );
    CHECK( eval_if_c_t<false, void, identity<true_>>() );
  }
  
  BOOST_AUTO_TEST_CASE(mp_arg_test)
  {
    CHECK(_1::apply<true_>::type() );
    CHECK(_1::apply<true_, void, void>::type() );
    CHECK(_2::apply<void, true_>::type() );
    CHECK(_2::apply<void, true_, void, void>::type() );
  }
  
  BOOST_AUTO_TEST_CASE(mp_apply_wrap_test)
  {
    CHECK( apply_wrap_t< always<true_> >() );
    CHECK( apply_wrap_t<_1, true_>() );
    CHECK( apply_wrap_t<_2, false_, true_, void>() );
    CHECK( apply_wrap_t< apply_type_test >() );
    CHECK( apply_wrap_t< apply_empty_test >() );
    CHECK( apply_wrap_t< apply_arg_test, true_>() );
  }
  

BOOST_AUTO_TEST_SUITE_END()