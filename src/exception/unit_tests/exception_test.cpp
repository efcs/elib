#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include <elib/exception.hpp>
#include <elib/aux.hpp>

#include <string>

using namespace elib::except;
using namespace elib;


BOOST_AUTO_TEST_SUITE(except_exception_test_suite)

BOOST_AUTO_TEST_CASE(except_exception_basic_test)
{
    std::string what_arg{"what"};
    
    const exception e1(what_arg.c_str());
    BOOST_CHECK(e1.what() == what_arg);
    
    const exception e2(what_arg);
    BOOST_CHECK(e2.what() == what_arg);
    
    // copy ctor test
    const exception e3 = e1;
    BOOST_CHECK(e3.what() == what_arg);
    
    exception e4("hello world");
    e4 = e2;
    BOOST_CHECK(e4.what() == what_arg);
    
    ELIB_SET_EXCEPTION_THROW_SITE(e4);
    BOOST_CHECK(e4.what() != what_arg);
}

BOOST_AUTO_TEST_CASE(throw_info_str_test)
{
    exception e("hello world");
    BOOST_CHECK(e.throw_info_str() == "");
    ELIB_SET_EXCEPTION_THROW_SITE(e);
    BOOST_CHECK(e.throw_info_str() != "");
}


BOOST_AUTO_TEST_CASE(except_exception_error_info_test)
{
    throw_file file(__FILE__);
    throw_func func(__func__);
    const throw_line line(__LINE__);
    
    exception e("Hello world");
    BOOST_CHECK(has_error_info<throw_file>(e) == false);
    BOOST_CHECK(has_error_info<throw_func>(e) == false);
    BOOST_CHECK(has_error_info<throw_line>(e) == false);
    
    BOOST_CHECK(insert_error_info(e, file));
    BOOST_CHECK(has_error_info<throw_file>(e));
    // check that second insert fails
    BOOST_CHECK(!insert_error_info(e, file));
    BOOST_CHECK(has_error_info<throw_file>(e));
    // check proper value inserted
    BOOST_CHECK(get_error_info<throw_file>(e).value() == std::string(__FILE__));
    
    throw_file file2("Not This File");
    set_error_info(e, file2);
    BOOST_CHECK(has_error_info<throw_file>(e));
    BOOST_CHECK(get_error_info<throw_file>(e).value() == std::string(file2.value()));
    
    // Check insertion operator
    e << func << line;
    BOOST_CHECK(has_error_info<throw_func>(e));
    BOOST_CHECK(has_error_info<throw_line>(e));
    // check proper value was inserted
    BOOST_CHECK(get_error_info<throw_func>(e).value() == std::string(func.value()));
    BOOST_CHECK(get_error_info<throw_line>(e).value() == line.value());
    
    // Check get_error_info_value()
    BOOST_CHECK(get_error_info_value<throw_func>(e) == std::string(func.value()));
    BOOST_CHECK(get_error_info<throw_line>(e).value() == get_error_info_value<throw_line>(e));
}

BOOST_AUTO_TEST_CASE(emplace_error_info_test)
{
    exception e("except");
    BOOST_CHECK(e.emplace_error_info<throw_line>(0));
    BOOST_CHECK(e.has_error_info<throw_line>());
}

BOOST_AUTO_TEST_CASE(get_error_info_nothrow_test)
{
    {
        exception const e("except");
        throw_line const *ptr = e.get_error_info<throw_line>();
        BOOST_CHECK(ptr == nullptr);
    }{
        exception e("except");
        e.set_error_info(throw_line(__LINE__));
        exception const & eref = e;
        throw_line const *ptr = eref.get_error_info<throw_line>();
        BOOST_CHECK(ptr != nullptr);
    }
}

BOOST_AUTO_TEST_CASE(insert_error_info_function_move_test)
{
    exception e("");
    throw_line l(0);
    BOOST_CHECK(insert_error_info(e, static_cast<throw_line &&>(l)));
    BOOST_CHECK(e.has_error_info<throw_line>());
}

BOOST_AUTO_TEST_CASE(emplace_error_info_function_test)
{
    exception e("");
    BOOST_CHECK(emplace_error_info<throw_line>(e, 0));
    BOOST_CHECK(e.has_error_info<throw_line>());
}

BOOST_AUTO_TEST_CASE(set_error_info_function_test)
{
    exception e("");
    throw_line l(0);
    set_error_info(e, static_cast<throw_line &&>(l));
    BOOST_CHECK(e.has_error_info<throw_line>());
}

BOOST_AUTO_TEST_CASE(get_error_info_const_funtion_test)
{
    exception e("");
    BOOST_CHECK(emplace_error_info<throw_line>(e, 1));
    exception const & eref = e;
    
    auto const & val = get_error_info_value<throw_line>(eref);
    BOOST_CHECK(val == 1);
}

BOOST_AUTO_TEST_SUITE_END()