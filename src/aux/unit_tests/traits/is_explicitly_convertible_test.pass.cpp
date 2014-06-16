// REQUIRES: ELIB_AUX_SOURCE
#include <elib/aux/traits/is_explicitly_convertible.hpp>
#include <elib/aux/traits/is_convertible.hpp>
#include "rapid-cxx-test.hpp"
using namespace elib::aux;

struct To;

struct from_explicit_construct {};
struct from_implicit_construct {};

struct To {
    To() {}
    explicit To(from_explicit_construct) {}
    To(from_implicit_construct) {}
};

struct from_implicit_conversion
{
    operator To() { return {}; }
};

struct from_explicit_conversion
{
    explicit operator To() const { return {}; }
};

struct not_castable {};

TEST_SUITE(elib_aux_traits_is_explicitly_convertible_test_suite)

TEST_CASE(is_explicitly_convertible_test)
{
    TEST_STATIC_ASSERT(is_explicitly_convertible<from_explicit_construct, To>::value);
    TEST_STATIC_ASSERT(is_explicitly_convertible<from_implicit_construct, To>::value);
    TEST_STATIC_ASSERT(is_explicitly_convertible<from_implicit_conversion, To>::value);
    TEST_STATIC_ASSERT(is_explicitly_convertible<from_explicit_conversion, To>::value);
    TEST_STATIC_ASSERT(not is_explicitly_convertible<not_castable, To>::value);
    TEST_STATIC_ASSERT(not is_explicitly_convertible<int, To>::value);
    TEST_STATIC_ASSERT(not is_explicitly_convertible<void, To>::value);
}

TEST_CASE(is_convertible_test)
{
    TEST_STATIC_ASSERT(is_convertible<from_implicit_construct, To>::value);
    TEST_STATIC_ASSERT(not is_convertible<from_explicit_construct, To>::value);
    TEST_STATIC_ASSERT(is_convertible<from_implicit_conversion, To>::value);
    TEST_STATIC_ASSERT(not is_convertible<from_explicit_conversion, To>::value);
    TEST_STATIC_ASSERT(not is_convertible<not_castable, To>::value);
    TEST_STATIC_ASSERT(not is_convertible<int, To>::value);
    TEST_STATIC_ASSERT(not is_convertible<void, To>::value);
}


TEST_SUITE_END()