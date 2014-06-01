#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include <elib/params.hpp>
#include <elib/aux/integral_constant.hpp>
#include <elib/aux/static_assert.hpp>
#include <elib/aux/traits/is_same.hpp>
#include <cstddef>
using namespace elib;
using namespace elib::params;
using namespace elib::aux;

#define TEST_ASSERT(...) ELIB_STATIC_ASSERT(__VA_ARGS__)
#define TEST_SAME(...)   TEST_ASSERT(is_same<__VA_ARGS__>::value)

template <class ...Types>
struct param_pack2
{
    using type = param_pack2;
    static constexpr std::size_t size = sizeof...(Types);
};

template <class ...Types>
constexpr std::size_t param_pack2<Types...>::size;


template <class T, T ...Values>
struct value_pack2
{
    using type = value_pack2;
    using value_type = T;
    static constexpr std::size_t size = sizeof...(Values);
};

template <class T, T ...Values>
constexpr std::size_t value_pack2<T, Values...>::size;

struct tag {};
struct tag2 {};

BOOST_AUTO_TEST_SUITE(elib_params_test_suite)

BOOST_AUTO_TEST_CASE(param_pack_test)
{
    {
        TEST_SAME(param_pack<>, param_pack<>::type);
        TEST_ASSERT(param_pack<>::size == 0);
    }{
        using T = param_pack<int>;
        TEST_SAME(T, T::type);
        TEST_ASSERT(T::size == 1);
    }{
        using T = param_pack<void, int, float>;
        TEST_SAME(T, T::type);
        TEST_ASSERT(T::size == 3);
    }
    BOOST_CHECK(true);
}

BOOST_AUTO_TEST_CASE(param_pack_c_test)
{
    {
        using T = param_pack_c<int>;
        using E = param_pack<>;
        TEST_SAME(T, E);
    }{
        using T = param_pack_c<int, 0>;
        using E = param_pack<int_<0>>;
        TEST_SAME(T, E);
    }{
        using T = param_pack_c<int, 0, 1, 2>;
        using E = param_pack<int_<0>, int_<1>, int_<2>>;
        TEST_SAME(T, E);
    }{
        using T = param_pack_c<bool, true, false>;
        using E = param_pack<true_, false_>;
        TEST_SAME(T, E);
    }
    BOOST_CHECK(true);
}

BOOST_AUTO_TEST_CASE(value_pack_test)
{
    {
        using T = value_pack<int>;
        TEST_SAME(T::type, T);
        TEST_ASSERT(T::size == 0);
    }{
        using T = value_pack<int, 0>;
        TEST_SAME(T::type, T);
        TEST_ASSERT(T::size == 1);
    }{
        using T = value_pack<int, 0, 1>;
        TEST_SAME(T::type, T);
        TEST_ASSERT(T::size == 2);
    }
    BOOST_CHECK(true);
}

BOOST_AUTO_TEST_CASE(convert_to_value_pack_test)
{
    {
        using From = param_pack_c<int>;
        using Expect = value_pack<int>;
        using T = convert_to_value_pack<value_pack, int, From>;
        TEST_SAME(T::type, Expect);
        TEST_SAME(T::type, convert_to_value_pack_t<value_pack, int, From>);
    }{
        using From = param_pack_c<int, 0, 1, 2>;
        using Expect = value_pack<int, 0, 1, 2>;
        using T = convert_to_value_pack<value_pack, int, From>;
        TEST_SAME(T::type, Expect);
        TEST_SAME(T::type, convert_to_value_pack_t<value_pack, int, From>);
    }{
        using From = tag();
        using Expect = value_pack<int>;
        using T = convert_to_value_pack<value_pack, int, From>;
        TEST_SAME(T::type, Expect);
        TEST_SAME(T::type, convert_to_value_pack_t<value_pack, int, From>);
    }{
        using From = tag(int_<0>, int_<1>, int_<2>);
        using Expect = value_pack<int, 0, 1, 2>;
        using T = convert_to_value_pack<value_pack, int, From>;
        TEST_SAME(T::type, Expect);
        TEST_SAME(T::type, convert_to_value_pack_t<value_pack, int, From>);
    }{
        using From = value_pack2<short>;
        using Expect = value_pack<int>;
        using T = convert_to_value_pack<value_pack, int, From>;
        TEST_SAME(T::type, Expect);
        TEST_SAME(T::type, convert_to_value_pack_t<value_pack, int, From>);
    }{
        using From = value_pack2<short, 0, 1, 2>;
        using Expect = value_pack<int, 0, 1, 2>;
        using T = convert_to_value_pack<value_pack, int, From>;
        TEST_SAME(T::type, Expect);
        TEST_SAME(T::type, convert_to_value_pack_t<value_pack, int, From>);
    }
    BOOST_CHECK(true);
}

BOOST_AUTO_TEST_CASE(convert_to_tag_pack_test)
{
    {
        using From = param_pack<>;
        using Expect = tag();
        using T = convert_to_tag_pack<tag, From>;
        TEST_SAME(T::type, Expect);
        TEST_SAME(T::type, convert_to_tag_pack_t<tag, From>);
    }{
        using From = param_pack<int, long>;
        using Expect = tag(int, long);
        using T = convert_to_tag_pack<tag, From>;
        TEST_SAME(T::type, Expect);
        TEST_SAME(T::type, convert_to_tag_pack_t<tag, From>);
    }{
        using From = tag2();
        using Expect = tag();
        using T = convert_to_tag_pack<tag, From>;
        TEST_SAME(T::type, Expect);
        TEST_SAME(T::type, convert_to_tag_pack_t<tag, From>);
    }
    {
        using From = tag2(int, long);
        using Expect = tag(int, long);
        using T = convert_to_tag_pack<tag, From>;
        TEST_SAME(T::type, Expect);
        TEST_SAME(T::type, convert_to_tag_pack_t<tag, From>);
    }
    BOOST_CHECK(true);
}

