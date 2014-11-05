// REQUIRES: ELIB_AUX
#include <elib/aux/traits/has_explicit_conversion.hpp>
#include <elib/aux/traits/has_implicit_conversion.hpp>
#include <elib/aux/traits/has_conversion.hpp>
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

TEST_CASE(has_explicit_conversion_test)
{
    TEST_STATIC_ASSERT(has_explicit_conversion<from_explicit_construct, To>::value);
    TEST_STATIC_ASSERT(not has_explicit_conversion<from_implicit_construct, To>::value);
    TEST_STATIC_ASSERT(not has_explicit_conversion<from_implicit_conversion, To>::value);
    TEST_STATIC_ASSERT(has_explicit_conversion<from_explicit_conversion, To>::value);
    TEST_STATIC_ASSERT(not has_explicit_conversion<not_castable, To>::value);
    TEST_STATIC_ASSERT(not has_explicit_conversion<int, To>::value);
    TEST_STATIC_ASSERT(not has_explicit_conversion<void, To>::value);
    TEST_CHECK(true);
}

TEST_CASE(has_implicit_conversion_test)
{
    TEST_STATIC_ASSERT(has_implicit_conversion<from_implicit_construct, To>::value);
    TEST_STATIC_ASSERT(not has_implicit_conversion<from_explicit_construct, To>::value);
    TEST_STATIC_ASSERT(has_implicit_conversion<from_implicit_conversion, To>::value);
    TEST_STATIC_ASSERT(not has_implicit_conversion<from_explicit_conversion, To>::value);
    TEST_STATIC_ASSERT(not has_implicit_conversion<not_castable, To>::value);
    TEST_STATIC_ASSERT(not has_implicit_conversion<int, To>::value);
    TEST_STATIC_ASSERT(not has_implicit_conversion<void, To>::value);
    TEST_CHECK(true);
}

TEST_CASE(has_conversion_test)
{
    TEST_STATIC_ASSERT(has_conversion<from_explicit_construct, To>::value);
    TEST_STATIC_ASSERT(has_conversion<from_implicit_construct, To>::value);
    TEST_STATIC_ASSERT(has_conversion<from_implicit_conversion, To>::value);
    TEST_STATIC_ASSERT(has_conversion<from_explicit_conversion, To>::value);
    TEST_STATIC_ASSERT(not has_conversion<not_castable, To>::value);
    TEST_STATIC_ASSERT(not has_conversion<int, To>::value);
    TEST_STATIC_ASSERT(not has_conversion<void, To>::value);
    TEST_CHECK(true);
}


TEST_SUITE_END()