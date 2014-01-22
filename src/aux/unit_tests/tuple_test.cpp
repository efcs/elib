#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include "elib/aux.hpp"
#include "elib/pair.hpp"
#include "elib/tuple.hpp"
#include <utility>
#include <tuple>
#include <string>

using namespace elib;
using namespace elib::aux;

#define CHECK(...) BOOST_CHECK((__VA_ARGS__))
#define SAME_TYPE(...) BOOST_CHECK(( is_same<__VA_ARGS__>::value ))

#define CHECK_SIZE(i, ...) BOOST_CHECK((i == tuple_size<__VA_ARGS__>()))
#define CHECK_ELEM(i, e, ...) SAME_TYPE(e, tuple_element_t<i, __VA_ARGS__>)
#define CHECK_ID(i, e, ...) BOOST_CHECK((i == tuple_element_index_t<e, __VA_ARGS__>()))

#define IS_REF(...) is_ref<decltype(__VA_ARGS__)>()
#define IS_LVALUE_REF(...) is_lvalue_reference<decltype(__VA_ARGS__)>()
#define IS_RVALUE_REF(...) is_rvalue_reference<decltype(__VA_ARGS__)>()
#define IS_PTR(...) is_ptr<decltype(__VA_ARGS__)>()
#define IS_VALUE(...) (!IS_REF(__VA_ARGS__) && !IS_PTR(__VA_ARGS__))

#define IS_CONST(...) is_const<decltype(__VA_ARGS__)>()
#define IS_VOLATILE(...) is_volatile<decltype(__VA_ARGS__)>()
#define IS_CV(...) (IS_CONST(__VA_ARGS__) && IS_VOLATILE(__VA_ARGS__))

#define IS_CONST_REF(...) (IS_REF(__VA_ARGS__) && is_const<remove_ref_t<decltype(__VA_ARGS__)>>())
#define IS_CONST_PTR(...) (IS_PTR(__VA_ARGS__) && is_const<remove_ptr_t<decltype(__VA_ARGS__)>>())
#define IS_SAME(t, ...) SAME_TYPE(t, decltype(__VA_ARGS__))

BOOST_AUTO_TEST_SUITE(aux_tuple_test_suite)

BOOST_AUTO_TEST_CASE(aux_tuple_size_test)
{
    CHECK_SIZE(2, pair<int, int>);
    CHECK_SIZE(2, std::pair<int, int>);
    CHECK_SIZE(0, tuple<>);
    CHECK_SIZE(0, std::tuple<>);
    CHECK_SIZE(1, tuple<int>);
    CHECK_SIZE(1, std::tuple<int>);
    CHECK_SIZE(2, tuple<int, long>);
    CHECK_SIZE(2, const tuple<int, long>);
    CHECK_SIZE(2, volatile tuple<int, long>);
    CHECK_SIZE(2, const volatile tuple<int, long>);
    CHECK_SIZE(3, const volatile tuple<int, long, char>&);
}

BOOST_AUTO_TEST_CASE(aux_tuple_element_test)
{
    CHECK_ELEM(0, int, pair<int, void>);
    CHECK_ELEM(1, int, pair<void, int>);
    CHECK_ELEM(0, int, std::pair<int, void>);
    CHECK_ELEM(1, int, std::pair<void, int>);
    CHECK_ELEM(0, int, tuple<int, void, void>);
    CHECK_ELEM(1, int, tuple<void, int, void>);
    CHECK_ELEM(2, int, tuple<void, void, int>);
    CHECK_ELEM(0, const volatile int, const volatile pair<int, void>);
    CHECK_ELEM(0, const volatile int, const volatile std::pair<int, void>);
    CHECK_ELEM(1, const int, const tuple<void, int>);
    CHECK_ELEM(2, volatile int, volatile tuple<long, long, int>);
}

BOOST_AUTO_TEST_CASE(aux_tuple_element_index_test)
{
    CHECK_ID(0, int, pair<int, void>);
    CHECK_ID(1, char, pair<int, char>);
    CHECK_ID(0, long, std::pair<long, void>);
    CHECK_ID(1, int, std::pair<long, int>);
    CHECK_ID(0, int, tuple<int, long, char>);
    CHECK_ID(1, std::string, tuple<int, std::string, long>);
    CHECK_ID(2, char, tuple<int, long, char>);
}

BOOST_AUTO_TEST_CASE(aux_pair_get_test)
{
    int x;
    pair<int&, std::string> p{x, ""};
    CHECK(&x == &get<0>(p));
    CHECK(&x == &get<int&>(p));
    CHECK(&get<1>(p) == &get<std::string>(p));
    
    CHECK( IS_LVALUE_REF(get<0>(p)) && IS_LVALUE_REF(get<int&>(p)));
    CHECK( IS_LVALUE_REF(get<1>(p)) && IS_LVALUE_REF(get<std::string>(p)));
    CHECK( !IS_CONST(get<0>(p)) && !IS_CONST(get<1>(p)));
    
    const pair<long, void*> cp{};
    IS_SAME(long const&, get<0>(cp));
    IS_SAME(void* const&, get<1>(cp));
    
    const pair<std::string, const int&> ct2{"", x};
    IS_SAME(std::string const&, get<0>(ct2));
    
    IS_SAME(std::string&&, get<1>(std::move(p)));
}

BOOST_AUTO_TEST_CASE(aux_tuple_get_test)
{
    int x{};
    tuple<int&, void*, std::string> t{x, nullptr, "Hello"};
    IS_SAME(int&, get<0>(t));
    IS_SAME(void*&, get<1>(t));
    IS_SAME(std::string&, get<2>(t));
    
    const int cx{};
    const tuple<const int&, void*, std::string> ct{cx};
    IS_SAME(int const&, get<0>(ct));
    IS_SAME(void* const&, get<1>(ct));
    IS_SAME(std::string const&, get<std::string>(ct));
    
    IS_SAME(std::string&&, get<std::string>(std::move(t)));
}

BOOST_AUTO_TEST_CASE(aux_pair_ctor_test)
{
    pair<int, int> t;
    CHECK(get<0>(t) == 0 && get<1>(t) == 0);
    
    int x{};
    const int cx{};
    pair<int&, const int&> t2{x, cx};
}

BOOST_AUTO_TEST_SUITE_END()