BOOST_AUTO_TEST_CASE(size_test)
{
    {
        using T = param_pack<>;
        TEST_ASSERT(params::size<T>::value == 0);
        TEST_SAME(params::size<T>::type, params::size_t<T>);
    }{ 
        using T = void();
        TEST_ASSERT(params::size<T>::value == 0);
        TEST_SAME(params::size<T>::type, params::size_t<T>);
    }{
        using T = value_pack<int>;
        TEST_ASSERT(params::size<T>::value == 0);
        TEST_SAME(params::size<T>::type, params::size_t<T>);
    }{ 
        using T = param_pack<void, int, float>;
        TEST_ASSERT(params::size<T>::value == 3);
        TEST_SAME(params::size<T>::type, params::size_t<T>);
    }{
        using T = void(char, int, float);
        TEST_ASSERT(params::size<T>::value == 3);
        TEST_SAME(params::size<T>::type, params::size_t<T>);
    }{
        using T = value_pack<int, 1, 2, 3>;
        TEST_ASSERT(params::size<T>::value == 3);
        TEST_SAME(params::size<T>::type, params::size_t<T>);
    }
    BOOST_CHECK(true);
}

BOOST_AUTO_TEST_CASE(empty_test)
{
    {
        using T = param_pack<>;
        TEST_ASSERT(params::empty<T>::value == true);
        TEST_SAME(params::empty<T>::type, params::empty_t<T>);
    }{ 
        using T = void();
        TEST_ASSERT(params::empty<T>::value == true);
        TEST_SAME(params::empty<T>::type, params::empty_t<T>);
    }{
        using T = value_pack<int>;
        TEST_ASSERT(params::empty<T>::value == true);
        TEST_SAME(params::empty<T>::type, params::empty_t<T>);
    }{ 
        using T = param_pack<void, int, float>;
        TEST_ASSERT(params::empty<T>::value == false);
        TEST_SAME(params::empty<T>::type, params::empty_t<T>);
    }{
        using T = void(char, int, float);
        TEST_ASSERT(params::empty<T>::value == false);
        TEST_SAME(params::empty<T>::type, params::empty_t<T>);
    }{
        using T = value_pack<int, 1, 2, 3>;
        TEST_ASSERT(params::empty<T>::value == false);
        TEST_SAME(params::empty<T>::type, params::empty_t<T>);
    }
    BOOST_CHECK(true);
}

BOOST_AUTO_TEST_CASE(concat_types_test)
{
    {
        using P1 = param_pack<>;
        using P2 = param_pack2<>;
        using Expect = param_pack<>;
        using T = concat<P1, P2>;
        TEST_SAME(T::type, Expect);
        TEST_SAME(T::type, concat_t<P1, P2>);
    }{
        using P1 = param_pack<int>;
        using P2 = param_pack2<>;
        using Expect = param_pack<int>;
        using T = concat<P1, P2>;
        TEST_SAME(T::type, Expect);
        TEST_SAME(T::type, concat_t<P1, P2>);
    }{
        using P1 = param_pack<>;
        using P2 = param_pack2<int>;
        using Expect = param_pack<int>;
        using T = concat<P1, P2>;
        TEST_SAME(T::type, Expect);
        TEST_SAME(T::type, concat_t<P1, P2>);
    }{
        using P1 = param_pack<int>;
        using P2 = param_pack2<void>;
        using Expect = param_pack<int, void>;
        using T = concat<P1, P2>;
        TEST_SAME(T::type, Expect);
        TEST_SAME(T::type, concat_t<P1, P2>);
    }{
        using P1 = param_pack<>;
        using P2 = void();
        using Expect = param_pack<>;
        using T = concat<P1, P2>;
        TEST_SAME(T::type, Expect);
        TEST_SAME(T::type, concat_t<P1, P2>);
    }{
        using P1 = param_pack<int>;
        using P2 = void();
        using Expect = param_pack<int>;
        using T = concat<P1, P2>;
        TEST_SAME(T::type, Expect);
        TEST_SAME(T::type, concat_t<P1, P2>);
    }{
        using P1 = param_pack<>;
        using P2 = void(int);
        using Expect = param_pack<int>;
        using T = concat<P1, P2>;
        TEST_SAME(T::type, Expect);
        TEST_SAME(T::type, concat_t<P1, P2>);
    }{
        using P1 = param_pack<void>;
        using P2 = void(int);
        using Expect = param_pack<void, int>;
        using T = concat<P1, P2>;
        TEST_SAME(T::type, Expect);
        TEST_SAME(T::type, concat_t<P1, P2>);
    }{
        using P1 = void();
        using P2 = param_pack<>;
        using Expect = void();
        using T = concat<P1, P2>;
        TEST_SAME(T::type, Expect);
        TEST_SAME(T::type, concat_t<P1, P2>);
    }{
        using P1 = void(int);
        using P2 = param_pack<>;
        using Expect = void(int);
        using T = concat<P1, P2>;
        TEST_SAME(T::type, Expect);
        TEST_SAME(T::type, concat_t<P1, P2>);
    }{
        using P1 = void();
        using P2 = param_pack<int>;
        using Expect = void(int);
        using T = concat<P1, P2>;
        TEST_SAME(T::type, Expect);
        TEST_SAME(T::type, concat_t<P1, P2>);
    }{
        using P1 = void(int);
        using P2 = param_pack<long>;
        using Expect = void(int, long);
        using T = concat<P1, P2>;
        TEST_SAME(T::type, Expect);
        TEST_SAME(T::type, concat_t<P1, P2>);
    }{
        using P1 = void();
        using P2 = void();
        using Expect = void();
        using T = concat<P1, P2>;
        TEST_SAME(T::type, Expect);
        TEST_SAME(T::type, concat_t<P1, P2>);
    }{
        using P1 = void(int);
        using P2 = void();
        using Expect = void(int);
        using T = concat<P1, P2>;
        TEST_SAME(T::type, Expect);
        TEST_SAME(T::type, concat_t<P1, P2>);
    }{
        using P1 = void();
        using P2 = void(int);
        using Expect = void(int);
        using T = concat<P1, P2>;
        TEST_SAME(T::type, Expect);
        TEST_SAME(T::type, concat_t<P1, P2>);
    }{
        using P1 = void(int);
        using P2 = void(long);
        using Expect = void(int, long);
        using T = concat<P1, P2>;
        TEST_SAME(T::type, Expect);
        TEST_SAME(T::type, concat_t<P1, P2>);
    }
    BOOST_CHECK(true);
}

