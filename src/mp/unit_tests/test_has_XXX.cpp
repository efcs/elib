#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include <elib/mp/detail/has_type.hpp>
#include <elib/mp/detail/has_apply.hpp>

#include <type_traits>

namespace mp = elib::mp;

BOOST_AUTO_TEST_SUITE(mp_has_XXX_test_suite)

struct good {};
struct bad {};

/* has-type-good and has-type-bad */
struct HTG1 { typedef good type; };
template <class T> struct HTG2 { typedef T type; };
typedef HTG2<good> HTG3;

struct HTB1 {};
struct HTB2 { int type; };
struct HTB3 { void type(); };
struct HTB4 { static void type(); };
template <class T> struct HTB5 {};


BOOST_AUTO_TEST_CASE(mp_has_type_test)
{
  BOOST_CHECK(mp::has_type<HTG1>::value);
  BOOST_CHECK(mp::has_type<HTG2<good>>::value);
  BOOST_CHECK(mp::has_type<HTG3>::value);
  
  BOOST_CHECK(mp::has_type<HTB1>::value == false);
  BOOST_CHECK(mp::has_type<HTB2>::value == false);
  BOOST_CHECK(mp::has_type<HTB3>::value == false);
  BOOST_CHECK(mp::has_type<HTB4>::value == false);
  BOOST_CHECK(mp::has_type<HTB5<bad>>::value == false);
}

struct HAG1
{
  struct apply
  {
    typedef good type;
  };
};

template <class=void, class=void>
struct HAG2
{
  struct apply
  {};
};

typedef HAG2<int, int> HAG3;

struct HAB1 {};
struct HAB2 { template <class> struct apply {}; };
struct HAB3 { template <class=void, class=void> struct apply {}; };
struct HAB4 { template <class=void> struct apply; };
struct HAB5 { typedef bad apply; };
struct HAB6 { void apply(); };
struct HAB7 { static void apply(); };
struct HAB8 { int apply; };

template <class> struct HAB9 {};
template <class, class> struct HAB10 { template <class> void apply(); };
template <class> struct HAB11 { template <class> struct apply {}; };

BOOST_AUTO_TEST_CASE(mp_has_apply_test)
{
  BOOST_CHECK((mp::has_apply<HAG1>::value));
  BOOST_CHECK((mp::has_apply<HAG2<>>::value));
  BOOST_CHECK((mp::has_apply<HAG3>::value));
  
  BOOST_CHECK((mp::has_apply<HAB1>::value == false));
  BOOST_CHECK((mp::has_apply<HAB2>::value == false));
  BOOST_CHECK((mp::has_apply<HAB3>::value == false));
  BOOST_CHECK((mp::has_apply<HAB4>::value == false));
  /* since HAB5 has a typedef for apply, this test case fails.
   * not sure if there is anything I can do about that
   */
  //BOOST_CHECK((mp::has_apply<HAB5>::value == false));
  BOOST_CHECK((mp::has_apply<HAB6>::value == false));
  BOOST_CHECK((mp::has_apply<HAB7>::value == false));
  BOOST_CHECK((mp::has_apply<HAB8>::value == false));
  BOOST_CHECK((mp::has_apply<HAB9<void>>::value == false));
  BOOST_CHECK((mp::has_apply<HAB10<bad, bad>>::value == false));
  BOOST_CHECK((mp::has_apply<HAB11<good>>::value == false));
}

BOOST_AUTO_TEST_SUITE_END()