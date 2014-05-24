#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include <elib/aux/traits/is_castable.hpp>
#include <elib/aux/traits/is_explicitly_castable.hpp>
#include <elib/aux/traits/is_implicitly_castable.hpp>
#include <elib/aux/static_assert.hpp>
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

BOOST_AUTO_TEST_SUITE(elib_aux_traits_is_castable_test_suite)

BOOST_AUTO_TEST_CASE(is_implicitly_castable_test)
{
    ELIB_STATIC_ASSERT(is_implicitly_castable<from_implicit_construct, To>::value);
    ELIB_STATIC_ASSERT(not is_implicitly_castable<from_explicit_construct, To>::value);
    ELIB_STATIC_ASSERT(is_implicitly_castable<from_implicit_conversion, To>::value);
    ELIB_STATIC_ASSERT(not is_implicitly_castable<from_explicit_conversion, To>::value);
    ELIB_STATIC_ASSERT(not is_implicitly_castable<not_castable, To>::value);
    ELIB_STATIC_ASSERT(not is_implicitly_castable<int, To>::value);
    ELIB_STATIC_ASSERT(not is_implicitly_castable<void, To>::value);
    BOOST_CHECK(true);
}

BOOST_AUTO_TEST_CASE(is_explicitly_castable_test)
{
    ELIB_STATIC_ASSERT(is_explicitly_castable<from_explicit_construct, To>::value);
    ELIB_STATIC_ASSERT(is_explicitly_castable<from_implicit_construct, To>::value);
    ELIB_STATIC_ASSERT(is_explicitly_castable<from_implicit_conversion, To>::value);
    ELIB_STATIC_ASSERT(is_explicitly_castable<from_explicit_conversion, To>::value);
    ELIB_STATIC_ASSERT(not is_explicitly_castable<not_castable, To>::value);
    ELIB_STATIC_ASSERT(not is_explicitly_castable<int, To>::value);
    ELIB_STATIC_ASSERT(not is_explicitly_castable<void, To>::value);
    BOOST_CHECK(true);
}

BOOST_AUTO_TEST_CASE(is_castable_test)
{
    ELIB_STATIC_ASSERT(is_castable<from_explicit_construct, To>::value);
    ELIB_STATIC_ASSERT(is_castable<from_implicit_construct, To>::value);
    ELIB_STATIC_ASSERT(is_castable<from_implicit_conversion, To>::value);
    ELIB_STATIC_ASSERT(is_castable<from_explicit_conversion, To>::value);
    ELIB_STATIC_ASSERT(not is_castable<not_castable, To>::value);
    ELIB_STATIC_ASSERT(not is_castable<int, To>::value);
    ELIB_STATIC_ASSERT(not is_castable<void, To>::value);
    BOOST_CHECK(true);
}

BOOST_AUTO_TEST_SUITE_END()