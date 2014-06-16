// REQUIRES: ELIB_AUX_SOURCE
#include <elib/aux/logical.hpp>
#include <elib/aux/integral_constant.hpp>
#include <elib/aux/none.hpp>
#include <elib/aux/traits/is_same.hpp>
#include "rapid-cxx-test.hpp"


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


TEST_SUITE(elib_aux_logical_test_suite)

TEST_CASE(not_type_tests)
{
    TEST_STATIC_ASSERT(not_<true_>::value == false);
    TEST_STATIC_ASSERT(not_<false_>::value == true);
    TEST_STATIC_ASSERT(not_<int_<0>>::value == true);
    TEST_STATIC_ASSERT(not_<int_<-1>>::value == false);
    TEST_STATIC_ASSERT(not_<int_<1>>::value == false);
    TEST_STATIC_ASSERT(not_<size_type_<10000>>::value == false);
    TEST_CHECK(true);
}

TEST_CASE(not_c_tests)
{
    TEST_STATIC_ASSERT(not_c<true>::value == false);
    TEST_STATIC_ASSERT(not_c<false>::value == true);
    TEST_STATIC_ASSERT(not_c<0>::value == true);
    TEST_STATIC_ASSERT(not_c<-1>::value == false);
    TEST_STATIC_ASSERT(not_c<1>::value == false);
    TEST_STATIC_ASSERT(not_c<10ul>::value == false);
    TEST_STATIC_ASSERT(not_c<0ul>::value == true);
    TEST_CHECK(true);
}

TEST_CASE(and_tests)
{
    // true - true
    {
        using T = and_<true1, true2>;
        TEST_STATIC_ASSERT(T::value);
        TEST_STATIC_ASSERT(is_same<T::which, none>::value);
    }
    // true - false
    {
        using T = and_<true1, false1>;
        TEST_STATIC_ASSERT(not T::value);
        TEST_STATIC_ASSERT(is_same<T::which, false1>::value);
    }
    // false - empty (second argument not evaluated)
    {
        using T = and_<false1, empty>;
        TEST_STATIC_ASSERT(not T::value);
        TEST_STATIC_ASSERT(is_same<T::which, false1>::value);
    }
    // true - true - true
    {
        using T = and_<true1, true2, true3>;
        TEST_STATIC_ASSERT(T::value);
        TEST_STATIC_ASSERT(is_same<T::which, none>::value);
    }
    // true - true - false
    {
        using T = and_<true1, true2, false1>;
        TEST_STATIC_ASSERT(not T::value);
        TEST_STATIC_ASSERT(is_same<T::which, false1>::value);
    }
    // true - false - empty
    {
        using T = and_<true1, false1, empty>;
        TEST_STATIC_ASSERT(not T::value);
        TEST_STATIC_ASSERT(is_same<T::which, false1>::value);
    }
    // false - empty - empty 
    {
        using T = and_<false1, empty, empty>;
        TEST_STATIC_ASSERT(not T::value);
        TEST_STATIC_ASSERT(is_same<T::which, false1>::value);
    }
    TEST_CHECK(true);
}

TEST_CASE(and_c_tests)
{
    TEST_STATIC_ASSERT(and_c<true, true>{});
    TEST_STATIC_ASSERT(not and_c<true, false>{});
    TEST_STATIC_ASSERT(not and_c<false, true>{});
    TEST_STATIC_ASSERT(not and_c<false, false>{});
    TEST_STATIC_ASSERT(and_c<true, true, true>{});
    TEST_STATIC_ASSERT(not and_c<true, true, false>{});
    TEST_STATIC_ASSERT(not and_c<true, false, true>{});
    TEST_STATIC_ASSERT(not and_c<true, false, false>{});
    TEST_STATIC_ASSERT(not and_c<false, true, true>{});
    TEST_STATIC_ASSERT(not and_c<false, false, true>{});
    TEST_STATIC_ASSERT(not and_c<false, true, false>{});
    TEST_STATIC_ASSERT(not and_c<false, false, false>{});
    TEST_CHECK(true);
}

TEST_CASE(fast_and_tests)
{
    TEST_STATIC_ASSERT(fast_and<true1, true1>{});
    TEST_STATIC_ASSERT(not fast_and<true1, false1>{});
    TEST_STATIC_ASSERT(not fast_and<false1, true1>{});
    TEST_STATIC_ASSERT(not fast_and<false1, false1>{});
    TEST_STATIC_ASSERT(fast_and<true1, true1, true1>{});
    TEST_STATIC_ASSERT(not fast_and<true1, true1, false1>{});
    TEST_STATIC_ASSERT(not fast_and<true1, false1, true1>{});
    TEST_STATIC_ASSERT(not fast_and<true1, false1, false1>{});
    TEST_STATIC_ASSERT(not fast_and<false1, true1, true1>{});
    TEST_STATIC_ASSERT(not fast_and<false1, false1, true1>{});
    TEST_STATIC_ASSERT(not fast_and<false1, true1, false1>{});
    TEST_STATIC_ASSERT(not fast_and<false1, false1, false1>{});
    TEST_CHECK(true);
}

