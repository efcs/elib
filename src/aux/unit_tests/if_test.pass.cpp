// REQUIRES: ELIB_AUX_SOURCE
#include <elib/aux/if.hpp>
#include <elib/aux/integral_constant.hpp>
#include <elib/aux/none.hpp>
#include <elib/aux/traits/is_same.hpp>
#include "rapid-cxx-test.hpp"


#if defined(__GNUC__) && !defined(__clang__)
# pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#endif

using namespace elib::aux;

using t1 = int_<1>;
using t2 = int_<2>;
using t3 = int_<3>;
using t4 = int_<4>;
using t5 = int_<5>;
struct empty {};


TEST_SUITE(elib_aux_if_test_suite)

TEST_CASE(if_then_test)
{
    {
        using T = if_<true_, t1, t2>::type;
        TEST_STATIC_ASSERT(T::value == 1);
    }
    {
        using T = if_<false_, t1, t2>::type;
        TEST_STATIC_ASSERT(T::value == 2);
    }
    {
        using T = if_t<true_, t1, t2>;
        TEST_STATIC_ASSERT(T::value == 1);
    }
    {
        using T = if_t<false_, t1, t2>;
        TEST_STATIC_ASSERT(T::value == 2);
    }
    {
        using T = if_c<true, t1, t2>::type;
        TEST_STATIC_ASSERT(T::value == 1);
    }
    {
        using T = if_c<false, t1, t2>::type;
        TEST_STATIC_ASSERT(T::value == 2);
    }
    {
        using T = if_c_t<true, t1, t2>;
        TEST_STATIC_ASSERT(T::value == 1);
    }
    {
        using T = if_c_t<false, t1, t2>;
        TEST_STATIC_ASSERT(T::value == 2);
    }
    TEST_CHECK(true);
}

TEST_CASE(if_else_test)
{
    {
        using T = if_<true_, t1>::else_<empty>::type;
        TEST_STATIC_ASSERT(T::value == 1);
    }
    {
        using T = if_<false_, empty>::else_<t2>::type;
        TEST_STATIC_ASSERT(T::value == 2);
    }
    {
        using T = if_<true_, t1>::else_t<empty>;
        TEST_STATIC_ASSERT(T::value == 1);
    }
    {
        using T = if_<false_, empty>::else_t<t2>;
        TEST_STATIC_ASSERT(T::value == 2);
    }
    TEST_CHECK(true);
}

TEST_CASE(if_else_if_test)
{
    {
        using T = if_<true_, t1>::else_if<empty, empty, empty>::type;
        TEST_STATIC_ASSERT(T::value == 1);
    }
    {
        using T = if_<false_, empty>::else_if<true_, t2, empty>::type;
        TEST_STATIC_ASSERT(T::value == 2);
    }
    {
        using T = if_<false_, empty>::else_if<false_, empty, t3>::type;
        TEST_STATIC_ASSERT(T::value == 3);
    }
    {
        using T = if_<true_, t1>::else_if_t<empty, empty, empty>;
        TEST_STATIC_ASSERT(T::value == 1);
    }
    {
        using T = if_<false_, empty>::else_if_t<true_, t2, empty>;
        TEST_STATIC_ASSERT(T::value == 2);
    }
    {
        using T = if_<false_, empty>::else_if_t<false_, empty, t3>;
        TEST_STATIC_ASSERT(T::value == 3);
    }
    {
        using T = if_<true_, t1>::else_if_c<false, empty, empty>::type;
        TEST_STATIC_ASSERT(T::value == 1);
    }
    {
        using T = if_<false_, empty>::else_if_c<true, t2, empty>::type;
        TEST_STATIC_ASSERT(T::value == 2);
    }
    {
        using T = if_<false_, empty>::else_if_c<false, empty, t3>::type;
        TEST_STATIC_ASSERT(T::value == 3);
    }
    {
        using T = if_<true_, t1>::else_if_c_t<false, empty, empty>;
        TEST_STATIC_ASSERT(T::value == 1);
    }
    {
        using T = if_<false_, empty>::else_if_c_t<true, t2, empty>;
        TEST_STATIC_ASSERT(T::value == 2);
    }
    {
        using T = if_<false_, empty>::else_if_c_t<false, empty, t3>;
        TEST_STATIC_ASSERT(T::value == 3);
    }
    TEST_CHECK(true);
}

TEST_CASE(if_else_if_else_test)
{
    {
        using T = if_<true_, t1>::else_if<empty, empty>::else_<empty>::type;
        TEST_STATIC_ASSERT(T::value == 1);
    }
    {
        using T = if_<false_, empty>::else_if<true_, t2>::else_<empty>::type;
        TEST_STATIC_ASSERT(T::value == 2);
    }
    {
        using T = if_<false_, empty>::else_if<false_, empty>::else_<t3>::type;
        TEST_STATIC_ASSERT(T::value == 3);
    }
    {
        using T = if_<true_, t1>::else_if<empty, empty>::else_t<empty>;
        TEST_STATIC_ASSERT(T::value == 1);
    }
    {
        using T = if_<false_, empty>::else_if<true_, t2>::else_t<empty>;
        TEST_STATIC_ASSERT(T::value == 2);
    }
    {
        using T = if_<false_, empty>::else_if<false_, empty>::else_t<t3>;
        TEST_STATIC_ASSERT(T::value == 3);
    }
    TEST_CHECK(true);
}


TEST_CASE(eval_if_test)
{
    {
        using T = eval_if<true_, t1, empty>::type;
        TEST_STATIC_ASSERT(T::value == 1);
    }
    {
        // Dummy. This should compile.
        using T = eval_if<true_, empty, t1>;
    }
    {
        using T = eval_if<false_, empty, t1>::type;
        TEST_STATIC_ASSERT(T::value == 1);
    }
    {
        using T = eval_if<false_, t1, empty>;
    }
    {
        using T = eval_if_t<true_, t1, empty>;
        TEST_STATIC_ASSERT(T::value == 1);
    }
    {
        using T = eval_if_t<false_, empty, t1>;
        TEST_STATIC_ASSERT(T::value == 1);
    }
    TEST_CHECK(true);
}

TEST_CASE(eval_if_c_test)
{
    {
        using T = eval_if_c<true, t1, empty>::type;
        TEST_STATIC_ASSERT(T::value == 1);
    }
    {
        // Dummy. This should compile.
        using T = eval_if_c<true, empty, t1>;
    }
    {
        using T = eval_if_c<false, empty, t1>::type;
        TEST_STATIC_ASSERT(T::value == 1);
    }
    {
        using T = eval_if_c<false, t1, empty>;
    }
    {
        using T = eval_if_c_t<true, t1, empty>;
        TEST_STATIC_ASSERT(T::value == 1);
    }
    {
        using T = eval_if_c_t<false, empty, t1>;
        TEST_STATIC_ASSERT(T::value == 1);
    }
    TEST_CHECK(true);
}

TEST_SUITE_END()