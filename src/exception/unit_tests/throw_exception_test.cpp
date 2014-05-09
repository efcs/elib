#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include <elib/exception/exception.hpp>
#include <elib/exception/throw_exception.hpp>
#include <stdexcept>

using namespace elib::except;

BOOST_AUTO_TEST_SUITE(exception_throw_exception_test_suite)

BOOST_AUTO_TEST_CASE(throw_exception_test)
{
    std::logic_error err("What");
    BOOST_CHECK_THROW(throw_exception(err), std::logic_error);
}

BOOST_AUTO_TEST_CASE(throw_exception_from_test)
{
    exception e("What");
    BOOST_CHECK_THROW(throw_exception_from(e, "file", "func", 1), exception);
    BOOST_CHECK(e.has_throw_info());
}

BOOST_AUTO_TEST_CASE(set_exception_throw_site_test)
{
    exception e("what");
    set_exception_throw_site(e, "file", "func", 1);
    BOOST_CHECK(e.has_throw_info());
}

BOOST_AUTO_TEST_SUITE_END()