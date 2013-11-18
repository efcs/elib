#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include <elib/mp/if.hpp>
#include <elib/mp/types.hpp>

#include <elib/pragma.hpp>
#include <type_traits>

using namespace elib;


#define CHECK_SAME(t1, t2) \
  BOOST_CHECK((std::is_same<t1, t2>::value))

  
struct if_t {};
struct else_t{};

struct if_tt { typedef if_t type; };
struct else_tt { typedef else_t type; };

ELIB_PRAGMA_DIAG_PUSH()
ELIB_PRAGMA_IGNORE_CXX11_NARROWING()

BOOST_AUTO_TEST_SUITE(mp_if_test_suite)

BOOST_AUTO_TEST_CASE(mp_if_test)
{
  using T1 = mp::if_t<mp::true_, if_t, else_t>;
  CHECK_SAME(T1, if_t);
  
  using T2 = mp::if_t<mp::false_, if_t, else_t>;
  CHECK_SAME(T2, else_t);
  
  using T3 = mp::if_t<mp::int_<1>, if_t, else_t>;
  CHECK_SAME(T3, if_t);
  
  using T4 = mp::if_t<mp::int_<0>, if_t, else_t>;
  CHECK_SAME(T4, else_t);
  
  using T5 = mp::if_t<mp::ulong_<1000>, if_t, else_t>;
  CHECK_SAME(T5, if_t);
  
}

BOOST_AUTO_TEST_CASE(mp_if_c_test)
{
  using T1 = mp::if_c_t<true, if_t, else_t>;
  CHECK_SAME(T1, if_t);
  
  using T2 = mp::if_c_t<false, if_t, else_t>;
  CHECK_SAME(T2, else_t);
  
  using T3 = mp::if_c_t<100, if_t, else_t>;
  CHECK_SAME(T3, if_t);
  
  using T4 = mp::if_c_t<0, if_t, else_t>;
  CHECK_SAME(T4, else_t);
  
}


BOOST_AUTO_TEST_CASE(mp_eval_if_test)
{
  using T1 = mp::eval_if_t<mp::true_, if_tt, else_tt>;
  CHECK_SAME(T1, if_t);
  
  using T2 = mp::eval_if_t<mp::false_, if_tt, else_tt>;
  CHECK_SAME(T2, else_t);
}

BOOST_AUTO_TEST_CASE(mp_eval_if_c_test)
{
  using T1 = mp::eval_if_c_t<true, if_tt, else_tt>;
  CHECK_SAME(T1, if_t);
  
  using T2 = mp::eval_if_c_t<false, if_tt, else_tt>;
  CHECK_SAME(T2, else_t);
}

BOOST_AUTO_TEST_SUITE_END()

ELIB_PRAGMA_DIAG_POP()