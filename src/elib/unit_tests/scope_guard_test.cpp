#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include <elib/scope_guard.hpp>
#include <elib/aux/move.hpp>
using namespace elib;

BOOST_AUTO_TEST_SUITE(elib_scope_guard_test_suite)

BOOST_AUTO_TEST_CASE(basic_test)
{
    int x = 0;
    {
        auto guard = elib::make_scope_guard([&]() { x = 1; });
    }
    BOOST_CHECK(x == 1);
}

BOOST_AUTO_TEST_CASE(exception_test)
{
    int x = 0;
    try {
        auto guard = elib::make_scope_guard([&]() { x = 1; });
        throw 0;
    } catch (...) {
    
    }
    BOOST_CHECK(x == 1);
}

BOOST_AUTO_TEST_CASE(basic_dissmissed_test)
{
    int x = 0;
    {
        auto guard = elib::make_scope_guard([&]() { x = 1; });
        guard.dismiss();
    }
    BOOST_CHECK(x == 0);
}

BOOST_AUTO_TEST_CASE(dismissed_exception_test)
{
    int x = 0;
    try {
        auto guard = elib::make_scope_guard([&]() { x = 1; });
        guard.dismiss();
        throw 0;
    } catch (...) {
        
    }
    BOOST_CHECK(x == 0);
}

BOOST_AUTO_TEST_CASE(move_test)
{
    int x = 0;
    {
        auto guard = elib::make_scope_guard([&]() { x += 1; });
        auto guard2 = elib::move(guard);
    }
    BOOST_CHECK(x == 1);
}

BOOST_AUTO_TEST_SUITE_END()