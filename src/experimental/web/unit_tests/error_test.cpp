#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include <elib/experimental/web/error.hpp>
using namespace elib::web;

BOOST_AUTO_TEST_SUITE(elib_web_error_test_suite)

BOOST_AUTO_TEST_CASE(exception_ctor_test)
{
    std::string const expect("hello");
    {
        web_error e(expect);
        BOOST_CHECK(e.what() == expect);
    }{
        web_error e(expect.c_str());
        BOOST_CHECK(e.what() == expect);
    }
}

BOOST_AUTO_TEST_CASE(copy_test)
{
    std::string const expect("hello");
    web_error const e1(expect);
    web_error const e2(e1);
    BOOST_CHECK(e2.what() == expect);
}

BOOST_AUTO_TEST_CASE(move_test)
{
    std::string const expect("hello");
    web_error e1(expect);
    web_error const e2(static_cast<web_error &&>(e1));
    BOOST_CHECK(e2.what() == expect);
}

BOOST_AUTO_TEST_CASE(copy_assign_test)
{
    std::string const expect("hello");
    web_error const e1(expect);
    web_error e2("bad");
    e2 = e1;
    BOOST_CHECK(e2.what() == expect);
}

BOOST_AUTO_TEST_CASE(move_assign_test)
{
    std::string const expect("hello");
    web_error e1(expect);
    web_error e2("bad");
    e2 = static_cast<web_error &&>(e1);
    BOOST_CHECK(e2.what() == expect);
}

BOOST_AUTO_TEST_SUITE_END()