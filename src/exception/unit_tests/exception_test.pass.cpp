// REQUIRES: ELIB_EXCEPTION
#include <elib/exception.hpp>
#include <elib/aux.hpp>
#include <string>
#include "rapid-cxx-test.hpp"

using namespace elib::except;
using namespace elib;


TEST_SUITE(except_exception_test_suite)

TEST_CASE(except_exception_basic_test)
{
    std::string what_arg{"what"};
    
    const exception e1(what_arg.c_str());
    TEST_CHECK(e1.what() == what_arg);
    
    const exception e2(what_arg);
    TEST_CHECK(e2.what() == what_arg);
    
    // copy ctor test
    const exception e3 = e1;
    TEST_CHECK(e3.what() == what_arg);
    
    exception e4("hello world");
    e4 = e2;
    TEST_CHECK(e4.what() == what_arg);
    
    ELIB_SET_EXCEPTION_THROW_SITE(e4);
    TEST_CHECK(e4.what() != what_arg);
}

TEST_CASE(throw_info_str_test)
{
    exception e("hello world");
    TEST_CHECK(e.throw_info_str() == "");
    ELIB_SET_EXCEPTION_THROW_SITE(e);
    TEST_CHECK(e.throw_info_str() != "");
}


TEST_CASE(except_exception_error_info_test)
{
    throw_file file(__FILE__);
    throw_func func(__func__);
    const throw_line line(__LINE__);
    
    exception e("Hello world");
    TEST_CHECK(has_error_info<throw_file>(e) == false);
    TEST_CHECK(has_error_info<throw_func>(e) == false);
    TEST_CHECK(has_error_info<throw_line>(e) == false);
    
    TEST_CHECK(insert_error_info(e, file));
    TEST_CHECK(has_error_info<throw_file>(e));
    // check that second insert fails
    TEST_CHECK(!insert_error_info(e, file));
    TEST_CHECK(has_error_info<throw_file>(e));
    // check proper value inserted
    TEST_CHECK(get_error_info<throw_file>(e).value() == std::string(__FILE__));
    
    throw_file file2("Not This File");
    set_error_info(e, file2);
    TEST_CHECK(has_error_info<throw_file>(e));
    TEST_CHECK(get_error_info<throw_file>(e).value() == std::string(file2.value()));
    
    // Check insertion operator
    e << func << line;
    TEST_CHECK(has_error_info<throw_func>(e));
    TEST_CHECK(has_error_info<throw_line>(e));
    // check proper value was inserted
    TEST_CHECK(get_error_info<throw_func>(e).value() == std::string(func.value()));
    TEST_CHECK(get_error_info<throw_line>(e).value() == line.value());
    
    // Check get_error_info_value()
    TEST_CHECK(get_error_info_value<throw_func>(e) == std::string(func.value()));
    TEST_CHECK(get_error_info<throw_line>(e).value() == get_error_info_value<throw_line>(e));
}

TEST_CASE(emplace_error_info_test)
{
    exception e("except");
    TEST_CHECK(e.emplace_error_info<throw_line>(0u));
    TEST_CHECK(e.has_error_info<throw_line>());
}

TEST_CASE(get_error_info_nothrow_test)
{
    {
        exception const e("except");
        throw_line const *ptr = e.get_error_info<throw_line>();
        TEST_CHECK(ptr == nullptr);
    }{
        exception e("except");
        e.set_error_info(throw_line(__LINE__));
        exception const & eref = e;
        throw_line const *ptr = eref.get_error_info<throw_line>();
        TEST_CHECK(ptr != nullptr);
    }
}

TEST_CASE(insert_error_info_function_move_test)
{
    exception e("");
    throw_line l(0u);
    TEST_CHECK(insert_error_info(e, static_cast<throw_line &&>(l)));
    TEST_CHECK(e.has_error_info<throw_line>());
}

TEST_CASE(emplace_error_info_function_test)
{
    exception e("");
    TEST_CHECK(emplace_error_info<throw_line>(e, 0u));
    TEST_CHECK(e.has_error_info<throw_line>());
}

TEST_CASE(set_error_info_function_test)
{
    exception e("");
    throw_line l(0u);
    set_error_info(e, static_cast<throw_line &&>(l));
    TEST_CHECK(e.has_error_info<throw_line>());
}

TEST_CASE(get_error_info_const_funtion_test)
{
    exception e("");
    TEST_CHECK(emplace_error_info<throw_line>(e, 1u));
    exception const & eref = e;
    
    auto const & val = get_error_info_value<throw_line>(eref);
    TEST_CHECK(val == 1u);
}

TEST_SUITE_END()