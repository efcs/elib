// REQUIRES: ELIB_AUX_SOURCE, ELIB_BOOST_TEST
#define BOOST_TEST_MODULE Main
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include <elib/config.hpp>
#include <elib/aux/traits/member_pointer_traits.hpp>
#include <elib/aux/traits/is_same.hpp>
#include <elib/aux/static_assert.hpp>
using namespace elib::aux;

struct class_type {};

struct t1 {};
struct t2 {};
struct t3 {};

BOOST_AUTO_TEST_SUITE(elib_aux_traits_member_pointer_traits_test_test_suite)

BOOST_AUTO_TEST_CASE(member_function_pointer_test)
{
    using Fn = t1(class_type::*)(t2, long);
    using T = member_pointer_traits<Fn>;
    ELIB_STATIC_ASSERT(is_same<T::type, Fn>::value);
    ELIB_STATIC_ASSERT(is_same<T::result, t1>::value);
    ELIB_STATIC_ASSERT(is_same<T::class_type, class_type>::value);
    ELIB_STATIC_ASSERT(T::arity::value == 2);
    BOOST_CHECK(true);
}

BOOST_AUTO_TEST_CASE(const_member_function_pointer_test)
{
    using Fn = t1(class_type::*)(t2, long) const;
    using T = member_pointer_traits<Fn>;
    ELIB_STATIC_ASSERT(is_same<T::type, Fn>::value);
    ELIB_STATIC_ASSERT(is_same<T::result, t1>::value);
    ELIB_STATIC_ASSERT(is_same<T::class_type, class_type const>::value);
    ELIB_STATIC_ASSERT(T::arity::value == 2);
    BOOST_CHECK(true);
}

BOOST_AUTO_TEST_CASE(volatile_member_function_pointer_test)
{
    using Fn = t1(class_type::*)(t2, long) volatile;
    using T = member_pointer_traits<Fn>;
    ELIB_STATIC_ASSERT(is_same<T::type, Fn>::value);
    ELIB_STATIC_ASSERT(is_same<T::result, t1>::value);
    ELIB_STATIC_ASSERT(is_same<T::class_type, class_type volatile>::value);
    ELIB_STATIC_ASSERT(T::arity::value == 2);
    BOOST_CHECK(true);
}

BOOST_AUTO_TEST_CASE(const_volatile_member_function_pointer_test)
{
    using Fn = t1(class_type::*)(t2, long) const volatile;
    using T = member_pointer_traits<Fn>;
    ELIB_STATIC_ASSERT(is_same<T::type, Fn>::value);
    ELIB_STATIC_ASSERT(is_same<T::result, t1>::value);
    ELIB_STATIC_ASSERT(is_same<T::class_type, class_type const volatile>::value);
    ELIB_STATIC_ASSERT(T::arity::value == 2);
    BOOST_CHECK(true);
}

#if !defined(ELIB_CONFIG_NO_REF_QUALIFIERS)

BOOST_AUTO_TEST_CASE(lvalue_member_function_pointer_test)
{
    using Fn = t1(class_type::*)(t2, long) &;
    using T = member_pointer_traits<Fn>;
    ELIB_STATIC_ASSERT(is_same<T::type, Fn>::value);
    ELIB_STATIC_ASSERT(is_same<T::result, t1>::value);
    ELIB_STATIC_ASSERT(is_same<T::class_type, class_type &>::value);
    ELIB_STATIC_ASSERT(T::arity::value == 2);
    BOOST_CHECK(true);
}

BOOST_AUTO_TEST_CASE(lvalue_const_member_function_pointer_test)
{
    using Fn = t1(class_type::*)(t2, long) const &;
    using T = member_pointer_traits<Fn>;
    ELIB_STATIC_ASSERT(is_same<T::type, Fn>::value);
    ELIB_STATIC_ASSERT(is_same<T::result, t1>::value);
    ELIB_STATIC_ASSERT(is_same<T::class_type, class_type const &>::value);
    ELIB_STATIC_ASSERT(T::arity::value == 2);
    BOOST_CHECK(true);
}

