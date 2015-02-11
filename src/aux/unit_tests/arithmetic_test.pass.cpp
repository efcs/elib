// REQUIRES: ELIB_AUX_SOURCE
#include <elib/aux/arithmetic.hpp>
#include <elib/aux/integral_constant.hpp>
#include <elib/aux/traits/is_same.hpp>
#include "rapid-cxx-test.hpp"


#if defined(__GNUC__) && !defined(__clang__)
# pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#elif defined(__clang__)
# pragma clang diagnostic ignored "-Wunused-macros"
# pragma clang diagnostic ignored "-Wunused-local-typedef"
#endif

#define TEST_1(x)                                                  \
    do {                                                           \
        using T = TEST_FN<ELIB_AUTO_INTC(x)>;                      \
        using T2 = TEST_FN_ALIAS<ELIB_AUTO_INTC(x)>;               \
        using Expect = ELIB_AUTO_INTC(TEST_OP (x));                \
        TEST_STATIC_ASSERT(is_same<T::type, Expect::type>::value); \
        TEST_STATIC_ASSERT(is_same<T::type, Expect::type>::value); \
    } while (false)
#

#define TEST_2(x, y)                                                    \
    do {                                                                \
        using T = TEST_FN<ELIB_AUTO_INTC(x), ELIB_AUTO_INTC(y)>;        \
        using T2 = TEST_FN_ALIAS<ELIB_AUTO_INTC(x), ELIB_AUTO_INTC(y)>; \
        using Expect = ELIB_AUTO_INTC((x) TEST_OP (y));                 \
        TEST_STATIC_ASSERT(is_same<T::type, Expect::type>::value);      \
        TEST_STATIC_ASSERT(is_same<T2::type, Expect::type>::value);     \
    } while (false)   
#

#define TEST_3(x, y, z)                                                                    \
    do {                                                                                   \
        using T = TEST_FN<ELIB_AUTO_INTC(x), ELIB_AUTO_INTC(y), ELIB_AUTO_INTC(z)>;        \
        using T2 = TEST_FN_ALIAS<ELIB_AUTO_INTC(x), ELIB_AUTO_INTC(y), ELIB_AUTO_INTC(z)>; \
        using Expect = ELIB_AUTO_INTC((x) TEST_OP (y) TEST_OP (z));                        \
        TEST_STATIC_ASSERT(is_same<T::type, Expect::type>::value);                         \
        TEST_STATIC_ASSERT(is_same<T2::type, Expect::type>::value);                        \
    } while (false)   
#

#define TEST_4(a, b, c, d)                                                                                    \
    do {                                                                                                      \
        using T = TEST_FN<ELIB_AUTO_INTC(a), ELIB_AUTO_INTC(b), ELIB_AUTO_INTC(c), ELIB_AUTO_INTC(d)>;        \
        using T2 = TEST_FN_ALIAS<ELIB_AUTO_INTC(a), ELIB_AUTO_INTC(b), ELIB_AUTO_INTC(c), ELIB_AUTO_INTC(d)>; \
        using Expect = ELIB_AUTO_INTC((a) TEST_OP (b) TEST_OP (c) TEST_OP (d));                               \
        TEST_STATIC_ASSERT(is_same<T::type, Expect>::value);                                                  \
        TEST_STATIC_ASSERT(is_same<T2::type, Expect>::value);                                                 \
    } while (false)   
#

#define TEST_5(a, b, c, d, e)                                                                                                    \
    do {                                                                                                                         \
        using T = TEST_FN<ELIB_AUTO_INTC(a), ELIB_AUTO_INTC(b), ELIB_AUTO_INTC(c), ELIB_AUTO_INTC(d), ELIB_AUTO_INTC(e)>;        \
        using T2 = TEST_FN_ALIAS<ELIB_AUTO_INTC(a), ELIB_AUTO_INTC(b), ELIB_AUTO_INTC(c), ELIB_AUTO_INTC(d), ELIB_AUTO_INTC(e)>; \
        using Expect = ELIB_AUTO_INTC((a) TEST_OP (b) TEST_OP (c) TEST_OP (d) TEST_OP (e));                                      \
        TEST_STATIC_ASSERT(is_same<T::type, Expect::type>::value);                                                               \
        TEST_STATIC_ASSERT(is_same<T2::type, Expect::type>::value);                                                              \
    } while (false)   
#

using namespace elib::aux;

TEST_SUITE(elib_aux_arithmetic_test_suite)

