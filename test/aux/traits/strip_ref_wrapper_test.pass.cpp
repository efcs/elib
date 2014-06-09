#define BOOST_TEST_MODULE Main
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include <elib/aux/traits/strip_ref_wrapper.hpp>
#include <elib/aux/traits/is_same.hpp>
#include <elib/aux/static_assert.hpp>
#include <functional>

using namespace elib::aux;

#define CHECK_SAME(...) ELIB_STATIC_ASSERT(is_same<__VA_ARGS__>::value)

struct class_type {};

BOOST_AUTO_TEST_SUITE(elib_aux_traits_strip_ref_wrapper_test_suite)

BOOST_AUTO_TEST_CASE(non_ref_wrapper_test)
{
    CHECK_SAME(strip_ref_wrapper_t<void>, void);
    CHECK_SAME(strip_ref_wrapper_t<int>, int);
    CHECK_SAME(strip_ref_wrapper_t<int*>, int*);
    CHECK_SAME(strip_ref_wrapper_t<int[]>, int[]);
    CHECK_SAME(strip_ref_wrapper_t<int[5]>, int[5]);
    CHECK_SAME(strip_ref_wrapper_t<int()>, int());
    CHECK_SAME(strip_ref_wrapper_t<int(&)()>, int(&)());
    CHECK_SAME(strip_ref_wrapper_t<int(*)()>, int(*)());
    CHECK_SAME(
        strip_ref_wrapper_t<void(class_type::*)(int, long)>
      , void(class_type::*)(int, long)
      );
    BOOST_CHECK(true);
}

BOOST_AUTO_TEST_CASE(ref_wrapper_test)
{
    {
        using R = std::reference_wrapper<int>;
        using E = int &;
        CHECK_SAME(strip_ref_wrapper_t<R>, E);
    }
    {
        using R = std::reference_wrapper<int> &;
        using E = std::reference_wrapper<int> &;
        CHECK_SAME(strip_ref_wrapper_t<R>, E);
    }
    BOOST_CHECK(true);
}

BOOST_AUTO_TEST_SUITE_END()