BOOST_AUTO_TEST_CASE(lvalue_volatile_member_function_pointer_test)
{
    using Fn = t1(class_type::*)(t2, long) volatile &;
    using T = member_pointer_traits<Fn>;
    ELIB_STATIC_ASSERT(is_same<T::type, Fn>::value);
    ELIB_STATIC_ASSERT(is_same<T::result, t1>::value);
    ELIB_STATIC_ASSERT(is_same<T::class_type, class_type volatile &>::value);
    ELIB_STATIC_ASSERT(T::arity::value == 2);
    BOOST_CHECK(true);
}

BOOST_AUTO_TEST_CASE(lvalue_const_volatile_member_function_pointer_test)
{
    using Fn = t1(class_type::*)(t2, long) const volatile &;
    using T = member_pointer_traits<Fn>;
    ELIB_STATIC_ASSERT(is_same<T::type, Fn>::value);
    ELIB_STATIC_ASSERT(is_same<T::result, t1>::value);
    ELIB_STATIC_ASSERT(is_same<T::class_type, class_type const volatile &>::value);
    ELIB_STATIC_ASSERT(T::arity::value == 2);
    BOOST_CHECK(true);
}

BOOST_AUTO_TEST_CASE(rvalue_member_function_pointer_test)
{
    using Fn = t1(class_type::*)(t2, long) &&;
    using T = member_pointer_traits<Fn>;
    ELIB_STATIC_ASSERT(is_same<T::type, Fn>::value);
    ELIB_STATIC_ASSERT(is_same<T::result, t1>::value);
    ELIB_STATIC_ASSERT(is_same<T::class_type, class_type &&>::value);
    ELIB_STATIC_ASSERT(T::arity::value == 2);
    BOOST_CHECK(true);
}

BOOST_AUTO_TEST_CASE(rvalue_const_member_function_pointer_test)
{
    using Fn = t1(class_type::*)(t2, long) const &&;
    using T = member_pointer_traits<Fn>;
    ELIB_STATIC_ASSERT(is_same<T::type, Fn>::value);
    ELIB_STATIC_ASSERT(is_same<T::result, t1>::value);
    ELIB_STATIC_ASSERT(is_same<T::class_type, class_type const &&>::value);
    ELIB_STATIC_ASSERT(T::arity::value == 2);
    BOOST_CHECK(true);
}

BOOST_AUTO_TEST_CASE(rvalue_volatile_member_function_pointer_test)
{
    using Fn = t1(class_type::*)(t2, long) volatile &&;
    using T = member_pointer_traits<Fn>;
    ELIB_STATIC_ASSERT(is_same<T::type, Fn>::value);
    ELIB_STATIC_ASSERT(is_same<T::result, t1>::value);
    ELIB_STATIC_ASSERT(is_same<T::class_type, class_type volatile &&>::value);
    ELIB_STATIC_ASSERT(T::arity::value == 2);
    BOOST_CHECK(true);
}

BOOST_AUTO_TEST_CASE(rvalue_const_volatile_member_function_pointer_test)
{
    using Fn = t1(class_type::*)(t2, long) const volatile &&;
    using T = member_pointer_traits<Fn>;
    ELIB_STATIC_ASSERT(is_same<T::type, Fn>::value);
    ELIB_STATIC_ASSERT(is_same<T::result, t1>::value);
    ELIB_STATIC_ASSERT(is_same<T::class_type, class_type const volatile &&>::value);
    ELIB_STATIC_ASSERT(T::arity::value == 2);
    BOOST_CHECK(true);
}
#endif /* ELIB_CONFIG_NO_REF_QUALIFIERS */

BOOST_AUTO_TEST_CASE(member_object_pointer_test)
{
    using Fn = char* class_type::*;
    using T = member_pointer_traits<Fn>;
    ELIB_STATIC_ASSERT(is_same<T::type, Fn>::value);
    ELIB_STATIC_ASSERT(is_same<T::result, char*>::value);
    ELIB_STATIC_ASSERT(is_same<T::class_type, class_type>::value);
    ELIB_STATIC_ASSERT(T::arity::value == 0);
    BOOST_CHECK(true);
}

BOOST_AUTO_TEST_SUITE_END()