BOOST_AUTO_TEST_CASE(concat_values_test)
{
    {
        using P1 = value_pack<int>;
        using P2 = value_pack2<int>;
        using Expect = value_pack<int>;
        using T = concat<P1, P2>;
        TEST_SAME(T::type, Expect);
        TEST_SAME(T::type, concat_t<P1, P2>);
    }{
        using P1 = value_pack<int, 0>;
        using P2 = value_pack2<int>;
        using Expect = value_pack<int, 0>;
        using T = concat<P1, P2>;
        TEST_SAME(T::type, Expect);
        TEST_SAME(T::type, concat_t<P1, P2>);
    }{
        using P1 = value_pack<int>;
        using P2 = value_pack2<int, 0>;
        using Expect = value_pack<int, 0>;
        using T = concat<P1, P2>;
        TEST_SAME(T::type, Expect);
        TEST_SAME(T::type, concat_t<P1, P2>);
    }
    {
        using P1 = value_pack<int, 0>;
        using P2 = value_pack2<int, 1>;
        using Expect = value_pack<int, 0, 1>;
        using T = concat<P1, P2>;
        TEST_SAME(T::type, Expect);
        TEST_SAME(T::type, concat_t<P1, P2>);
    }
    BOOST_CHECK(true);
}

BOOST_AUTO_TEST_CASE(append_test)
{
    {
        using P1 = param_pack<>;
        using Expect = param_pack<>;
        using T = append<P1>;
        TEST_SAME(T::type, Expect);
        TEST_SAME(T::type, append_t<P1>);
    }{
        using P1 = param_pack<int>;
        using Expect = param_pack<int>;
        using T = append<P1>;
        TEST_SAME(T::type, Expect);
        TEST_SAME(T::type, append_t<P1>);
    }{
        using P1 = param_pack<>;
        using Expect = param_pack<int>;
        using T = append<P1, int>;
        TEST_SAME(T::type, Expect);
        TEST_SAME(T::type, append_t<P1, int>);
    }{
        using P1 = param_pack<int>;
        using Expect = param_pack<int, long>;
        using T = append<P1, long>;
        TEST_SAME(T::type, Expect);
        TEST_SAME(T::type, append_t<P1, long>);
    }{
        using P1 = param_pack<int, void>;
        using Expect = param_pack<int, void, long, char>;
        using T = append<P1, long, char>;
        TEST_SAME(T::type, Expect);
        TEST_SAME(T::type, append_t<P1, long, char>);
    }{
        using P1 = void();
        using Expect = void();
        using T = append<P1>;
        TEST_SAME(T::type, Expect);
        TEST_SAME(T::type, append_t<P1>);
    }{
        using P1 = void(int);
        using Expect = void(int);
        using T = append<P1>;
        TEST_SAME(T::type, Expect);
        TEST_SAME(T::type, append_t<P1>);
    }{
        using P1 = void();
        using Expect = void(int);
        using T = append<P1, int>;
        TEST_SAME(T::type, Expect);
        TEST_SAME(T::type, append_t<P1, int>);
    }{
        using P1 = void(int);
        using Expect = void(int, long);
        using T = append<P1, long>;
        TEST_SAME(T::type, Expect);
        TEST_SAME(T::type, append_t<P1, long>);
    }{
        using P1 = void(int, short);
        using Expect = void(int, short, long, char);
        using T = append<P1, long, char>;
        TEST_SAME(T::type, Expect);
        TEST_SAME(T::type, append_t<P1, long, char>);
    }
    BOOST_CHECK(true);
}

