#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include <elib/aux/logical.hpp>
#include <elib/aux/integral_constant.hpp>
#include <elib/aux/static_assert.hpp>
#include <elib/aux/none.hpp>
#include <elib/aux/traits/is_same.hpp>

using namespace elib::aux;

template <bool Val, int Dummy = 0>
struct my_bool
{
    using type = my_bool;
    using value_type = bool;
    
    static constexpr const bool value = Val;
    static constexpr const int dummy = Dummy;
};

template <bool Val, int Dummy>
constexpr const bool my_bool<Val, Dummy>::value;

template <bool Val, int Dummy>
constexpr const int my_bool<Val, Dummy>::dummy;


using true1 = my_bool<true, 1>;
using true2 = my_bool<true, 2>;
using true3 = my_bool<true, 3>;
using true4 = my_bool<true, 4>;
using true5 = my_bool<true, 5>;

using false1 = my_bool<false, 1>;
using false2 = my_bool<false, 2>;
using false3 = my_bool<false, 3>;
using false4 = my_bool<false, 4>;
using false5 = my_bool<false, 5>;

struct empty {};


BOOST_AUTO_TEST_SUITE(elib_aux_logical_test_suite)

BOOST_AUTO_TEST_CASE(not_type_tests)
{
    ELIB_STATIC_ASSERT(not_<true_>::value == false);
    ELIB_STATIC_ASSERT(not_<false_>::value == true);
    ELIB_STATIC_ASSERT(not_<int_<0>>::value == true);
    ELIB_STATIC_ASSERT(not_<int_<-1>>::value == false);
    ELIB_STATIC_ASSERT(not_<int_<1>>::value == false);
    ELIB_STATIC_ASSERT(not_<size_type_<10000>>::value == false);
    BOOST_CHECK(true);
}

BOOST_AUTO_TEST_CASE(not_c_tests)
{
    ELIB_STATIC_ASSERT(not_c<true>::value == false);
    ELIB_STATIC_ASSERT(not_c<false>::value == true);
    ELIB_STATIC_ASSERT(not_c<0>::value == true);
    ELIB_STATIC_ASSERT(not_c<-1>::value == false);
    ELIB_STATIC_ASSERT(not_c<1>::value == false);
    ELIB_STATIC_ASSERT(not_c<10ul>::value == false);
    ELIB_STATIC_ASSERT(not_c<0ul>::value == true);
    BOOST_CHECK(true);
}

BOOST_AUTO_TEST_CASE(and_tests)
{
    // true - true
    {
        using T = and_<true1, true2>;
        ELIB_STATIC_ASSERT(T::value);
        ELIB_STATIC_ASSERT(is_same<T::which, none>::value);
    }
    // true - false
    {
        using T = and_<true1, false1>;
        ELIB_STATIC_ASSERT(not T::value);
        ELIB_STATIC_ASSERT(is_same<T::which, false1>::value);
    }
    // false - empty (second argument not evaluated)
    {
        using T = and_<false1, empty>;
        ELIB_STATIC_ASSERT(not T::value);
        ELIB_STATIC_ASSERT(is_same<T::which, false1>::value);
    }
    // true - true - true
    {
        using T = and_<true1, true2, true3>;
        ELIB_STATIC_ASSERT(T::value);
        ELIB_STATIC_ASSERT(is_same<T::which, none>::value);
    }
    // true - true - false
    {
        using T = and_<true1, true2, false1>;
        ELIB_STATIC_ASSERT(not T::value);
        ELIB_STATIC_ASSERT(is_same<T::which, false1>::value);
    }
    // true - false - empty
    {
        using T = and_<true1, false1, empty>;
        ELIB_STATIC_ASSERT(not T::value);
        ELIB_STATIC_ASSERT(is_same<T::which, false1>::value);
    }
    // false - empty - empty 
    {
        using T = and_<false1, empty, empty>;
        ELIB_STATIC_ASSERT(not T::value);
        ELIB_STATIC_ASSERT(is_same<T::which, false1>::value);
    }
    BOOST_CHECK(true);
}

