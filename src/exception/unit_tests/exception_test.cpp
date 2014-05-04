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

BOOST_AUTO_TEST_SUITE_END()