BOOST_AUTO_TEST_CASE(append_c_test)
{
    {
        using P1 = value_pack<int>;
        using Expect = value_pack<int>;
        using T = append_c<P1, int>;
        TEST_SAME(T::type, Expect);
        TEST_SAME(T::type, append_c_t<P1, int>);
    }{
        using P1 = value_pack<int, 0>;
        using Expect = value_pack<int, 0>;
        using T = append_c<P1, int>;
        TEST_SAME(T::type, Expect);
        TEST_SAME(T::type, append_c_t<P1, int>);
    }{
        using P1 = value_pack<int>;
        using Expect = value_pack<int, 0>;
        using T = append_c<P1, int, 0>;
        TEST_SAME(T::type, Expect);
        TEST_SAME(T::type, append_c_t<P1, int, 0>);
    }{
        using P1 = value_pack<int, 0>;
        using Expect = value_pack<int, 0, 1>;
        using T = append_c<P1, int, 1>;
        TEST_SAME(T::type, Expect);
        TEST_SAME(T::type, append_c_t<P1, int, 1>);
    }{
        using P1 = value_pack<int, 0>;
        using Expect = value_pack<int, 0, 1, 2>;
        using T = append_c<P1, int, 1, 2>;
        TEST_SAME(T::type, Expect);
        TEST_SAME(T::type, append_c_t<P1, int, 1, 2>);
    }
    BOOST_CHECK(true);
}


BOOST_AUTO_TEST_CASE(prepend_test)
{
    {
        using P1 = param_pack<>;
        using Expect = param_pack<>;
        using T = prepend<P1>;
        TEST_SAME(T::type, Expect);
        TEST_SAME(T::type, prepend_t<P1>);
    }{
        using P1 = param_pack<int>;
        using Expect = param_pack<int>;
        using T = prepend<P1>;
        TEST_SAME(T::type, Expect);
        TEST_SAME(T::type, prepend_t<P1>);
    }{
        using P1 = param_pack<>;
        using Expect = param_pack<int>;
        using T = prepend<P1, int>;
        TEST_SAME(T::type, Expect);
        TEST_SAME(T::type, prepend_t<P1, int>);
    }{
        using P1 = param_pack<int>;
        using Expect = param_pack<long, int>;
        using T = prepend<P1, long>;
        TEST_SAME(T::type, Expect);
        TEST_SAME(T::type, prepend_t<P1, long>);
    }{
        using P1 = param_pack<int, void>;
        using Expect = param_pack<long, char, int, void>;
        using T = prepend<P1, long, char>;
        TEST_SAME(T::type, Expect);
        TEST_SAME(T::type, prepend_t<P1, long, char>);
    }{
        using P1 = void();
        using Expect = void();
        using T = prepend<P1>;
        TEST_SAME(T::type, Expect);
        TEST_SAME(T::type, prepend_t<P1>);
    }{
        using P1 = void(int);
        using Expect = void(int);
        using T = prepend<P1>;
        TEST_SAME(T::type, Expect);
        TEST_SAME(T::type, prepend_t<P1>);
    }{
        using P1 = void();
        using Expect = void(int);
        using T = prepend<P1, int>;
        TEST_SAME(T::type, Expect);
        TEST_SAME(T::type, prepend_t<P1, int>);
    }{
        using P1 = void(int);
        using Expect = void(long, int);
        using T = prepend<P1, long>;
        TEST_SAME(T::type, Expect);
        TEST_SAME(T::type, prepend_t<P1, long>);
    }{
        using P1 = void(int, short);
        using Expect = void(long, char, int, short);
        using T = prepend<P1, long, char>;
        TEST_SAME(T::type, Expect);
        TEST_SAME(T::type, prepend_t<P1, long, char>);
    }
    BOOST_CHECK(true);
}

BOOST_AUTO_TEST_CASE(prepend_c_test)
{
    {
        using P1 = value_pack<int>;
        using Expect = value_pack<int>;
        using T = prepend_c<P1, int>;
        TEST_SAME(T::type, Expect);
        TEST_SAME(T::type, prepend_c_t<P1, int>);
    }{
        using P1 = value_pack<int, 0>;
        using Expect = value_pack<int, 0>;
        using T = prepend_c<P1, int>;
        TEST_SAME(T::type, Expect);
        TEST_SAME(T::type, prepend_c_t<P1, int>);
    }{
        using P1 = value_pack<int>;
        using Expect = value_pack<int, 0>;
        using T = prepend_c<P1, int, 0>;
        TEST_SAME(T::type, Expect);
        TEST_SAME(T::type, prepend_c_t<P1, int, 0>);
    }{
        using P1 = value_pack<int, 0>;
        using Expect = value_pack<int, 1, 0>;
        using T = prepend_c<P1, int, 1>;
        TEST_SAME(T::type, Expect);
        TEST_SAME(T::type, prepend_c_t<P1, int, 1>);
    }{
        using P1 = value_pack<int, 0>;
        using Expect = value_pack<int, 1, 2, 0>;
        using T = prepend_c<P1, int, 1, 2>;
        TEST_SAME(T::type, Expect);
        TEST_SAME(T::type, prepend_c_t<P1, int, 1, 2>);
    }
    BOOST_CHECK(true);
}

BOOST_AUTO_TEST_CASE(push_back_test)
{
    {
        using P1 = param_pack<>;
        using Expect = param_pack<int>;
        using T = push_back<P1, int>;
        TEST_SAME(T::type, Expect);
        TEST_SAME(T::type, push_back_t<P1, int>);
    }{
        using P1 = param_pack<int>;
        using Expect = param_pack<int, long>;
        using T = push_back<P1, long>;
        TEST_SAME(T::type, Expect);
        TEST_SAME(T::type, push_back_t<P1, long>);
    }{
        using P1 = void();
        using Expect = void(int);
        using T = push_back<P1, int>;
        TEST_SAME(T::type, Expect);
        TEST_SAME(T::type, push_back_t<P1, int>);
    }{
        using P1 = void(int);
        using Expect = void(int, long);
        using T = push_back<P1, long>;
        TEST_SAME(T::type, Expect);
        TEST_SAME(T::type, push_back_t<P1, long>);
    }
    BOOST_CHECK(true);
}