TEST_CASE(fast_and_c_tests)
{
    TEST_STATIC_ASSERT(fast_and_c<true, true>{});
    TEST_STATIC_ASSERT(not fast_and_c<true, false>{});
    TEST_STATIC_ASSERT(not fast_and_c<false, true>{});
    TEST_STATIC_ASSERT(not fast_and_c<false, false>{});
    TEST_STATIC_ASSERT(fast_and_c<true, true, true>{});
    TEST_STATIC_ASSERT(not fast_and_c<true, true, false>{});
    TEST_STATIC_ASSERT(not fast_and_c<true, false, true>{});
    TEST_STATIC_ASSERT(not fast_and_c<true, false, false>{});
    TEST_STATIC_ASSERT(not fast_and_c<false, true, true>{});
    TEST_STATIC_ASSERT(not fast_and_c<false, false, true>{});
    TEST_STATIC_ASSERT(not fast_and_c<false, true, false>{});
    TEST_STATIC_ASSERT(not fast_and_c<false, false, false>{});
    TEST_CHECK(true);
}


TEST_CASE(or_tests)
{
    // true - empty
    {
        using T = or_<true1, empty>;
        TEST_STATIC_ASSERT(T::value);
        TEST_STATIC_ASSERT(is_same<T::which, true1>::value);
    }
    // false - true
    {
        using T = or_<false1, true1>;
        TEST_STATIC_ASSERT(T::value);
        TEST_STATIC_ASSERT(is_same<T::which, true1>::value);
    }
    // false - false
    {
        using T = or_<false1, false2>;
        TEST_STATIC_ASSERT(not T::value);
        TEST_STATIC_ASSERT(is_same<T::which, none>::value);
    }
    // true - empty - empty
    {
        using T = or_<true1, empty, empty>;
        TEST_STATIC_ASSERT(T::value);
        TEST_STATIC_ASSERT(is_same<T::which, true1>::value);
    }
    // false - true - empty
    {
        using T = or_<false1, true1, empty>;
        TEST_STATIC_ASSERT(T::value);
        TEST_STATIC_ASSERT(is_same<T::which, true1>::value);
    }
    // false - false - true
    {
        using T = or_<false1, false2, true1>;
        TEST_STATIC_ASSERT(T::value);
        TEST_STATIC_ASSERT(is_same<T::which, true1>::value);
    }
    // false - false - false
    {
        using T = or_<false1, false2, false3>;
        TEST_STATIC_ASSERT(not T::value);
        TEST_STATIC_ASSERT(is_same<T::which, none>::value);
    }
    TEST_CHECK(true);
}

TEST_CASE(or_c_tests)
{
    TEST_STATIC_ASSERT(or_c<true, true>{});
    TEST_STATIC_ASSERT(or_c<true, false>{});
    TEST_STATIC_ASSERT(or_c<false, true>{});
    TEST_STATIC_ASSERT(not or_c<false, false>{});
    TEST_STATIC_ASSERT(or_c<true, true, true>{});
    TEST_STATIC_ASSERT(or_c<true, true, false>{});
    TEST_STATIC_ASSERT(or_c<true, false, true>{});
    TEST_STATIC_ASSERT(or_c<true, false, false>{});
    TEST_STATIC_ASSERT(or_c<false, true, true>{});
    TEST_STATIC_ASSERT(or_c<false, false, true>{});
    TEST_STATIC_ASSERT(or_c<false, true, false>{});
    TEST_STATIC_ASSERT(not or_c<false, false, false>{});
    TEST_CHECK(true);
}

TEST_CASE(fast_or_tests)
{
    TEST_STATIC_ASSERT(fast_or<true1, true1>{});
    TEST_STATIC_ASSERT(fast_or<true1, false1>{});
    TEST_STATIC_ASSERT(fast_or<false1, true1>{});
    TEST_STATIC_ASSERT(not fast_or<false1, false1>{});
    TEST_STATIC_ASSERT(fast_or<true1, true1, true1>{});
    TEST_STATIC_ASSERT(fast_or<true1, true1, false1>{});
    TEST_STATIC_ASSERT(fast_or<true1, false1, true1>{});
    TEST_STATIC_ASSERT(fast_or<true1, false1, false1>{});
    TEST_STATIC_ASSERT(fast_or<false1, true1, true1>{});
    TEST_STATIC_ASSERT(fast_or<false1, false1, true1>{});
    TEST_STATIC_ASSERT(fast_or<false1, true1, false1>{});
    TEST_STATIC_ASSERT(not fast_or<false1, false1, false1>{});
    TEST_CHECK(true);
}

TEST_CASE(fast_or_c_tests)
{
    TEST_STATIC_ASSERT(fast_or_c<true, true>{});
    TEST_STATIC_ASSERT(fast_or_c<true, false>{});
    TEST_STATIC_ASSERT(fast_or_c<false, true>{});
    TEST_STATIC_ASSERT(not fast_or_c<false, false>{});
    TEST_STATIC_ASSERT(fast_or_c<true, true, true>{});
    TEST_STATIC_ASSERT(fast_or_c<true, true, false>{});
    TEST_STATIC_ASSERT(fast_or_c<true, false, true>{});
    TEST_STATIC_ASSERT(fast_or_c<true, false, false>{});
    TEST_STATIC_ASSERT(fast_or_c<false, true, true>{});
    TEST_STATIC_ASSERT(fast_or_c<false, false, true>{});
    TEST_STATIC_ASSERT(fast_or_c<false, true, false>{});
    TEST_STATIC_ASSERT(not fast_or_c<false, false, false>{});
    TEST_CHECK(true);
}

TEST_SUITE_END()