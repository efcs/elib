// REQUIRES: ELIB_AUX
#include <elib/config.hpp>
#include <elib/aux/invoke.hpp>
#include <elib/aux.hpp>
#include <tuple>
#include "rapid-cxx-test.hpp"

using namespace elib;
using namespace elib::aux;


struct class_type
{
    class_type() {}
    
    int none() { return 0; }
    int const_none() const { return 1; }
    
    int first(int x, int) { return x; }
    int second(int, int y) const { return y; }
    
    int data{10};
};


struct functor
{
#if !defined(ELIB_CONFIG_NO_REF_QUALIFIERS)
    int operator()(int x, int) & { return x; }
    int operator()(int, int y) && { return y; }
# else
    /* change the signature so all tests that use the functor must also work 
     * around this issue.
     */
    int operator()(int , int x, int) { return x; }
#endif
};


inline int unpackable_function(int x, std::string, long)
{
    return x;
}

TEST_SUITE(elib_aux_invoke_test_suite)

TEST_CASE(non_const_member_function_from_ref_with_args_test)
{
    class_type c;
    auto fn_ptr = &class_type::first;
    auto ret = invoke(fn_ptr, c, 2, 3);
    TEST_CHECK(ret == 2);
}

TEST_CASE(const_member_function_from_ref_with_args_test)
{
    const class_type c;
    auto fn_ptr = &class_type::second;
    auto ret = invoke(fn_ptr, c, 2, 3);
    TEST_CHECK(ret == 3);
}

TEST_CASE(non_const_member_function_from_pointer_with_args_test)
{
    class_type c;
    auto fn_ptr = &class_type::first;
    auto ret = invoke(fn_ptr, &c, 2, 3);
    TEST_CHECK(ret == 2);
}

TEST_CASE(const_member_function_from_pointer_with_args_test)
{
    const class_type c;
    auto fn_ptr = &class_type::second;
    auto ret = invoke(fn_ptr, &c, 2, 3);
    TEST_CHECK(ret == 3);
}

TEST_CASE(non_const_member_function_from_ref_no_args_test)
{
    class_type c;
    auto fn_ptr = &class_type::none;
    auto ret = invoke(fn_ptr, c);
    TEST_CHECK(ret == 0);
}

TEST_CASE(const_member_function_from_ref_no_args_test)
{
    const class_type c;
    auto fn_ptr = &class_type::const_none;
    auto ret = invoke(fn_ptr, c);
    TEST_CHECK(ret == 1);
}

TEST_CASE(non_const_member_function_from_pointer_no_args_test)
{
    class_type c;
    auto fn_ptr = &class_type::none;
    auto ret = invoke(fn_ptr, &c);
    TEST_CHECK(ret == 0);
}

TEST_CASE(const_member_function_from_pointer_no_args_test)
{
    const class_type c;
    auto fn_ptr = &class_type::const_none;
    auto ret = invoke(fn_ptr, &c);
    TEST_CHECK(ret == 1);
}

TEST_CASE(member_object_from_ref_test)
{
    class_type t;
    auto fn_ptr = &class_type::data;
    auto ret = invoke(fn_ptr, t);
    TEST_CHECK(ret == 10);
}

TEST_CASE(member_object_from_ptr_test)
{
    class_type t;
    auto fn_ptr = &class_type::data;
    auto ret = invoke(fn_ptr, &t);
    TEST_CHECK(ret == 10);
}

#if !defined(ELIB_CONFIG_NO_REF_QUALIFIERS)

TEST_CASE(functor_lvalue_test)
{
    functor f;
    auto ret = invoke(f, 1, 2);
    TEST_CHECK(ret == 1);
}

TEST_CASE(functor_rvalue_test)
{
    auto ret = invoke(functor{}, 1, 2);
    TEST_CHECK(ret == 2);
}

# else

TEST_CASE(functor_test)
{
    auto ret = invoke(functor{}, 1, 2, 3);
    TEST_CHECK(ret == 2);
}
# endif

TEST_CASE(unpackable_function_invoke_test_2)
{
    std::tuple<int, std::string, long> pack(1, "", 2);
    auto ret = invoke(invoke_unpack, &unpackable_function, pack);
    TEST_CHECK(ret == 1);
}

TEST_CASE(packed_unpackable_function_invoke_test)
{
    using FnType = decltype(&unpackable_function);
    std::tuple<FnType, int, std::string, long> pack(&unpackable_function, 1, "", 2);
    auto ret = invoke(invoke_unpack, pack);
    TEST_CHECK(ret == 1);
}

TEST_SUITE_END()