BOOST_AUTO_TEST_CASE(push_front_test)
{
    {
        using P1 = param_pack<>;
        using Expect = param_pack<int>;
        using T = push_front<P1, int>;
        TEST_SAME(T::type, Expect);
        TEST_SAME(T::type, push_front_t<P1, int>);
    }{
        using P1 = param_pack<int>;
        using Expect = param_pack<long, int>;
        using T = push_front<P1, long>;
        TEST_SAME(T::type, Expect);
        TEST_SAME(T::type, push_front_t<P1, long>);
    }{
        using P1 = void();
        using Expect = void(int);
        using T = push_front<P1, int>;
        TEST_SAME(T::type, Expect);
        TEST_SAME(T::type, push_front_t<P1, int>);
    }{
        using P1 = void(int);
        using Expect = void(long, int);
        using T = push_front<P1, long>;
        TEST_SAME(T::type, Expect);
        TEST_SAME(T::type, push_front_t<P1, long>);
    }
    BOOST_CHECK(true);
}

BOOST_AUTO_TEST_CASE(fill_test)
{
    {
        using Expect = param_pack<>;
        using T = fill<0, void, param_pack<> >;
        TEST_SAME(T::type, Expect);
        TEST_SAME(T::type, fill_t<0, void, param_pack<> >);
    }{
        using Expect = param_pack<void>;
        using T = fill<1, void, param_pack<> >;
        TEST_SAME(T::type, Expect);
        TEST_SAME(T::type, fill_t<1, void, param_pack<> >);
    }{
        using Expect = param_pack<void, void>;
        using T = fill<2, void, param_pack<> >;
        TEST_SAME(T::type, Expect);
        TEST_SAME(T::type, fill_t<2, void, param_pack<> >);
    }{
        using Expect = param_pack<void, void, void>;
        using T = fill<3, void, param_pack<> >;
        TEST_SAME(T::type, Expect);
        TEST_SAME(T::type, fill_t<3, void, param_pack<> >);
    }{
        using Expect = param_pack<void, void, void, void>;
        using T = fill<4, void, param_pack<> >;
        TEST_SAME(T::type, Expect);
        TEST_SAME(T::type, fill_t<4, void, param_pack<> >);
    }{
        using Expect = param_pack<void, void, void, void, void>;
        using T = fill<5, void, param_pack<> >;
        TEST_SAME(T::type, Expect);
        TEST_SAME(T::type, fill_t<5, void, param_pack<> >);
    }{
        using Expect = tag();
        using T = fill<0, int, tag()>;
        TEST_SAME(T::type, Expect);
        TEST_SAME(T::type, fill_t<0, int, tag()>);
    }{
        using Expect = tag(int);
        using T = fill<1, int, tag()>;
        TEST_SAME(T::type, Expect);
        TEST_SAME(T::type, fill_t<1, int, tag()>);
    }{
        using Expect = tag(int, int);
        using T = fill<2, int, tag()>;
        TEST_SAME(T::type, Expect);
        TEST_SAME(T::type, fill_t<2, int, tag()>);
    }{
        using Expect = tag(int, int, int);
        using T = fill<3, int, tag()>;
        TEST_SAME(T::type, Expect);
        TEST_SAME(T::type, fill_t<3, int, tag()>);
    }{
        using Expect = tag(int, int, int, int);
        using T = fill<4, int, tag()>;
        TEST_SAME(T::type, Expect);
        TEST_SAME(T::type, fill_t<4, int, tag()>);
    }{
        using Expect = tag(int, int, int, int, int);
        using T = fill<5, int, tag()>;
        TEST_SAME(T::type, Expect);
        TEST_SAME(T::type, fill_t<5, int, tag()>);
    }
    BOOST_CHECK(true);
}

BOOST_AUTO_TEST_CASE(at_test)
{
    {
        using P = param_pack<void, int, long>;
        using Expect = void;
        using T = at<P, 0>;
        TEST_SAME(T::type, Expect);
        TEST_SAME(T::type, at_t<P, 0>);
    }{
        using P = param_pack<void, int, long>;
        using Expect = int;
        using T = at<P, 1>;
        TEST_SAME(T::type, Expect);
        TEST_SAME(T::type, at_t<P, 1>);
    }{
        using P = param_pack<void, int, long>;
        using Expect = long;
        using T = at<P, 2>;
        TEST_SAME(T::type, Expect);
        TEST_SAME(T::type, at_t<P, 2>);
    }{
        using P = tag(char, int, long);
        using Expect = char;
        using T = at<P, 0>;
        TEST_SAME(T::type, Expect);
        TEST_SAME(T::type, at_t<P, 0>);
    }{
        using P = tag(char, int, long);
        using Expect = int;
        using T = at<P, 1>;
        TEST_SAME(T::type, Expect);
        TEST_SAME(T::type, at_t<P, 1>);
    }{
        using P = tag(char, int, long);
        using Expect = long;
        using T = at<P, 2>;
        TEST_SAME(T::type, Expect);
        TEST_SAME(T::type, at_t<P, 2>);
    }{
        using P = value_pack<int, 0, 1, 2>;
        using Expect = int_<0>;
        using T = at<P, Expect::value>;
        TEST_SAME(T::type, Expect);
        TEST_SAME(T::type, at_t<P, Expect::value>);
    }{
        using P = value_pack<int, 0, 1, 2>;
        using Expect = int_<1>;
        using T = at<P, Expect::value>;
        TEST_SAME(T::type, Expect);
        TEST_SAME(T::type, at_t<P, Expect::value>);
    }{
        using P = value_pack<int, 0, 1, 2>;
        using Expect = int_<2>;
        using T = at<P, Expect::value>;
        TEST_SAME(T::type, Expect);
        TEST_SAME(T::type, at_t<P, Expect::value>);
    }
    BOOST_CHECK(true);
}

