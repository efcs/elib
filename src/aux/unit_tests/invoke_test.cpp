#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include <elib/aux/invoke.hpp>
#include <tuple>
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
    int operator()(int x, int) & { return x; }
    int operator()(int, int y) && { return y; }
};

int unpackable_function(int x, std::string, long)
{
    return x;
}

BOOST_AUTO_TEST_SUITE(elib_aux_invoke_test_suite)

BOOST_AUTO_TEST_CASE(non_const_member_function_from_ref_with_args_test)
{
    class_type c;
    auto fn_ptr = &class_type::first;
    auto ret = invoke(fn_ptr, c, 2, 3);
    BOOST_CHECK(ret == 2);
}

BOOST_AUTO_TEST_CASE(const_member_function_from_ref_with_args_test)
{
    const class_type c;
    auto fn_ptr = &class_type::second;
    auto ret = invoke(fn_ptr, c, 2, 3);
    BOOST_CHECK(ret == 3);
}

BOOST_AUTO_TEST_CASE(non_const_member_function_from_pointer_with_args_test)
{
    class_type c;
    auto fn_ptr = &class_type::first;
    auto ret = invoke(fn_ptr, &c, 2, 3);
    BOOST_CHECK(ret == 2);
}

BOOST_AUTO_TEST_CASE(const_member_function_from_pointer_with_args_test)
{
    const class_type c;
    auto fn_ptr = &class_type::second;
    auto ret = invoke(fn_ptr, &c, 2, 3);
    BOOST_CHECK(ret == 3);
}

BOOST_AUTO_TEST_CASE(non_const_member_function_from_ref_no_args_test)
{
    class_type c;
    auto fn_ptr = &class_type::none;
    auto ret = invoke(fn_ptr, c);
    BOOST_CHECK(ret == 0);
}

BOOST_AUTO_TEST_CASE(const_member_function_from_ref_no_args_test)
{
    const class_type c;
    auto fn_ptr = &class_type::const_none;
    auto ret = invoke(fn_ptr, c);
    BOOST_CHECK(ret == 1);
}

BOOST_AUTO_TEST_CASE(non_const_member_function_from_pointer_no_args_test)
{
    class_type c;
    auto fn_ptr = &class_type::none;
    auto ret = invoke(fn_ptr, &c);
    BOOST_CHECK(ret == 0);
}

BOOST_AUTO_TEST_CASE(const_member_function_from_pointer_no_args_test)
{
    const class_type c;
    auto fn_ptr = &class_type::const_none;
    auto ret = invoke(fn_ptr, &c);
    BOOST_CHECK(ret == 1);
}

BOOST_AUTO_TEST_CASE(member_object_from_ref_test)
{
    class_type t;
    auto fn_ptr = &class_type::data;
    auto ret = invoke(fn_ptr, t);
    BOOST_CHECK(ret == 10);
}

BOOST_AUTO_TEST_CASE(member_object_from_ptr_test)
{
    class_type t;
    auto fn_ptr = &class_type::data;
    auto ret = invoke(fn_ptr, &t);
    BOOST_CHECK(ret == 10);
}

BOOST_AUTO_TEST_CASE(functor_lvalue_test)
{
    functor f;
    auto ret = invoke(f, 1, 2);
    BOOST_CHECK(ret == 1);
}

BOOST_AUTO_TEST_CASE(functor_rvalue_test)
{
    auto ret = invoke(functor{}, 1, 2);
    BOOST_CHECK(ret == 2);
}

BOOST_AUTO_TEST_CASE(unpackable_function_invoke_test)
{
    std::tuple<int, std::string, long> pack(1, "", 2);
    auto ret = invoke(invoke_unpack, &unpackable_function, pack);
    BOOST_CHECK(ret == 1);
}

BOOST_AUTO_TEST_CASE(packed_unpackable_function_invoke_test)
{
    using FnType = decltype(&unpackable_function);
    std::tuple<FnType, int, std::string, long> pack(&unpackable_function, 1, "", 2);
    auto ret = invoke(invoke_unpack, pack);
    BOOST_CHECK(ret == 1);
}

BOOST_AUTO_TEST_SUITE_END()