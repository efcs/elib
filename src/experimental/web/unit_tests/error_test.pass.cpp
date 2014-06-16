// REQUIRES: ELIB_WEB_SOURCE
#include <elib/experimental/web/error.hpp>
#include "rapid-cxx-test.hpp"
using namespace elib::web;

TEST_SUITE(elib_web_error_test_suite)

TEST_CASE(exception_ctor_test)
{
    std::string const expect("hello");
    {
        web_error e(expect);
        TEST_CHECK(e.what() == expect);
    }{
        web_error e(expect.c_str());
        TEST_CHECK(e.what() == expect);
    }
}

TEST_CASE(copy_test)
{
    std::string const expect("hello");
    web_error const e1(expect);
    web_error const e2(e1);
    TEST_CHECK(e2.what() == expect);
}

TEST_CASE(move_test)
{
    std::string const expect("hello");
    web_error e1(expect);
    web_error const e2(static_cast<web_error &&>(e1));
    TEST_CHECK(e2.what() == expect);
}

TEST_CASE(copy_assign_test)
{
    std::string const expect("hello");
    web_error const e1(expect);
    web_error e2("bad");
    e2 = e1;
    TEST_CHECK(e2.what() == expect);
}

TEST_CASE(move_assign_test)
{
    std::string const expect("hello");
    web_error e1(expect);
    web_error e2("bad");
    e2 = static_cast<web_error &&>(e1);
    TEST_CHECK(e2.what() == expect);
}

TEST_SUITE_END()