BOOST_AUTO_TEST_CASE(front_back_test)
{
    {
        using P = param_pack<char, int, long>;
        using FrontE = char;
        using BackE = long;
        using FT = front<P>;
        using BT = back<P>;
        TEST_SAME(FT::type, FrontE);
        TEST_SAME(FT::type, front_t<P>);
        TEST_SAME(BT::type, BackE);
        TEST_SAME(BT::type, back_t<P>);
    }{
        using P = tag(char, int, long);
        using FrontE = char;
        using BackE = long;
        using FT = front<P>;
        using BT = back<P>;
        TEST_SAME(FT::type, FrontE);
        TEST_SAME(FT::type, front_t<P>);
        TEST_SAME(BT::type, BackE);
        TEST_SAME(BT::type, back_t<P>);
    }{
        using P = value_pack<int, 0, 1, 2>;
        using FrontE = int_<0>;
        using BackE = int_<2>;
        using FT = front<P>;
        using BT = back<P>;
        TEST_SAME(FT::type, FrontE);
        TEST_SAME(FT::type, front_t<P>);
        TEST_SAME(BT::type, BackE);
        TEST_SAME(BT::type, back_t<P>);
    }
    BOOST_CHECK(true);
}

BOOST_AUTO_TEST_CASE(take_test)
{
    {
        using P = param_pack<>;
        constexpr std::size_t I = 0;
        using E = param_pack<>;
        using T = take<P, I>;
        TEST_SAME(T::type, E);
        TEST_SAME(T::type, take_t<P, I>);
    }{
        using P = param_pack<int>;
        constexpr std::size_t I = 0;
        using E = param_pack<>;
        using T = take<P, I>;
        TEST_SAME(T::type, E);
        TEST_SAME(T::type, take_t<P, I>);
    }
    {
        using P = param_pack<int>;
        constexpr std::size_t I = 1;
        using E = param_pack<int>;
        using T = take<P, I>;
        TEST_SAME(T::type, E);
        TEST_SAME(T::type, take_t<P, I>);
    }{
        using P = param_pack<int, long>;
        constexpr std::size_t I = 1;
        using E = param_pack<int>;
        using T = take<P, I>;
        TEST_SAME(T::type, E);
        TEST_SAME(T::type, take_t<P, I>);
    }{
        using P = param_pack<int, long, char>;
        constexpr std::size_t I = 3;
        using E = param_pack<int, long, char>;
        using T = take<P, I>;
        TEST_SAME(T::type, E);
        TEST_SAME(T::type, take_t<P, I>);
    }
    
    {
        using P = tag();
        constexpr std::size_t I = 0;
        using E = tag();
        using T = take<P, I>;
        TEST_SAME(T::type, E);
        TEST_SAME(T::type, take_t<P, I>);
    }{
        using P = tag(int);
        constexpr std::size_t I = 0;
        using E = tag();
        using T = take<P, I>;
        TEST_SAME(T::type, E);
        TEST_SAME(T::type, take_t<P, I>);
    }{
        using P = tag(int);
        constexpr std::size_t I = 1;
        using E = tag(int);
        using T = take<P, I>;
        TEST_SAME(T::type, E);
        TEST_SAME(T::type, take_t<P, I>);
    }{
        using P = tag(int, long);
        constexpr std::size_t I = 1;
        using E = tag(int);
        using T = take<P, I>;
        TEST_SAME(T::type, E);
        TEST_SAME(T::type, take_t<P, I>);
    }{
        using P = tag(int, long, char);
        constexpr std::size_t I = 3;
        using E = tag(int, long, char);
        using T = take<P, I>;
        TEST_SAME(T::type, E);
        TEST_SAME(T::type, take_t<P, I>);
    }
    
    {
        using P = value_pack<int>;
        constexpr std::size_t I = 0;
        using E = value_pack<int>;
        using T = take<P, I>;
        TEST_SAME(T::type, E);
        TEST_SAME(T::type, take_t<P, I>);
    }{
        using P = value_pack<int, 0>;
        constexpr std::size_t I = 0;
        using E = value_pack<int>;
        using T = take<P, I>;
        TEST_SAME(T::type, E);
        TEST_SAME(T::type, take_t<P, I>);
    }{
        using P = value_pack<int ,0>;
        constexpr std::size_t I = 1;
        using E = value_pack<int, 0>;
        using T = take<P, I>;
        TEST_SAME(T::type, E);
        TEST_SAME(T::type, take_t<P, I>);
    }{
        using P = value_pack<int, 0, 1>;
        constexpr std::size_t I = 1;
        using E = value_pack<int, 0>;
        using T = take<P, I>;
        TEST_SAME(T::type, E);
        TEST_SAME(T::type, take_t<P, I>);
    }{
        using P = value_pack<int, 0, 1, 2>;
        constexpr std::size_t I = 3;
        using E = value_pack<int, 0, 1, 2>;
        using T = take<P, I>;
        TEST_SAME(T::type, E);
        TEST_SAME(T::type, take_t<P, I>);
    }
    BOOST_CHECK(true);
}