#define TEST_FN negate
#define TEST_FN_ALIAS negate_t
#define TEST_OP -
TEST_CASE(negate_test)
{
    TEST_1(true);
    TEST_1(false);
    TEST_1(0);
    TEST_1(1);
    TEST_1(-1);
    TEST_1(0u);
    TEST_1(1u);
    TEST_1(0ul);
    TEST_1(1ul);
    TEST_1(0l);
    TEST_1(-1l);
    TEST_1(1l);
    TEST_CHECK(true);
}
#undef TEST_FN
#undef TEST_FN_ALIAS
#undef TEST_OP
#define TEST_FN add
#define TEST_FN_ALIAS add_t
#define TEST_OP +
TEST_CASE(add_test)
{
    TEST_2(0, 0);
    TEST_2(0, 1);
    TEST_2(1, 0);
    TEST_2(1, 1);
    TEST_2(-1, 0);
    TEST_2(0, -1);
    TEST_2(-1, -1);
    TEST_2(1, -1);
    TEST_2(-1, 1);
    TEST_3(0, 0, 0);
    TEST_3(1, 0, 0);
    TEST_3(0, 1, 0);
    TEST_3(0, 0, 1);
    TEST_3(1, 1, 0);
    TEST_3(1, 0, 1);
    TEST_3(0, 1, 1);
    TEST_3(1, 1, 1);
    TEST_3(-1, 0, 0);
    TEST_3(0, -1, 0);
    TEST_3(0, 0, -1);
    TEST_3(-1, -1, 0);
    TEST_3(-1, 0, -1);
    TEST_3(0, -1, -1);
    TEST_3(-1, -1, -1);
    TEST_3(1, -1, 0);
    TEST_3(1, 0, -1);
    TEST_3(1, -1, -1);
    TEST_3(-1, 0, 1);
    TEST_3(-1, 1, 0);
    TEST_3(-1, 1, 1);
    TEST_3(1, 2, 3);
    TEST_3(3, 2, 1);
    TEST_3(-1, -2, -3);
    TEST_3(-3, -2, -1);
    TEST_3(1, 2, -3);
    TEST_3(1, -2, -3);
    TEST_3(-1, 2, -3);
    TEST_3(-1, -2, 3);
    TEST_5(0, 1, -1, 10u, -100l);
    TEST_CHECK(true);
}
#undef TEST_FN
#undef TEST_FN_ALIAS
#undef TEST_OP
#define TEST_FN subtract
#define TEST_FN_ALIAS subtract_t
#define TEST_OP -
TEST_CASE(subtract_test)
{
    TEST_2(0, 0);
    TEST_2(0, 1);
    TEST_2(1, 0);
    TEST_2(1, 1);
    TEST_2(-1, 0);
    TEST_2(0, -1);
    TEST_2(-1, -1);
    TEST_2(1, -1);
    TEST_2(-1, 1);
    TEST_3(0, 0, 0);
    TEST_3(1, 0, 0);
    TEST_3(0, 1, 0);
    TEST_3(0, 0, 1);
    TEST_3(1, 1, 0);
    TEST_3(1, 0, 1);
    TEST_3(0, 1, 1);
    TEST_3(1, 1, 1);
    TEST_3(-1, 0, 0);
    TEST_3(0, -1, 0);
    TEST_3(0, 0, -1);
    TEST_3(-1, -1, 0);
    TEST_3(-1, 0, -1);
    TEST_3(0, -1, -1);
    TEST_3(-1, -1, -1);
    TEST_3(1, -1, 0);
    TEST_3(1, 0, -1);
    TEST_3(1, -1, -1);
    TEST_3(-1, 0, 1);
    TEST_3(-1, 1, 0);
    TEST_3(-1, 1, 1);
    TEST_3(1, 2, 3);
    TEST_3(3, 2, 1);
    TEST_3(-1, -2, -3);
    TEST_3(-3, -2, -1);
    TEST_3(1, 2, -3);
    TEST_3(1, -2, -3);
    TEST_3(-1, 2, -3);
    TEST_3(-1, -2, 3);
    TEST_5(0, 1, -1, 10u, -100l);
    TEST_CHECK(true);
}
#undef TEST_FN
#undef TEST_FN_ALIAS
#undef TEST_OP
#define TEST_FN multiply
#define TEST_FN_ALIAS multiply_t
#define TEST_OP *
TEST_CASE(multiply_test)
{
    TEST_2(0, 0);
    TEST_2(0, 1);
    TEST_2(1, 0);
    TEST_2(1, 1);
    TEST_2(-1, 0);
    TEST_2(0, -1);
    TEST_2(-1, -1);
    TEST_2(1, -1);
    TEST_2(-1, 1);
    TEST_3(0, 0, 0);
    TEST_3(1, 0, 0);
    TEST_3(0, 1, 0);
    TEST_3(0, 0, 1);
    TEST_3(1, 1, 0);
    TEST_3(1, 0, 1);
    TEST_3(0, 1, 1);
    TEST_3(1, 1, 1);
    TEST_3(-1, 0, 0);
    TEST_3(0, -1, 0);
    TEST_3(0, 0, -1);
    TEST_3(-1, -1, 0);
    TEST_3(-1, 0, -1);
    TEST_3(0, -1, -1);
    TEST_3(-1, -1, -1);
    TEST_3(1, -1, 0);
    TEST_3(1, 0, -1);
    TEST_3(1, -1, -1);
    TEST_3(-1, 0, 1);
    TEST_3(-1, 1, 0);
    TEST_3(-1, 1, 1);
    TEST_3(1, 2, 3);
    TEST_3(3, 2, 1);
    TEST_3(-1, -2, -3);
    TEST_3(-3, -2, -1);
    TEST_3(1, 2, -3);
    TEST_3(1, -2, -3);
    TEST_3(-1, 2, -3);
    TEST_3(-1, -2, 3);
    TEST_5(0, 1, -1, 10u, -100l);
    TEST_CHECK(true);
}
#undef TEST_FN
#undef TEST_FN_ALIAS
#undef TEST_OP
#define TEST_FN divide
#define TEST_FN_ALIAS divide_t
#define TEST_OP /
TEST_CASE(divide_test)
{
    TEST_2(0, 1);
    TEST_2(1, 1);
    TEST_2(0, -1);
    TEST_2(-1, -1);
    TEST_2(1, -1);
    TEST_2(-1, 1);
    TEST_3(0, 1, 1);
    TEST_3(1, 1, 1);
    TEST_3(0, -1, -1);
    TEST_3(-1, -1, -1);
    TEST_3(1, -1, -1);
    TEST_3(-1, 1, 1);
    TEST_3(1, 2, 3);
    TEST_3(3, 2, 1);
    TEST_3(-1, -2, -3);
    TEST_3(-3, -2, -1);
    TEST_3(1, 2, -3);
    TEST_3(1, -2, -3);
    TEST_3(-1, 2, -3);
    TEST_3(-1, -2, 3);
    TEST_5(0, 1, -1, 10u, -100l);
    TEST_5(true, '0', -1, 10u, -100l);
    TEST_CHECK(true);
}
#undef TEST_FN
#undef TEST_FN_ALIAS
#undef TEST_OP
#define TEST_FN modulus
#define TEST_FN_ALIAS modulus_t
#define TEST_OP %
TEST_CASE(mod_test)
{
    TEST_2(0, 1);
    TEST_2(1, 1);
    TEST_2(2, 1);
    TEST_2(0, -1);
    TEST_2(1, -1);
    TEST_2(2, -1);
    TEST_2(-1, 1);
    TEST_2(-2, 1);
    TEST_2(-1, -1);
    TEST_2(-2, -1);
    TEST_CHECK(true);
}
#undef TEST_FN
#undef TEST_FN_ALIAS
#undef TEST_OP

