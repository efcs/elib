#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include "elib/mp/get_arg.hpp"

using namespace elib;

#include <type_traits>


BOOST_AUTO_TEST_SUITE(mp_get_arg_test_suite)

#define PACK5(type) \
  type, type, type, type, type

#define PACK10(type) PACK5(type), PACK5(type)

#define PACK25(type) PACK10(type), PACK10(type), PACK5(type)

#define PACK50(type) PACK25(type), PACK25(type)

#define PACK100(type) PACK50(type), PACK50(type)

#define PACK250(type) PACK100(type), PACK100(type), PACK50(type)
  
#define PACK500(type) PACK250(type), PACK250(type)
  
#define PACK1000(type) PACK500(type), PACK500(type)
  
#define CHECK_SAME(t1, t2) \
  BOOST_CHECK((std::is_same<t1, t2>::value))
  
  
typedef int good;
typedef long bad;

BOOST_AUTO_TEST_CASE(mp_get_arg_init)
{
  
  typedef mp::get_arg_t<0, good> T1;
  CHECK_SAME(T1, good);
  
  typedef mp::get_arg_t<1, bad, good> T2;
  CHECK_SAME(T2, good);
  
  typedef mp::get_arg_t<10, PACK10(bad), good> T3;
  CHECK_SAME(T3, good);
  
  typedef mp::get_arg_t<25, PACK25(bad), good> T4;
  CHECK_SAME(T4, good);
  
  /* some compilers limit template recursion depth, or max params
   * to 256, So to test this exact limit we want 255 params (+ index)
   * thus the index of the 255th param is 254
   */
  typedef mp::get_arg_t<254, PACK250(bad), bad, bad, bad, bad, good> T5;
  CHECK_SAME(T5, good);
  
  
#if ELIB_MP_PARAM_LIMIT == ELIB_MP_MAX_PARAM_LIMIT

  /* same logic as above, but just for 1024 */
  typedef mp::get_arg_t<1022, 
    PACK1000(bad), PACK10(bad), PACK10(bad), bad, bad, good> T5;
  CHECK_SAME(T5, good);
  
# endif
  
}

BOOST_AUTO_TEST_SUITE_END()