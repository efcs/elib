#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include <elib/mp/config.hpp>

#include <elib/mp/apply_wrap.hpp>
#include <elib/mp/arg.hpp>
#include <elib/mp/bind.hpp>
#include <elib/mp/has_apply.hpp>
#include <elib/mp/has_type.hpp>
#include <elib/mp/quote.hpp>
#include <elib/mp/protect.hpp>
#include <elib/mp/is_placeholder.hpp>

#include <type_traits>

#include <iostream>
#include <typeinfo>

namespace mp = elib::mp;

#define CHECK_SAME(T1, T2) \
  BOOST_CHECK((std::is_same<T1, T2>::value))

#define CHECK_GOOD(T) CHECK_SAME(T, good)
#define CHECK_BAD(T) CHECK_SAME(T, bad)

struct good {};
struct bad {};


BOOST_AUTO_TEST_SUITE(mp_compose_and_bind_test_suite)

////////////////////////////////////////////////////////////////////////////////
//                           ARG                                             
////////////////////////////////////////////////////////////////////////////////


  
BOOST_AUTO_TEST_CASE(mp_arg_test)
{
  
  using T1 = mp::arg<1>::template apply<good>::type;
  CHECK_GOOD(T1);
  
  using T2 = mp::arg<1>::template apply<good, bad, bad>::type;
  CHECK_GOOD(T2);
  
  using T3 = mp::arg<2>::template apply<bad, good>::type;
  CHECK_GOOD(T3);
  
  using T4 = mp::arg<2>::template apply<bad, good, bad>::type;
  CHECK_GOOD(T4);
}


BOOST_AUTO_TEST_CASE(mp_arg_placeholders_test)
{
  using namespace mp::placeholders;
  
  using T1 = _1::template apply<good>::type;
  CHECK_GOOD(T1);
  
  using T2 = _1::template apply<good, bad, bad>::type;
  CHECK_GOOD(T2);
  
  using T3 = _2::template apply<bad, good>::type;
  CHECK_GOOD(T3);
  
  using T4 = _2::template apply<bad, good, bad>::type;
  CHECK_GOOD(T4);
}

BOOST_AUTO_TEST_CASE(mp_is_placeholder_test)
{
  using namespace mp::placeholders;
  BOOST_CHECK(mp::is_placeholder<_1>::value);
  BOOST_CHECK(mp::is_placeholder<_9>::value);
  BOOST_CHECK(mp::is_placeholder<void>::value == false);
  BOOST_CHECK(mp::is_placeholder<int>::value == false);
}

////////////////////////////////////////////////////////////////////////////////
//                            HAS_APPLY  && APPLY                                             
////////////////////////////////////////////////////////////////////////////////


struct APPLY_A
{
  struct apply
  {
    typedef good type;
  };
};

struct APPLY_B
{
  template <class T>
  struct apply
  {
    typedef T type;
  };
};

struct APPLY_C
{
  template <class T=good>
  struct apply
  {
    typedef T type;
  };
};


BOOST_AUTO_TEST_CASE(mp_test_apply_wrap)
{
  using T1 = mp::apply_wrap_t<APPLY_A>;
  CHECK_GOOD(T1);
  
  using T2 = mp::apply_wrap_t<APPLY_B, good>;
  CHECK_GOOD(T2);
  
  using T3 = mp::apply_wrap_t<APPLY_C>;
  CHECK_GOOD(T3);
  
  using T4 = mp::apply_wrap_t<APPLY_C, good>;
  CHECK_GOOD(T4);
  
  using T5 = mp::apply_wrap_t<APPLY_C, bad>;
  CHECK_BAD(T5);
}

////////////////////////////////////////////////////////////////////////////////
//                            QUOTE                                              
////////////////////////////////////////////////////////////////////////////////

template <class One>
struct QUOTE1
{
  typedef One type;
};

template <class One, class Two>
struct QUOTE2
{
  typedef Two type;
};

template <class One, class Two, class Three>
struct QUOTE3
{
  typedef Three type;
};

template <class, class>
struct QUOTE4
{
  
};

/* create out own placeholders so we are not testing against mp::arg<> */
struct PH1 {};
struct PH2 {};
typedef void PH3;


BOOST_AUTO_TEST_CASE(mp_quote_test)
{
  using _T1 = mp::quote< QUOTE1<bad> >;
  using T1 = mp::apply_wrap_t<_T1, good>;
  CHECK_GOOD(T1);
  
  using _T2 = mp::quote< QUOTE2<bad, bad> >;
  using T2 = mp::apply_wrap_t<_T2, bad, good>;
  CHECK_GOOD(T2);
  
  using _T3 = mp::quote< QUOTE3<bad, bad, bad> >;
  using T3 = mp::apply_wrap_t<_T3, bad, bad, good>;
  CHECK_GOOD(T3);
  
  /* QUOTE4 has no internal typedef so QUOTE4<good, good> is returned */
  using _T4 = mp::quote< QUOTE4<bad, bad> >;
  using T4 = mp::apply_wrap_t<_T4, good, good>;
  using T4_2 = QUOTE4<good, good>;
  CHECK_SAME(T4, T4_2);
}


////////////////////////////////////////////////////////////////////////////////
//                             BIND                                               
////////////////////////////////////////////////////////////////////////////////

struct BF
{
  template <class P1, class P2>
  struct apply
  {
    typedef P1 type;
  };
};

BOOST_AUTO_TEST_CASE(mp_bind_test)
{
  using namespace mp::placeholders;
  
  using _T1 = mp::bind<BF, good, bad>;
  using T1 = mp::apply_wrap_t<_T1>;
  CHECK_GOOD(T1);
  
  using _T2 = mp::bind<BF, _1, _2>;
  using T2 = mp::apply_wrap_t<_T2, good, bad>;
  CHECK_GOOD(T2);
  
  using _T3 = mp::bind<BF, _2, _1>;
  using T3 = mp::apply_wrap_t<_T3, bad, good>;
  CHECK_GOOD(T3);
  
}


BOOST_AUTO_TEST_SUITE_END()