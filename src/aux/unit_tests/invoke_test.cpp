#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include <elib/aux/invoke.hpp>
using namespace elib;
using namespace elib::aux;


struct class_type
{
    class_type() {}
    
    int none() { return 0; }
    int const_none() const { return 1; }
    
    int first(int x, int) { return x; }
    int second(int, int y) const { return y; }
};


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

BOOST_AUTO_TEST_SUITE_END()