BOOST_AUTO_TEST_CASE(drop_test)
{
    {
        using P = param_pack<>;
        constexpr std::size_t I = 0;
        using E = param_pack<>;
        using T = drop<P, I>;
        TEST_SAME(T::type, E);
        TEST_SAME(T::type, drop_t<P, I>);
    }{
        using P = param_pack<int>;
        constexpr std::size_t I = 0;
        using E = param_pack<int>;
        using T = drop<P, I>;
        TEST_SAME(T::type, E);
        TEST_SAME(T::type, drop_t<P, I>);
    }
    {
        using P = param_pack<int>;
        constexpr std::size_t I = 1;
        using E = param_pack<>;
        using T = drop<P, I>;
        TEST_SAME(T::type, E);
        TEST_SAME(T::type, drop_t<P, I>);
    }{
        using P = param_pack<int, long>;
        constexpr std::size_t I = 1;
        using E = param_pack<long>;
        using T = drop<P, I>;
        TEST_SAME(T::type, E);
        TEST_SAME(T::type, drop_t<P, I>);
    }{
        using P = param_pack<int, long, char>;
        constexpr std::size_t I = 3;
        using E = param_pack<>;
        using T = drop<P, I>;
        TEST_SAME(T::type, E);
        TEST_SAME(T::type, drop_t<P, I>);
    }
    
    {
        using P = tag();
        constexpr std::size_t I = 0;
        using E = tag();
        using T = drop<P, I>;
        TEST_SAME(T::type, E);
        TEST_SAME(T::type, drop_t<P, I>);
    }{
        using P = tag(int);
        constexpr std::size_t I = 0;
        using E = tag(int);
        using T = drop<P, I>;
        TEST_SAME(T::type, E);
        TEST_SAME(T::type, drop_t<P, I>);
    }{
        using P = tag(int);
        constexpr std::size_t I = 1;
        using E = tag();
        using T = drop<P, I>;
        TEST_SAME(T::type, E);
        TEST_SAME(T::type, drop_t<P, I>);
    }{
        using P = tag(int, long);
        constexpr std::size_t I = 1;
        using E = tag(long);
        using T = drop<P, I>;
        TEST_SAME(T::type, E);
        TEST_SAME(T::type, drop_t<P, I>);
    }{
        using P = tag(int, long, char);
        constexpr std::size_t I = 3;
        using E = tag();
        using T = drop<P, I>;
        TEST_SAME(T::type, E);
        TEST_SAME(T::type, drop_t<P, I>);
    }
    
    {
        using P = value_pack<int>;
        constexpr std::size_t I = 0;
        using E = value_pack<int>;
        using T = drop<P, I>;
        TEST_SAME(T::type, E);
        TEST_SAME(T::type, drop_t<P, I>);
    }{
        using P = value_pack<int, 0>;
        constexpr std::size_t I = 0;
        using E = value_pack<int, 0>;
        using T = drop<P, I>;
        TEST_SAME(T::type, E);
        TEST_SAME(T::type, drop_t<P, I>);
    }{
        using P = value_pack<int ,0>;
        constexpr std::size_t I = 1;
        using E = value_pack<int>;
        using T = drop<P, I>;
        TEST_SAME(T::type, E);
        TEST_SAME(T::type, drop_t<P, I>);
    }{
        using P = value_pack<int, 0, 1>;
        constexpr std::size_t I = 1;
        using E = value_pack<int, 1>;
        using T = drop<P, I>;
        TEST_SAME(T::type, E);
        TEST_SAME(T::type, drop_t<P, I>);
    }{
        using P = value_pack<int, 0, 1, 2>;
        constexpr std::size_t I = 3;
        using E = value_pack<int>;
        using T = drop<P, I>;
        TEST_SAME(T::type, E);
        TEST_SAME(T::type, drop_t<P, I>);
    }
    BOOST_CHECK(true);
}

BOOST_AUTO_TEST_CASE(pop_front_test)
{
    {
        using P = param_pack<int>;
        using E = param_pack<>;
        using T = pop_front<P>;
        TEST_SAME(T::type, E);
        TEST_SAME(T::type, pop_front_t<P>);
    }{
        using P = param_pack<int, long>;
        using E = param_pack<long>;
        using T = pop_front<P>;
        TEST_SAME(T::type, E);
        TEST_SAME(T::type, pop_front_t<P>);
    }{
        using P = tag(int);
        using E = tag();
        using T = pop_front<P>;
        TEST_SAME(T::type, E);
        TEST_SAME(T::type, pop_front_t<P>);
    }{
        using P = tag(int, long);
        using E = tag(long);
        using T = pop_front<P>;
        TEST_SAME(T::type, E);
        TEST_SAME(T::type, pop_front_t<P>);
    }{
        using P = value_pack<int, 0>;
        using E = value_pack<int>;
        using T = pop_front<P>;
        TEST_SAME(T::type, E);
        TEST_SAME(T::type, pop_front_t<P>);
    }{
        using P = value_pack<int, 0, 1>;
        using E = value_pack<int, 1>;
        using T = pop_front<P>;
        TEST_SAME(T::type, E);
        TEST_SAME(T::type, pop_front_t<P>);
    }
    BOOST_CHECK(true);
}

