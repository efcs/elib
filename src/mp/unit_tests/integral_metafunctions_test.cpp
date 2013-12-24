#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>


#include <elib/mp/arithmetic.hpp>
#include <elib/mp/bitwise.hpp>
#include <elib/mp/logical.hpp>
#include <elib/mp/detail/integral_constant.hpp>
#include <elib/pp/overload.hpp>
#include "mp_test_helper.hpp"

#define V_(x) x::type::value 
#
#define BOOL(v) static_cast<bool>(v)
#define BOOL_(v) bool_<BOOL(v)>
#
#define CHAR(v) static_cast<char>(v)
#define CHAR_(v) char_<CHAR(v)>
#
#define SHORT(v) static_cast<short>(v)
#define SHORT_(v) short_<SHORT(v)>
#
#define INT(v) static_cast<int>(v)
#define INT_(v) int_<INT(v)>
#
#define UINT(v) static_cast<unsigned>(v)
#define UINT_(v) uint_<UINT(v)>
#
#define LONG(v) static_cast<long>(v)
#define LONG_(v) long_<LONG(v)>
#
#define ULONG(v) static_cast<unsigned long>(v)
#define ULONG_(v) ulong_<ULONG(v)>
#
#define LLONG(v) static_cast<long long>(v)
#define LLONG_(v) llong_<LLONG(v)>
#
#define ULLONG(v) static_cast<unsigned long long>(v)
#define ULLONG_(v) ullong_<ULLONG(v)>
#
#define EXPAND_EXPR(...) ELIB_PP_OVERLOAD(EXPAND_EXPR_, __VA_ARGS__)(__VA_ARGS__)
#define EXPAND_EXPR_1(a) OP V_(a)
#define EXPAND_EXPR_2(a1, a2) V_(a1) OP V_(a2)
#define EXPAND_EXPR_3(a1, a2, a3) V_(a1) OP V_(a2) OP V_(a3)
#define EXPAND_EXPR_4(a1, a2, a3, a4) V_(a1) OP V_(a2) OP V_(a3) OP V_(a4)
#define EXPAND_EXPR_5(a1, a2, a3, a4, a5) V_(a1) OP V_(a2) OP V_(a3) OP V_(a4) OP V_(a5)
#define EXPAND_EXPR_6(a1, a2, a3, a4, a5, a6) V_(a1) OP V_(a2) OP V_(a3) OP V_(a4) OP V_(a5) OP V_(a6)

#
#define CHECK_RESULT(R, CT, result)                                       \
  CHECK( std::is_same<typename R::type::value_type, CT>::type::value ); \
  CHECK( R::type::value == result )
#
#define TEST_OP(etype, eval, ...)                    \
  do {                                               \
    using R = FN<__VA_ARGS__>;                       \
    using CT = decltype( EXPAND_EXPR(__VA_ARGS__) ); \
    constexpr CT result = EXPAND_EXPR(__VA_ARGS__);  \
    CHECK_RESULT(R, CT, result);                     \
    CHECK_RESULT(R, etype, eval);                    \
  } while (false)
#
#define TEST_SIGNED_TYPES(e, x, y)       \
  TEST_OP(int, e, char_<x>, char_<y>);   \
  TEST_OP(int, e, short_<x>, short_<y>); \
  TEST_OP(int, e, int_<x>, int_<y>);     \
  TEST_OP(long, e, long_<x>, long_<y>);  \
  TEST_OP(long long, e, llong_<x>, llong_<y>)
#
#define TEST_UNSIGNED_TYPES(e, x, y)               \
  TEST_OP(unsigned, e, uint_<x>, uint_<y>);        \
  TEST_OP(unsigned long, e, ulong_<x>, ulong_<y>); \
  TEST_OP(unsigned long long, e, ullong_<x>, ullong_<y>)
#
#define TEST_BOOL(e, x, y)  \
  TEST_OP(int, e, bool_<x>, bool_<y>)