BOOST_AUTO_TEST_CASE(and_c_tests)
{
    ELIB_STATIC_ASSERT(and_c<true, true>{});
    ELIB_STATIC_ASSERT(not and_c<true, false>{});
    ELIB_STATIC_ASSERT(not and_c<false, true>{});
    ELIB_STATIC_ASSERT(not and_c<false, false>{});
    ELIB_STATIC_ASSERT(and_c<true, true, true>{});
    ELIB_STATIC_ASSERT(not and_c<true, true, false>{});
    ELIB_STATIC_ASSERT(not and_c<true, false, true>{});
    ELIB_STATIC_ASSERT(not and_c<true, false, false>{});
    ELIB_STATIC_ASSERT(not and_c<false, true, true>{});
    ELIB_STATIC_ASSERT(not and_c<false, false, true>{});
    ELIB_STATIC_ASSERT(not and_c<false, true, false>{});
    ELIB_STATIC_ASSERT(not and_c<false, false, false>{});
    BOOST_CHECK(true);
}

BOOST_AUTO_TEST_CASE(fast_and_tests)
{
    ELIB_STATIC_ASSERT(fast_and<true1, true1>{});
    ELIB_STATIC_ASSERT(not fast_and<true1, false1>{});
    ELIB_STATIC_ASSERT(not fast_and<false1, true1>{});
    ELIB_STATIC_ASSERT(not fast_and<false1, false1>{});
    ELIB_STATIC_ASSERT(fast_and<true1, true1, true1>{});
    ELIB_STATIC_ASSERT(not fast_and<true1, true1, false1>{});
    ELIB_STATIC_ASSERT(not fast_and<true1, false1, true1>{});
    ELIB_STATIC_ASSERT(not fast_and<true1, false1, false1>{});
    ELIB_STATIC_ASSERT(not fast_and<false1, true1, true1>{});
    ELIB_STATIC_ASSERT(not fast_and<false1, false1, true1>{});
    ELIB_STATIC_ASSERT(not fast_and<false1, true1, false1>{});
    ELIB_STATIC_ASSERT(not fast_and<false1, false1, false1>{});
    BOOST_CHECK(true);
}

BOOST_AUTO_TEST_CASE(fast_and_c_tests)
{
    ELIB_STATIC_ASSERT(fast_and_c<true, true>{});
    ELIB_STATIC_ASSERT(not fast_and_c<true, false>{});
    ELIB_STATIC_ASSERT(not fast_and_c<false, true>{});
    ELIB_STATIC_ASSERT(not fast_and_c<false, false>{});
    ELIB_STATIC_ASSERT(fast_and_c<true, true, true>{});
    ELIB_STATIC_ASSERT(not fast_and_c<true, true, false>{});
    ELIB_STATIC_ASSERT(not fast_and_c<true, false, true>{});
    ELIB_STATIC_ASSERT(not fast_and_c<true, false, false>{});
    ELIB_STATIC_ASSERT(not fast_and_c<false, true, true>{});
    ELIB_STATIC_ASSERT(not fast_and_c<false, false, true>{});
    ELIB_STATIC_ASSERT(not fast_and_c<false, true, false>{});
    ELIB_STATIC_ASSERT(not fast_and_c<false, false, false>{});
    BOOST_CHECK(true);
}


BOOST_AUTO_TEST_CASE(or_tests)
{
    // true - empty
    {
        using T = or_<true1, empty>;
        ELIB_STATIC_ASSERT(T::value);
        ELIB_STATIC_ASSERT(is_same<T::which, true1>::value);
    }
    // false - true
    {
        using T = or_<false1, true1>;
        ELIB_STATIC_ASSERT(T::value);
        ELIB_STATIC_ASSERT(is_same<T::which, true1>::value);
    }
    // false - false
    {
        using T = or_<false1, false2>;
        ELIB_STATIC_ASSERT(not T::value);
        ELIB_STATIC_ASSERT(is_same<T::which, none>::value);
    }
    // true - empty - empty
    {
        using T = or_<true1, empty, empty>;
        ELIB_STATIC_ASSERT(T::value);
        ELIB_STATIC_ASSERT(is_same<T::which, true1>::value);
    }
    // false - true - empty
    {
        using T = or_<false1, true1, empty>;
        ELIB_STATIC_ASSERT(T::value);
        ELIB_STATIC_ASSERT(is_same<T::which, true1>::value);
    }
    // false - false - true
    {
        using T = or_<false1, false2, true1>;
        ELIB_STATIC_ASSERT(T::value);
        ELIB_STATIC_ASSERT(is_same<T::which, true1>::value);
    }
    // false - false - false
    {
        using T = or_<false1, false2, false3>;
        ELIB_STATIC_ASSERT(not T::value);
        ELIB_STATIC_ASSERT(is_same<T::which, none>::value);
    }
    BOOST_CHECK(true);
}