BOOST_AUTO_TEST_CASE(pop_back_test)
{
    {
        using P = param_pack<int>;
        using E = param_pack<>;
        using T = pop_back<P>;
        TEST_SAME(T::type, E);
        TEST_SAME(T::type, pop_back_t<P>);
    }{
        using P = param_pack<int, long>;
        using E = param_pack<int>;
        using T = pop_back<P>;
        TEST_SAME(T::type, E);
        TEST_SAME(T::type, pop_back_t<P>);
    }{
        using P = tag(int);
        using E = tag();
        using T = pop_back<P>;
        TEST_SAME(T::type, E);
        TEST_SAME(T::type, pop_back_t<P>);
    }{
        using P = tag(int, long);
        using E = tag(int);
        using T = pop_back<P>;
        TEST_SAME(T::type, E);
        TEST_SAME(T::type, pop_back_t<P>);
    }{
        using P = value_pack<int, 0>;
        using E = value_pack<int>;
        using T = pop_back<P>;
        TEST_SAME(T::type, E);
        TEST_SAME(T::type, pop_back_t<P>);
    }{
        using P = value_pack<int, 0, 1>;
        using E = value_pack<int, 0>;
        using T = pop_back<P>;
        TEST_SAME(T::type, E);
        TEST_SAME(T::type, pop_back_t<P>);
    }
    BOOST_CHECK(true);
}

BOOST_AUTO_TEST_CASE(slice_test)
{
    {
        using P = param_pack<int>;
        using E = param_pack<>;
        using Start = int_<0>;
        using End = int_<0>;
        using T = slice<P, Start::value, End::value>;
        TEST_SAME(T::type, E);
        TEST_SAME(T::type, slice_t<P, Start::value, End::value>);
    }{
        using P = param_pack<int>;
        using E = param_pack<int>;
        using Start = int_<0>;
        using End = int_<1>;
        using T = slice<P, Start::value, End::value>;
        TEST_SAME(T::type, E);
        TEST_SAME(T::type, slice_t<P, Start::value, End::value>);
    }{
        using P = param_pack<int, long>;
        using E = param_pack<int>;
        using Start = int_<0>;
        using End = int_<1>;
        using T = slice<P, Start::value, End::value>;
        TEST_SAME(T::type, E);
        TEST_SAME(T::type, slice_t<P, Start::value, End::value>);
    }{
        using P = param_pack<int, long>;
        using E = param_pack<long>;
        using Start = int_<1>;
        using End = int_<2>;
        using T = slice<P, Start::value, End::value>;
        TEST_SAME(T::type, E);
        TEST_SAME(T::type, slice_t<P, Start::value, End::value>);
    }{
        using P = param_pack<int, long>;
        using E = param_pack<>;
        using Start = int_<2>;
        using End = int_<2>;
        using T = slice<P, Start::value, End::value>;
        TEST_SAME(T::type, E);
        TEST_SAME(T::type, slice_t<P, Start::value, End::value>);
    }
    
    {
        using P = tag(int);
        using E = tag();
        using Start = int_<0>;
        using End = int_<0>;
        using T = slice<P, Start::value, End::value>;
        TEST_SAME(T::type, E);
        TEST_SAME(T::type, slice_t<P, Start::value, End::value>);
    }{
        using P = tag(int);
        using E = tag(int);
        using Start = int_<0>;
        using End = int_<1>;
        using T = slice<P, Start::value, End::value>;
        TEST_SAME(T::type, E);
        TEST_SAME(T::type, slice_t<P, Start::value, End::value>);
    }{
        using P = tag(int, long);
        using E = tag(int);
        using Start = int_<0>;
        using End = int_<1>;
        using T = slice<P, Start::value, End::value>;
        TEST_SAME(T::type, E);
        TEST_SAME(T::type, slice_t<P, Start::value, End::value>);
    }{
        using P = tag(int, long);
        using E = tag(long);
        using Start = int_<1>;
        using End = int_<2>;
        using T = slice<P, Start::value, End::value>;
        TEST_SAME(T::type, E);
        TEST_SAME(T::type, slice_t<P, Start::value, End::value>);
    }{
        using P = tag(int, long);
        using E = tag();
        using Start = int_<2>;
        using End = int_<2>;
        using T = slice<P, Start::value, End::value>;
        TEST_SAME(T::type, E);
        TEST_SAME(T::type, slice_t<P, Start::value, End::value>);
    }{
        using P = value_pack<int>;
        using E = value_pack<int>;
        using Start = int_<0>;
        using End = int_<0>;
        using T = slice<P, Start::value, End::value>;
        TEST_SAME(T::type, E);
        TEST_SAME(T::type, slice_t<P, Start::value, End::value>);
    }{
        using P = value_pack<int, 0>;
        using E = value_pack<int, 0>;
        using Start = int_<0>;
        using End = int_<1>;
        using T = slice<P, Start::value, End::value>;
        TEST_SAME(T::type, E);
        TEST_SAME(T::type, slice_t<P, Start::value, End::value>);
    }{
        using P = value_pack<int, 0, 1>;
        using E = value_pack<int, 0>;
        using Start = int_<0>;
        using End = int_<1>;
        using T = slice<P, Start::value, End::value>;
        TEST_SAME(T::type, E);
        TEST_SAME(T::type, slice_t<P, Start::value, End::value>);
    }{
        using P = value_pack<int, 0, 1>;
        using E = value_pack<int, 1>;
        using Start = int_<1>;
        using End = int_<2>;
        using T = slice<P, Start::value, End::value>;
        TEST_SAME(T::type, E);
        TEST_SAME(T::type, slice_t<P, Start::value, End::value>);
    }{
        using P = value_pack<int, 0, 1>;
        using E = value_pack<int>;
        using Start = int_<2>;
        using End = int_<2>;
        using T = slice<P, Start::value, End::value>;
        TEST_SAME(T::type, E);
        TEST_SAME(T::type, slice_t<P, Start::value, End::value>);
    }
    BOOST_CHECK(true);
}

BOOST_AUTO_TEST_SUITE_END()