#
#define TEST_TYPES(e, x, y)   \
  TEST_SIGNED_TYPES(e, x, y); \
  TEST_UNSIGNED_TYPES(e, x, y)
#
#define TEST_ALL_TYPES(e, x, y) \
  TEST_BOOL(e, x, y);           \
  TEST_TYPES(e, x, y)                                   
#
#define TEST_CONVERSIONS(e, x, y)                        \
  /* bool */                                             \
  TEST_OP(int, e, bool_<x>, char_<y>);                   \
  TEST_OP(int, e, short_<x>, bool_<y>);                  \
  TEST_OP(int, e, bool_<x>, int_<y>);                    \
  TEST_OP(unsigned, e, uint_<x>, bool_<y>);              \
  TEST_OP(long, e, bool_<x>, long_<y>);                  \
  TEST_OP(unsigned long, e, ulong_<x>, bool_<y>);        \
  TEST_OP(long long, e, bool_<x>, llong_<y>);            \
  TEST_OP(unsigned long long, e, ullong_<x>, bool_<y>);  \
  /* char */                                             \
  TEST_OP(int, e, short_<x>, char_<y>);                  \
  TEST_OP(int, e, char_<x>, int_<y>);                    \
  TEST_OP(unsigned, e, uint_<x>, char_<y>);              \
  TEST_OP(long, e, char_<x>, long_<y>);                  \
  TEST_OP(unsigned long, e, ulong_<x>, char_<y>);        \
  TEST_OP(long long, e, char_<x>, llong_<y>);            \
  TEST_OP(unsigned long long, e, ullong_<x>, char_<y>);  \
  /* short */                                            \
  TEST_OP(int, e, short_<x>, int_<y>);                   \
  TEST_OP(unsigned, e, uint_<x>, short_<y>);             \
  TEST_OP(long, e, short_<x>, long_<y>);                 \
  TEST_OP(unsigned long, e, ulong_<x>, short_<y>);       \
  TEST_OP(long long, e, short_<x>, llong_<y>);           \
  TEST_OP(unsigned long long, e, ullong_<x>, short_<y>); \
  /* int */                                              \
  TEST_OP(unsigned, e, uint_<x>, int_<y>);               \
  TEST_OP(long, e, int_<x>, long_<y>);                   \
  TEST_OP(unsigned long, e, ulong_<x>, int_<y>);         \
  TEST_OP(long long, e, int_<x>, llong_<y>);             \
  TEST_OP(unsigned long long, e, ullong_<x>, int_<y>);   \
  /* uint */                                             \
  TEST_OP(long, e, uint_<x>, long_<y>);                  \
  TEST_OP(unsigned long, e, ulong_<x>, uint_<y>);        \
  TEST_OP(long long, e, uint_<x>, llong_<y>);            \
  TEST_OP(unsigned long long, e, ullong_<x>, uint_<y>);  \
  /* long */                                             \
  TEST_OP(unsigned long, e, ulong_<x>, long_<y>);        \
  TEST_OP(long long, e, long_<x>, llong_<y>);            \
  TEST_OP(unsigned long long, e, ullong_<x>, long_<y>);  \
  /* unsigned long */                                    \
  TEST_OP(unsigned long long, e, ulong_<x>, llong_<y>);  \
  TEST_OP(unsigned long long, e, ullong_<x>, ulong_<y>)
#
BOOST_AUTO_TEST_SUITE(mp_integral_metafunctions_test_suite)

////////////////////////////////////////////////////////////////////////////////
//                            arithmetic                                              
////////////////////////////////////////////////////////////////////////////////

#define OP -
#define FN negate_t

  BOOST_AUTO_TEST_CASE(mp_arithmetic_negate)
  {
    TEST_OP(int, 0, false_);
    TEST_OP(int, -1, true_);
    TEST_OP(int, 0, int_<0>);
    TEST_OP(int, -1, int_<1>);
    TEST_OP(int, 1, int_<-1>);
    TEST_OP(unsigned, 0u, uint_<0>);
    TEST_OP(unsigned, UINT(-1), uint_<1>);
    TEST_OP(long, 0l, long_<0>);
    TEST_OP(long, 1l, long_<-1>);
    TEST_OP(long, -1l, long_<1>);
  }
  