#define INC_TEST(x)                                                \
    do {                                                           \
        using T = increment<ELIB_AUTO_INTC(x)>;                    \
        using T2 = increment_t<ELIB_AUTO_INTC(x)>;                 \
        using Expect = ELIB_AUTO_INTC(1 + (x));                    \
        TEST_STATIC_ASSERT(is_same<T::type, Expect::type>::value); \
        TEST_STATIC_ASSERT(is_same<T::type, Expect::type>::value); \
    } while (false)
#
TEST_CASE(increment_test)
{
    INC_TEST(true);
    INC_TEST(false);
    INC_TEST('0');
    INC_TEST(static_cast<short>(0));
    INC_TEST(static_cast<short>(-1));
    INC_TEST(static_cast<short>(1));
    INC_TEST(0);
    INC_TEST(-1);
    INC_TEST(-2);
    INC_TEST(1);
    INC_TEST(2);
    INC_TEST(0u);
    INC_TEST(1u);
    INC_TEST(0l);
    INC_TEST(-1l);
    INC_TEST(1l);
    INC_TEST(0ul);
    INC_TEST(1ul);
    TEST_CHECK(true);
}
#define DEC_TEST(x)                                                \
    do {                                                           \
        using T = decrement<ELIB_AUTO_INTC(x)>;                    \
        using T2 = decrement_t<ELIB_AUTO_INTC(x)>;                 \
        using Expect = ELIB_AUTO_INTC((x) - 1);                    \
        TEST_STATIC_ASSERT(is_same<T::type, Expect::type>::value); \
        TEST_STATIC_ASSERT(is_same<T::type, Expect::type>::value); \
    } while (false)
#
TEST_CASE(decrement_test)
{
    DEC_TEST(true);
    DEC_TEST(false);
    DEC_TEST('0');
    DEC_TEST(static_cast<short>(0));
    DEC_TEST(static_cast<short>(-1));
    DEC_TEST(static_cast<short>(1));
    DEC_TEST(0);
    DEC_TEST(-1);
    DEC_TEST(-2);
    DEC_TEST(1);
    DEC_TEST(2);
    DEC_TEST(0u);
    DEC_TEST(1u);
    DEC_TEST(0l);
    DEC_TEST(-1l);
    DEC_TEST(1l);
    DEC_TEST(0ul);
    DEC_TEST(1ul);
    TEST_CHECK(true);
}
TEST_SUITE_END()