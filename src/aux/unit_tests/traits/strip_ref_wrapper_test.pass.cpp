// REQUIRES: ELIB_AUX
#include <elib/aux/traits/strip_ref_wrapper.hpp>
#include <functional>
#include "rapid-cxx-test.hpp"

using namespace elib::aux;

struct class_type {};

TEST_SUITE(elib_aux_traits_strip_ref_wrapper_test_suite)

TEST_CASE(non_ref_wrapper_test)
{
    TEST_SAME_TYPE(strip_ref_wrapper_t<void>, void);
    TEST_SAME_TYPE(strip_ref_wrapper_t<int>, int);
    TEST_SAME_TYPE(strip_ref_wrapper_t<int*>, int*);
    TEST_SAME_TYPE(strip_ref_wrapper_t<int[]>, int[]);
    TEST_SAME_TYPE(strip_ref_wrapper_t<int[5]>, int[5]);
    TEST_SAME_TYPE(strip_ref_wrapper_t<int()>, int());
    TEST_SAME_TYPE(strip_ref_wrapper_t<int(&)()>, int(&)());
    TEST_SAME_TYPE(strip_ref_wrapper_t<int(*)()>, int(*)());
    TEST_SAME_TYPE(
        strip_ref_wrapper_t<void(class_type::*)(int, long)>
      , void(class_type::*)(int, long)
      );
}

TEST_CASE(ref_wrapper_test)
{
    {
        using R = std::reference_wrapper<int>;
        using E = int &;
        TEST_SAME_TYPE(strip_ref_wrapper_t<R>, E);
    }
    {
        using R = std::reference_wrapper<int> &;
        using E = std::reference_wrapper<int> &;
        TEST_SAME_TYPE(strip_ref_wrapper_t<R>, E);
    }
}

TEST_SUITE_END()