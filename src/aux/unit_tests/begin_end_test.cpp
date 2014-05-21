#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include <elib/aux/begin_end.hpp>
#include <elib/aux/move.hpp>
#include <elib/aux/static_assert.hpp>

namespace adl_barrier
{
    struct iter {};
    struct const_iter {};
    struct move_iter {};
    
    struct iterable {
        constexpr iterable() noexcept {}
    };
    iter begin(iterable &) { return {}; }
    iter end(iterable &) { return {}; }
    const_iter begin(iterable const &) { return {}; }
    const_iter end(iterable const &) { return {}; }
    
    struct move_iterable {
        constexpr move_iterable() noexcept {}
    };
    move_iter begin(move_iterable &&) { return {}; }
    move_iter end(move_iterable &&) { return {}; }
    
    struct const_iterable {
        constexpr const_iterable() noexcept {}
    };
    const_iter begin(const_iterable const &) { return {}; }
    const_iter end(const_iterable const &) { return {}; }
    
    struct non_iter {};
}

using adl_barrier::iter;
using adl_barrier::const_iter;
using adl_barrier::move_iter;

using adl_barrier::iterable;
using adl_barrier::const_iterable;
using adl_barrier::move_iterable;

using adl_barrier::non_iter;

using namespace elib::aux;

BOOST_AUTO_TEST_SUITE(elib_aux_begin_end_test_suite)

BOOST_AUTO_TEST_CASE(get_begin_test)
{
    iterable i;
    const_iterable const ci;
    move_iterable mi;
    
    {
        BOOST_CHECK(get_begin(i));
        BOOST_CHECK(get_begin((iterable const &)i));
        BOOST_CHECK(get_begin(elib::move(i)));
    }
    {
        BOOST_CHECK(get_begin(ci));
        BOOST_CHECK(get_begin(elib::move(ci)));
    }
    {
        BOOST_CHECK(get_begin(elib::move(mi)));
    }
}

BOOST_AUTO_TEST_CASE(get_begin_ptr_test)
{
    iterable i;
    const_iterable const ci;
    move_iterable mi;
    non_iter ni;
    
    {
        BOOST_CHECK(get_begin_ptr(i));
        BOOST_CHECK(get_begin_ptr((iterable const &)i));
        BOOST_CHECK(get_begin_ptr(elib::move(i)));
    }
    {
        BOOST_CHECK(get_begin_ptr(ci));
        BOOST_CHECK(get_begin_ptr(elib::move(ci)));
    }
    {
        BOOST_CHECK(get_begin_ptr(elib::move(mi)));
        BOOST_CHECK(not get_begin_ptr(mi));
        BOOST_CHECK(not get_begin_ptr(elib::move((move_iterable const &)mi)));
    }
    {
        BOOST_CHECK(not get_begin_ptr(ni));
        BOOST_CHECK(not get_begin_ptr((non_iter const &)ni));
        BOOST_CHECK(not get_begin_ptr(elib::move(ni)));
        BOOST_CHECK(not get_begin_ptr(elib::move((non_iter const &)ni)));
    }
}

BOOST_AUTO_TEST_CASE(get_end_test)
{
    iterable i;
    const_iterable const ci;
    move_iterable mi;
    
    {
        BOOST_CHECK(get_end(i));
        BOOST_CHECK(get_end((iterable const &)i));
        BOOST_CHECK(get_end(elib::move(i)));
    }
    {
        BOOST_CHECK(get_end(ci));
        BOOST_CHECK(get_end(elib::move(ci)));
    }
    {
        BOOST_CHECK(get_end(elib::move(mi)));
    }
}

BOOST_AUTO_TEST_CASE(get_end_ptr_test)
{
    iterable i;
    const_iterable const ci;
    move_iterable mi;
    non_iter ni;
    
    {
        BOOST_CHECK(get_end_ptr(i));
        BOOST_CHECK(get_end_ptr((iterable const &)i));
        BOOST_CHECK(get_end_ptr(elib::move(i)));
    }
    {
        BOOST_CHECK(get_end_ptr(ci));
        BOOST_CHECK(get_end_ptr(elib::move(ci)));
    }
    {
        BOOST_CHECK(get_end_ptr(elib::move(mi)));
        BOOST_CHECK(not get_end_ptr(mi));
        BOOST_CHECK(not get_end_ptr(elib::move((move_iterable const &)mi)));
    }
    {
        BOOST_CHECK(not get_end_ptr(ni));
        BOOST_CHECK(not get_end_ptr((non_iter const &)ni));
        BOOST_CHECK(not get_end_ptr(elib::move(ni)));
        BOOST_CHECK(not get_end_ptr(elib::move((non_iter const &)ni)));
    }
}

/// compilation test
BOOST_AUTO_TEST_CASE(adl_begin_test)
{
    iterable i;
    const_iterable const ci;
    move_iterable mi;
    
    {
        iter it = adl_begin(i);
        it = adl_end(i);
        const_iter cit = adl_begin((iterable const &)i);
        cit = adl_end((iterable const &)i);
    }
    {
        const_iter cit = adl_begin(ci);
        cit = adl_end(ci);
    }
    {
        move_iter mit = adl_begin(elib::move(mi));
        mit = adl_end(elib::move(mi));
    }
    BOOST_CHECK(true);
}

BOOST_AUTO_TEST_SUITE_END()