BOOST_AUTO_TEST_CASE(or_c_tests)
{
    ELIB_STATIC_ASSERT(or_c<true, true>{});
    ELIB_STATIC_ASSERT(or_c<true, false>{});
    ELIB_STATIC_ASSERT(or_c<false, true>{});
    ELIB_STATIC_ASSERT(not or_c<false, false>{});
    ELIB_STATIC_ASSERT(or_c<true, true, true>{});
    ELIB_STATIC_ASSERT(or_c<true, true, false>{});
    ELIB_STATIC_ASSERT(or_c<true, false, true>{});
    ELIB_STATIC_ASSERT(or_c<true, false, false>{});
    ELIB_STATIC_ASSERT(or_c<false, true, true>{});
    ELIB_STATIC_ASSERT(or_c<false, false, true>{});
    ELIB_STATIC_ASSERT(or_c<false, true, false>{});
    ELIB_STATIC_ASSERT(not or_c<false, false, false>{});
    BOOST_CHECK(true);
}

BOOST_AUTO_TEST_CASE(fast_or_tests)
{
    ELIB_STATIC_ASSERT(fast_or<true1, true1>{});
    ELIB_STATIC_ASSERT(fast_or<true1, false1>{});
    ELIB_STATIC_ASSERT(fast_or<false1, true1>{});
    ELIB_STATIC_ASSERT(not fast_or<false1, false1>{});
    ELIB_STATIC_ASSERT(fast_or<true1, true1, true1>{});
    ELIB_STATIC_ASSERT(fast_or<true1, true1, false1>{});
    ELIB_STATIC_ASSERT(fast_or<true1, false1, true1>{});
    ELIB_STATIC_ASSERT(fast_or<true1, false1, false1>{});
    ELIB_STATIC_ASSERT(fast_or<false1, true1, true1>{});
    ELIB_STATIC_ASSERT(fast_or<false1, false1, true1>{});
    ELIB_STATIC_ASSERT(fast_or<false1, true1, false1>{});
    ELIB_STATIC_ASSERT(not fast_or<false1, false1, false1>{});
    BOOST_CHECK(true);
}

BOOST_AUTO_TEST_CASE(fast_or_c_tests)
{
    ELIB_STATIC_ASSERT(fast_or_c<true, true>{});
    ELIB_STATIC_ASSERT(fast_or_c<true, false>{});
    ELIB_STATIC_ASSERT(fast_or_c<false, true>{});
    ELIB_STATIC_ASSERT(not fast_or_c<false, false>{});
    ELIB_STATIC_ASSERT(fast_or_c<true, true, true>{});
    ELIB_STATIC_ASSERT(fast_or_c<true, true, false>{});
    ELIB_STATIC_ASSERT(fast_or_c<true, false, true>{});
    ELIB_STATIC_ASSERT(fast_or_c<true, false, false>{});
    ELIB_STATIC_ASSERT(fast_or_c<false, true, true>{});
    ELIB_STATIC_ASSERT(fast_or_c<false, false, true>{});
    ELIB_STATIC_ASSERT(fast_or_c<false, true, false>{});
    ELIB_STATIC_ASSERT(not fast_or_c<false, false, false>{});
    BOOST_CHECK(true);
}

BOOST_AUTO_TEST_SUITE_END()