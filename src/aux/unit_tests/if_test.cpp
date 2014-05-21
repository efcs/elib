#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include <elib/aux/if.hpp>
#include <elib/aux/integral_constant.hpp>
#include <elib/aux/static_assert.hpp>
#include <elib/aux/none.hpp>
#include <elib/aux/traits/is_same.hpp>

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


BOOST_AUTO_TEST_SUITE(elib_aux_if_test_suite)

BOOST_AUTO_TEST_CASE(if_then_test)
{
    {
        using T = if_<true_, t1, t2>::type;
        ELIB_STATIC_ASSERT(T::value == 1);
    }
    {
        using T = if_<false_, t1, t2>::type;
        ELIB_STATIC_ASSERT(T::value == 2);
    }
    {
        using T = if_t<true_, t1, t2>;
        ELIB_STATIC_ASSERT(T::value == 1);
    }
    {
        using T = if_t<false_, t1, t2>;
        ELIB_STATIC_ASSERT(T::value == 2);
    }
    {
        using T = if_c<true, t1, t2>::type;
        ELIB_STATIC_ASSERT(T::value == 1);
    }
    {
        using T = if_c<false, t1, t2>::type;
        ELIB_STATIC_ASSERT(T::value == 2);
    }
    {
        using T = if_c_t<true, t1, t2>;
        ELIB_STATIC_ASSERT(T::value == 1);
    }
    {
        using T = if_c_t<false, t1, t2>;
        ELIB_STATIC_ASSERT(T::value == 2);
    }
    BOOST_CHECK(true);
}

BOOST_AUTO_TEST_CASE(if_else_test)
{
    {
        using T = if_<true_, t1>::else_<empty>::type;
        ELIB_STATIC_ASSERT(T::value == 1);
    }
    {
        using T = if_<false_, empty>::else_<t2>::type;
        ELIB_STATIC_ASSERT(T::value == 2);
    }
    {
        using T = if_<true_, t1>::else_t<empty>;
        ELIB_STATIC_ASSERT(T::value == 1);
    }
    {
        using T = if_<false_, empty>::else_t<t2>;
        ELIB_STATIC_ASSERT(T::value == 2);
    }
    BOOST_CHECK(true);
}

BOOST_AUTO_TEST_CASE(if_else_if_test)
{
    {
        using T = if_<true_, t1>::else_if<empty, empty, empty>::type;
        ELIB_STATIC_ASSERT(T::value == 1);
    }
    {
        using T = if_<false_, empty>::else_if<true_, t2, empty>::type;
        ELIB_STATIC_ASSERT(T::value == 2);
    }
    {
        using T = if_<false_, empty>::else_if<false_, empty, t3>::type;
        ELIB_STATIC_ASSERT(T::value == 3);
    }
    {
        using T = if_<true_, t1>::else_if_t<empty, empty, empty>;
        ELIB_STATIC_ASSERT(T::value == 1);
    }
    {
        using T = if_<false_, empty>::else_if_t<true_, t2, empty>;
        ELIB_STATIC_ASSERT(T::value == 2);
    }
    {
        using T = if_<false_, empty>::else_if_t<false_, empty, t3>;
        ELIB_STATIC_ASSERT(T::value == 3);
    }
    {
        using T = if_<true_, t1>::else_if_c<false, empty, empty>::type;
        ELIB_STATIC_ASSERT(T::value == 1);
    }
    {
        using T = if_<false_, empty>::else_if_c<true, t2, empty>::type;
        ELIB_STATIC_ASSERT(T::value == 2);
    }
    {
        using T = if_<false_, empty>::else_if_c<false, empty, t3>::type;
        ELIB_STATIC_ASSERT(T::value == 3);
    }
    {
        using T = if_<true_, t1>::else_if_c_t<false, empty, empty>;
        ELIB_STATIC_ASSERT(T::value == 1);
    }
    {
        using T = if_<false_, empty>::else_if_c_t<true, t2, empty>;
        ELIB_STATIC_ASSERT(T::value == 2);
    }
    {
        using T = if_<false_, empty>::else_if_c_t<false, empty, t3>;
        ELIB_STATIC_ASSERT(T::value == 3);
    }
    BOOST_CHECK(true);
}

BOOST_AUTO_TEST_CASE(if_else_if_else_test)
{
    {
        using T = if_<true_, t1>::else_if<empty, empty>::else_<empty>::type;
        ELIB_STATIC_ASSERT(T::value == 1);
    }
    {
        using T = if_<false_, empty>::else_if<true_, t2>::else_<empty>::type;
        ELIB_STATIC_ASSERT(T::value == 2);
    }
    {
        using T = if_<false_, empty>::else_if<false_, empty>::else_<t3>::type;
        ELIB_STATIC_ASSERT(T::value == 3);
    }
    {
        using T = if_<true_, t1>::else_if<empty, empty>::else_t<empty>;
        ELIB_STATIC_ASSERT(T::value == 1);
    }
    {
        using T = if_<false_, empty>::else_if<true_, t2>::else_t<empty>;
        ELIB_STATIC_ASSERT(T::value == 2);
    }
    {
        using T = if_<false_, empty>::else_if<false_, empty>::else_t<t3>;
        ELIB_STATIC_ASSERT(T::value == 3);
    }
    BOOST_CHECK(true);
}


BOOST_AUTO_TEST_CASE(eval_if_test)
{
    {
        using T = eval_if<true_, t1, empty>::type;
        ELIB_STATIC_ASSERT(T::value == 1);
    }
    {
        // Dummy. This should compile.
        using T = eval_if<true_, empty, t1>;
    }
    {
        using T = eval_if<false_, empty, t1>::type;
        ELIB_STATIC_ASSERT(T::value == 1);
    }
    {
        using T = eval_if<false_, t1, empty>;
    }
    {
        using T = eval_if_t<true_, t1, empty>;
        ELIB_STATIC_ASSERT(T::value == 1);
    }
    {
        using T = eval_if_t<false_, empty, t1>;
        ELIB_STATIC_ASSERT(T::value == 1);
    }
    BOOST_CHECK(true);
}

BOOST_AUTO_TEST_CASE(eval_if_c_test)
{
    {
        using T = eval_if_c<true, t1, empty>::type;
        ELIB_STATIC_ASSERT(T::value == 1);
    }
    {
        // Dummy. This should compile.
        using T = eval_if_c<true, empty, t1>;
    }
    {
        using T = eval_if_c<false, empty, t1>::type;
        ELIB_STATIC_ASSERT(T::value == 1);
    }
    {
        using T = eval_if_c<false, t1, empty>;
    }
    {
        using T = eval_if_c_t<true, t1, empty>;
        ELIB_STATIC_ASSERT(T::value == 1);
    }
    {
        using T = eval_if_c_t<false, empty, t1>;
        ELIB_STATIC_ASSERT(T::value == 1);
    }
    BOOST_CHECK(true);
}

BOOST_AUTO_TEST_SUITE_END()