#undef OP
#undef FN

#define OP +
#define FN add_t
    
  BOOST_AUTO_TEST_CASE(mp_arithmetic_add)
  {
    // all (w. bool)
    TEST_ALL_TYPES(0, 0, 0);
    TEST_ALL_TYPES(1, 1, 0);
    TEST_ALL_TYPES(1, 0, 1);
    // all (w/o bool)
    TEST_TYPES(2, 1, 1);
    TEST_TYPES(2, 2, 0);
    TEST_TYPES(2, 0, 2);
    // signed
    TEST_SIGNED_TYPES(0, -1, 1);
    TEST_SIGNED_TYPES(0, 1, -1);
    TEST_SIGNED_TYPES(-2, -1, -1);
    // mixed
    TEST_CONVERSIONS(0, 0, 0);
  }                                                         // mp_arithmetic_add

#undef OP
#undef FN

#define OP -
#define FN subtract_t
  
  BOOST_AUTO_TEST_CASE(mp_arithmetic_subtract)
  {
    // all (w. bool)
    TEST_ALL_TYPES(0, 0, 0);
    TEST_ALL_TYPES(1, 1, 0);
    TEST_ALL_TYPES(0, 1, 1);
    // all (w/o bool)
    TEST_TYPES(0, 2, 2);
    TEST_TYPES(1, 2, 1);
    TEST_TYPES(2, 4, 2);
    // signed
    TEST_SIGNED_TYPES(0, -1, -1);
    TEST_SIGNED_TYPES(2, 1, -1);
    TEST_SIGNED_TYPES(-2, -1, 1);
    // mixed
    TEST_CONVERSIONS(0, 0, 0);
  }                                                   // mp_arithmetic_subtract

#undef OP
#undef FN
  
#define OP *
#define FN multiply

  BOOST_AUTO_TEST_CASE(mp_arithmetic_multiply)
  {
    // all (w. bool)
    TEST_ALL_TYPES(0, 0, 0);
    TEST_ALL_TYPES(0, 1, 0);
    TEST_ALL_TYPES(0, 0, 1);
    TEST_ALL_TYPES(1, 1, 1);
    // all (w/o bool)
    TEST_TYPES(2, 1, 2);
    TEST_TYPES(2, 2, 1);
    // signed
    TEST_SIGNED_TYPES(-1, -1, 1);
    TEST_SIGNED_TYPES(-1, 1, -1);
    TEST_SIGNED_TYPES(1, -1, -1);
    // mixed
    TEST_CONVERSIONS(0, 0, 0);
  }                                                   // mp_arithmetic_multiply
  
#undef OP
#undef FN

#define OP /
#define FN divide_t

  BOOST_AUTO_TEST_CASE(mp_arithmetic_divide)
  {
    // all (including bool)
    TEST_ALL_TYPES(0, 0, 1);
    TEST_ALL_TYPES(1, 1, 1);
    // all (no bool)
    TEST_TYPES(2, 2, 1);
    TEST_TYPES(2, 4, 2);
    // signed 
    TEST_SIGNED_TYPES(-1, 1, -1);
    TEST_SIGNED_TYPES(-1, -1, 1);
    TEST_SIGNED_TYPES(1, -1, -1);
    // mixed
    TEST_CONVERSIONS(0, 0, 1);
    TEST_CONVERSIONS(1, 1, 1);
  }                                                     // mp_arithmetic_divide
  
#undef OP
#undef FN

