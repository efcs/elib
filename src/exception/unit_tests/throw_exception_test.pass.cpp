// REQUIRES: ELIB_EXCEPTION_SOURCE
#include <elib/exception/exception.hpp>
#include <elib/exception/throw_exception.hpp>
#include <elib/aux/move.hpp>
#include <stdexcept>
#include "rapid-cxx-test.hpp"

using namespace elib::except;

TEST_SUITE(exception_throw_exception_test_suite)

TEST_CASE(throw_exception_test)
{
    std::logic_error err("What");
    TEST_CHECK_THROW(std::logic_error, throw_exception(err));
}

TEST_CASE(throw_exception_from_test)
{
    // lvalue test
    {
        exception e("What");
        TEST_CHECK_THROW(exception, throw_exception_from(e, "file", "func", 1));
        TEST_CHECK(e.has_throw_info());
    }
    // rvalue test
    {
        exception e("What");
        TEST_CHECK_THROW(exception, throw_exception_from(elib::move(e), "file", "func", 1));
    }
}

TEST_CASE(set_exception_throw_site_test)
{
    exception e("what");
    set_exception_throw_site(e, "file", "func", 1);
    TEST_CHECK(e.has_throw_info());
}

TEST_SUITE_END()