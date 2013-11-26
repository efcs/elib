#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include <elib/mp/detail/template_arity.hpp>
#include <elib/mp/types.hpp>

#include <type_traits>

namespace mp = elib::mp;

struct NONE {};

template <class=void>
struct ONE {};

template <class=void, class=void>
struct TWO {};

template <class=void, class=void, class=void>
struct THREE {};


BOOST_AUTO_TEST_SUITE(mp_detail_test_suite)

BOOST_AUTO_TEST_CASE(mp_detail_init)
{
  BOOST_CHECK((
    std::is_same<
      mp::detail::template_arity<NONE>::type
      , mp::na
    >::value
  ));

  BOOST_CHECK(mp::detail::template_arity<ONE<>>::value == 1);
  BOOST_CHECK(mp::detail::template_arity<TWO<>>::value == 2);
  BOOST_CHECK(mp::detail::template_arity<THREE<>>::value == 3);
  
}

BOOST_AUTO_TEST_SUITE_END()