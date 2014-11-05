// REQUIRES: ELIB_AUX
#include <elib/config.hpp>
#include <elib/aux/traits/member_pointer_traits.hpp>
#include "rapid-cxx-test.hpp"
using namespace elib::aux;

struct class_type {};

struct t1 {};
struct t2 {};
struct t3 {};

TEST_SUITE(elib_aux_traits_member_pointer_traits_test_test_suite)

TEST_CASE(member_function_pointer_test)
{
    using Fn = t1(class_type::*)(t2, long);
    using T = member_pointer_traits<Fn>;
    TEST_SAME_TYPE(T::type, Fn);
    TEST_SAME_TYPE(T::result, t1);
    TEST_SAME_TYPE(T::class_type, class_type);
    TEST_STATIC_ASSERT(T::arity::value == 2);
    TEST_CHECK(true);
}

TEST_CASE(const_member_function_pointer_test)
{
    using Fn = t1(class_type::*)(t2, long) const;
    using T = member_pointer_traits<Fn>;
    TEST_SAME_TYPE(T::type, Fn);
    TEST_SAME_TYPE(T::result, t1);
    TEST_SAME_TYPE(T::class_type, class_type const);
    TEST_STATIC_ASSERT(T::arity::value == 2);
    TEST_CHECK(true);
}

TEST_CASE(volatile_member_function_pointer_test)
{
    using Fn = t1(class_type::*)(t2, long) volatile;
    using T = member_pointer_traits<Fn>;
    TEST_SAME_TYPE(T::type, Fn);
    TEST_SAME_TYPE(T::result, t1);
    TEST_SAME_TYPE(T::class_type, class_type volatile);
    TEST_STATIC_ASSERT(T::arity::value == 2);
    TEST_CHECK(true);
}

TEST_CASE(const_volatile_member_function_pointer_test)
{
    using Fn = t1(class_type::*)(t2, long) const volatile;
    using T = member_pointer_traits<Fn>;
    TEST_SAME_TYPE(T::type, Fn);
    TEST_SAME_TYPE(T::result, t1);
    TEST_SAME_TYPE(T::class_type, class_type const volatile);
    TEST_STATIC_ASSERT(T::arity::value == 2);
    TEST_CHECK(true);
}

#if !defined(ELIB_CONFIG_NO_REF_QUALIFIERS)

TEST_CASE(lvalue_member_function_pointer_test)
{
    using Fn = t1(class_type::*)(t2, long) &;
    using T = member_pointer_traits<Fn>;
    TEST_SAME_TYPE(T::type, Fn);
    TEST_SAME_TYPE(T::result, t1);
    TEST_SAME_TYPE(T::class_type, class_type &);
    TEST_STATIC_ASSERT(T::arity::value == 2);
    TEST_CHECK(true);
}

TEST_CASE(lvalue_const_member_function_pointer_test)
{
    using Fn = t1(class_type::*)(t2, long) const &;
    using T = member_pointer_traits<Fn>;
    TEST_SAME_TYPE(T::type, Fn);
    TEST_SAME_TYPE(T::result, t1);
    TEST_SAME_TYPE(T::class_type, class_type const &);
    TEST_STATIC_ASSERT(T::arity::value == 2);
    TEST_CHECK(true);
}

TEST_CASE(lvalue_volatile_member_function_pointer_test)
{
    using Fn = t1(class_type::*)(t2, long) volatile &;
    using T = member_pointer_traits<Fn>;
    TEST_SAME_TYPE(T::type, Fn);
    TEST_SAME_TYPE(T::result, t1);
    TEST_SAME_TYPE(T::class_type, class_type volatile &);
    TEST_STATIC_ASSERT(T::arity::value == 2);
    TEST_CHECK(true);
}

TEST_CASE(lvalue_const_volatile_member_function_pointer_test)
{
    using Fn = t1(class_type::*)(t2, long) const volatile &;
    using T = member_pointer_traits<Fn>;
    TEST_SAME_TYPE(T::type, Fn);
    TEST_SAME_TYPE(T::result, t1);
    TEST_SAME_TYPE(T::class_type, class_type const volatile &);
    TEST_STATIC_ASSERT(T::arity::value == 2);
    TEST_CHECK(true);
}

TEST_CASE(rvalue_member_function_pointer_test)
{
    using Fn = t1(class_type::*)(t2, long) &&;
    using T = member_pointer_traits<Fn>;
    TEST_SAME_TYPE(T::type, Fn);
    TEST_SAME_TYPE(T::result, t1);
    TEST_SAME_TYPE(T::class_type, class_type &&);
    TEST_STATIC_ASSERT(T::arity::value == 2);
    TEST_CHECK(true);
}

TEST_CASE(rvalue_const_member_function_pointer_test)
{
    using Fn = t1(class_type::*)(t2, long) const &&;
    using T = member_pointer_traits<Fn>;
    TEST_SAME_TYPE(T::type, Fn);
    TEST_SAME_TYPE(T::result, t1);
    TEST_SAME_TYPE(T::class_type, class_type const &&);
    TEST_STATIC_ASSERT(T::arity::value == 2);
    TEST_CHECK(true);
}

TEST_CASE(rvalue_volatile_member_function_pointer_test)
{
    using Fn = t1(class_type::*)(t2, long) volatile &&;
    using T = member_pointer_traits<Fn>;
    TEST_SAME_TYPE(T::type, Fn);
    TEST_SAME_TYPE(T::result, t1);
    TEST_SAME_TYPE(T::class_type, class_type volatile &&);
    TEST_STATIC_ASSERT(T::arity::value == 2);
    TEST_CHECK(true);
}

TEST_CASE(rvalue_const_volatile_member_function_pointer_test)
{
    using Fn = t1(class_type::*)(t2, long) const volatile &&;
    using T = member_pointer_traits<Fn>;
    TEST_SAME_TYPE(T::type, Fn);
    TEST_SAME_TYPE(T::result, t1);
    TEST_SAME_TYPE(T::class_type, class_type const volatile &&);
    TEST_STATIC_ASSERT(T::arity::value == 2);
    TEST_CHECK(true);
}
#else /* ELIB_CONFIG_NO_REF_QUALIFIERS */
TEST_CASE(rvalue_test)
{
    TEST_UNSUPPORTED();
}
#endif /* ELIB_CONFIG_NO_REF_QUALIFIERS */

TEST_CASE(member_object_pointer_test)
{
    using Fn = char* class_type::*;
    using T = member_pointer_traits<Fn>;
    TEST_SAME_TYPE(T::type, Fn);
    TEST_SAME_TYPE(T::result, char*);
    TEST_SAME_TYPE(T::class_type, class_type);
    TEST_STATIC_ASSERT(T::arity::value == 0);
    TEST_CHECK(true);
}

TEST_SUITE_END()