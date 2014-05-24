#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include <elib/aux/invoke.hpp>
using namespace elib;
using namespace elib::aux;


struct class_type
{
    int foo(int x) { return x; }
};



BOOST_AUTO_TEST_SUITE(elib_aux_invoke_test_suite)

BOOST_AUTO_TEST_CASE(member_function_test)
{
    class_type c;
    auto fn_ptr = &class_type::foo;
    auto ret = invoke(fn_ptr, c, 5);
    BOOST_CHECK(ret == 5);
}

BOOST_AUTO_TEST_SUITE_END()