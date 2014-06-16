// REQUIRES: ELIB_AUX_SOURCE
#include <elib/aux/make_array.hpp>
#include <elib/aux/traits/is_same.hpp>
#include <array>
#include <functional>
#include "rapid-cxx-test.hpp"

using namespace elib;
using namespace elib::aux;


TEST_SUITE(elib_aux_make_array_test_suite)

TEST_CASE(make_array_int_test)
{
    using Expect = std::array<int, 3>;
    using Got = decltype(make_array(0, 1, 2));
    static_assert(is_same<Expect, Got>::value, "must be same");
    
    auto a = make_array(0, 1, 2);
    TEST_CHECK(a[0] == 0);
    TEST_CHECK(a[1] == 1);
    TEST_CHECK(a[2] == 2);
}

TEST_CASE(make_array_common_type_test)
{
    using Expect = std::array<unsigned, 3>;
    using Got = decltype(make_array('\0', 1, 2u));
    static_assert(is_same<Expect, Got>::value, "must be same");
    
    auto a = make_array('\0', 1, 2u);
    TEST_CHECK(a[0] == 0);
    TEST_CHECK(a[1] == 1);
    TEST_CHECK(a[2] == 2);
}

TEST_CASE(make_array_specify_type)
{
    using Expect = std::array<char, 3>;
    using Got = decltype(make_array<char>(0, 1u, 2ul));
    static_assert(is_same<Expect, Got>::value, "must be same");
    
    auto a = make_array<char>(0, 1u, 2ul);
    TEST_CHECK(a[0] == 0);
    TEST_CHECK(a[1] == 1);
    TEST_CHECK(a[2] == 2);
}

TEST_CASE(make_array_specify_type_ref_wrapper)
{
    int x = 0, y = 1, z = 2;
    auto a = make_array<int>(std::ref(x), std::ref(y), std::ref(z));
    
    using Expect = std::array<int, 3>;
    using Got = decltype(a);
    static_assert(is_same<Expect, Got>::value, "must be same");
    
    TEST_CHECK(a[0] == 0);
    TEST_CHECK(a[1] == 1);
    TEST_CHECK(a[2] == 2);
}

TEST_CASE(to_array_test)
{
    int arr[3] = {0, 1, 2};
    auto a = to_array(arr);
    
    using Expect = std::array<int, 3>;
    using Got = decltype(a);
    static_assert(is_same<Expect, Got>::value, "must be same");
    
    TEST_CHECK(a[0] == 0);
    TEST_CHECK(a[1] == 1);
    TEST_CHECK(a[2] == 2);
}

TEST_SUITE_END()