#define OP %
#define FN modulus_t

  BOOST_AUTO_TEST_CASE(mp_arithmetic_modulus)
  {
    TEST_ALL_TYPES(0, 0, 1);
    TEST_ALL_TYPES(0, 1, 1);
    TEST_TYPES(1, 1, 2);
    TEST_SIGNED_TYPES(1, 1, -2);
    TEST_SIGNED_TYPES(-1, -1, 2);
    TEST_SIGNED_TYPES(-1, -1, -2);
    TEST_CONVERSIONS(0, 0, 1);
    TEST_CONVERSIONS(0, 1, 1);
  }                                                    // mp_arithmetic_modulus
  
#undef OP
#undef FN 

////////////////////////////////////////////////////////////////////////////////
//                            BITWISE                                              
////////////////////////////////////////////////////////////////////////////////

#define OP ~
#define FN bitnegate_t

  BOOST_AUTO_TEST_CASE(mp_bitwise_negate)
  {
    TEST_OP(int, ~0, false_);
    TEST_OP(int, ~1, true_);
    TEST_OP(int, ~0, int_<0>);
    TEST_OP(int, ~(-1), int_<-1>);
    TEST_OP(int, ~2, int_<2>);
    TEST_OP(unsigned, ~0u, uint_<0>);
    TEST_OP(unsigned, ~1u, uint_<1>);
  }                                                        // mp_bitwise_negate
  
#undef OP
#undef FN

#define OP &
#define FN bitand_t
  
  BOOST_AUTO_TEST_CASE(mp_bitwise_and)
  {
    TEST_ALL_TYPES(0, 0, 0);
    TEST_ALL_TYPES(0, 1, 0);
    TEST_ALL_TYPES(0, 0, 1);
    TEST_ALL_TYPES(1, 1, 1);
    // mixed
    TEST_CONVERSIONS(0, 0, 0);
    TEST_CONVERSIONS(1, 1, 1);
  }                                                         // mp_bitwise_and

#undef OP
#undef FN

#define OP |
#define FN bitor_t

  BOOST_AUTO_TEST_CASE(mp_bitwise_or)
  {
    TEST_ALL_TYPES(0, 0, 0);
    TEST_ALL_TYPES(1, 1, 0);
    TEST_ALL_TYPES(1, 0, 1);
    TEST_ALL_TYPES(1, 1, 1);
    // mixed
    TEST_CONVERSIONS(0, 0, 0);
    TEST_CONVERSIONS(1, 1, 1);
  }                                                         // mp_bitwise_or
  
#undef OP
#undef FN

#define OP ^
#define FN bitxor_t

  BOOST_AUTO_TEST_CASE(mp_bitwise_xor)
  {
    TEST_ALL_TYPES(0, 0, 0);
    TEST_ALL_TYPES(1, 1, 0);
    TEST_ALL_TYPES(1, 0, 1);
    TEST_ALL_TYPES(0, 1, 1);
    // mixed
    TEST_CONVERSIONS(0, 0, 0);
    TEST_CONVERSIONS(1, 1, 0);
    TEST_CONVERSIONS(0, 1, 1);
  }                                                         // mp_bitwise_xor
  
#undef OP
#undef FN

#define OP << 
#define FN shift_left_t
  
  BOOST_AUTO_TEST_CASE(mp_bitwise_shift_left)
  {
    // all (w. bool)
    TEST_ALL_TYPES(0, 0, 0);
    TEST_ALL_TYPES(0, 0, 1);
    // all (w/o bool)
    TEST_TYPES(2, 1, 1);
    TEST_TYPES(4, 1, 2);
    TEST_TYPES(4, 2, 1);
    // mixed
    
  }                                                    // mp_bitwise_shift_left
  
#undef OP
#undef FN

#define OP >>
#define FN shift_right_t
  
  BOOST_AUTO_TEST_CASE(mp_bitwise_shift_right)
  {
    TEST_ALL_TYPES(0, 0, 0);
    TEST_ALL_TYPES(0, 0, 1);
  }                                                   // mp_bitwise_shift_right

#undef OP
#undef FN

BOOST_AUTO_TEST_SUITE_END()