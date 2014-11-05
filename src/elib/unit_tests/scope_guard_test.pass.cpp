// REQUIRES: ELIB_CORE
#include <elib/scope_guard.hpp>
#include <elib/aux/move.hpp>
#include "rapid-cxx-test.hpp"
using namespace elib;

TEST_SUITE(elib_scope_guard_test_suite)

TEST_CASE(basic_test)
{
    int x = 0;
    {
        auto guard = elib::make_scope_guard([&]() { x = 1; });
    }
    TEST_CHECK(x == 1);
}

TEST_CASE(exception_test)
{
    int x = 0;
    try {
        auto guard = elib::make_scope_guard([&]() { x = 1; });
        throw 0;
    } catch (...) {
    
    }
    TEST_CHECK(x == 1);
}

TEST_CASE(basic_dissmissed_test)
{
    int x = 0;
    {
        auto guard = elib::make_scope_guard([&]() { x = 1; });
        guard.dismiss();
    }
    TEST_CHECK(x == 0);
}

TEST_CASE(dismissed_exception_test)
{
    int x = 0;
    try {
        auto guard = elib::make_scope_guard([&]() { x = 1; });
        guard.dismiss();
        throw 0;
    } catch (...) {
        
    }
    TEST_CHECK(x == 0);
}

TEST_CASE(move_test)
{
    int x = 0;
    {
        auto guard = elib::make_scope_guard([&]() { x += 1; });
        auto guard2 = elib::move(guard);
    }
    TEST_CHECK(x == 1);
}

TEST_SUITE_END()