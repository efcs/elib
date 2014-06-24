// REQUIRES: ELIB_AUX
#include <elib/config.hpp>
#include <elib/aux/traits/invoke_of.hpp>
#include "rapid-cxx-test.hpp"

using namespace elib::aux;

struct dummy_type {};

struct class_type {};

struct functor
{
#if !defined(ELIB_CONFIG_NO_REF_QUALIFIERS)
    int operator()(int) & { return 0; }
    long operator()(int) && { return 0; }
#else
    int operator()(int) { return 0; }
#endif
};

TEST_SUITE(elib_aux_traits_invoke_of_test_suite)

TEST_CASE(non_const_member_function_from_ref_with_args_test)
{
    using Fn = long(class_type::*)(int, dummy_type);
    using Ret = invoke_of_t<Fn, class_type &, int, dummy_type>;
    using CanInvoke = is_invokable<Fn, class_type &, int, dummy_type>;
    TEST_STATIC_ASSERT(CanInvoke::value);
    TEST_SAME_TYPE(Ret, long);
}

TEST_CASE(const_member_function_from_ref_with_args_test)
{
    using Fn = long(class_type::*)(int, dummy_type) const;
    using Ret = invoke_of_t<Fn, class_type const &, int, dummy_type>;
    using CanInvoke = is_invokable<Fn, class_type const&, int, dummy_type>;
    TEST_STATIC_ASSERT(CanInvoke::value);
    TEST_SAME_TYPE(Ret, long);
}

TEST_CASE(non_const_member_function_from_ptr_with_args_test)
{
    using Fn = long(class_type::*)(int, dummy_type);
    using Ret = invoke_of_t<Fn, class_type *, int, dummy_type>;
    using CanInvoke = is_invokable<Fn, class_type *, int, dummy_type>;
    TEST_STATIC_ASSERT(CanInvoke::value);
    TEST_SAME_TYPE(Ret, long);
}

TEST_CASE(const_member_function_from_ptr_with_args_test)
{
    using Fn = long(class_type::*)(int, dummy_type) const;
    using Ret = invoke_of_t<Fn, class_type const *, int, dummy_type>;
    using CanInvoke = is_invokable<Fn, class_type const *, int, dummy_type>;
    TEST_STATIC_ASSERT(CanInvoke::value);
    TEST_SAME_TYPE(Ret, long);
}

TEST_CASE(member_function_const_mismatch_from_ref_test)
{
    using Fn = void(class_type::*)();
    using CanInvoke = is_invokable<Fn, class_type const &>;
    TEST_STATIC_ASSERT(not CanInvoke::value);
    
    // you should still be able to instantiate this
    using Invoke = invoke_of<Fn, class_type const &>;
    Invoke inv;
    ((void)inv);
    
}

TEST_CASE(member_function_const_mismatch_from_ptr_test)
{
    using Fn = void(class_type::*)();
    using CanInvoke = is_invokable<Fn, class_type const*>;
    TEST_STATIC_ASSERT(not CanInvoke::value);
    
    using Invoke = invoke_of<Fn, class_type const*>;
    Invoke inv;
    ((void)inv);
}

TEST_CASE(member_object_with_ref_test)
{
    using Fn = char* class_type::*;
    using CanInvoke = is_invokable<Fn, class_type &>;
    using Ret = invoke_of_t<Fn, class_type &>;
    
    TEST_STATIC_ASSERT(CanInvoke::value);
    TEST_SAME_TYPE(Ret, char*&);
}

TEST_CASE(member_object_with_ptr_test)
{
    using Fn = char* class_type::*;
    using CanInvoke = is_invokable<Fn, class_type *>;
    using Ret = invoke_of_t<Fn, class_type *>;
    
    TEST_STATIC_ASSERT(CanInvoke::value);
    TEST_SAME_TYPE(Ret, char*&);

}


TEST_CASE(lvalue_functor_test)
{
    using Fn = functor &;
    using CanInvoke = is_invokable<Fn, int>;
    using Ret = invoke_of_t<Fn, int>;
    
    TEST_STATIC_ASSERT(CanInvoke::value);
    TEST_SAME_TYPE(Ret, int);

}


TEST_CASE(rvalue_functor_test)
{
#if !defined(ELIB_CONFIG_NO_REF_QUALIFIERS)
    using Fn = functor &&;
    using CanInvoke = is_invokable<Fn, int>;
    using Ret = invoke_of_t<Fn, int>;
    
    TEST_STATIC_ASSERT(CanInvoke::value);
    TEST_SAME_TYPE(Ret, long);
#else
    TEST_UNSUPPORTED();
#endif
}


TEST_SUITE_END()