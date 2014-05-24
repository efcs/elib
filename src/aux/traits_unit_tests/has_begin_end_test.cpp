#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include <elib/aux/traits/has_begin_end.hpp>
#include <elib/aux/static_assert.hpp>
#include <iterator>

#if defined(__clang__)
# pragma clang diagnostic ignored "-Wunneeded-internal-declaration"
# pragma clang diagnostic ignored "-Wunused-function"
# endif

namespace { namespace adl_barrier
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
    
    struct member_iterable {
        constexpr member_iterable() noexcept {}
        iter begin() { return {}; }
        iter end() { return {}; }
        const_iter begin() const { return {}; }
        const_iter end() const { return {}; }
    };
    
    struct non_iter {};
}}

using adl_barrier::iter;
using adl_barrier::const_iter;
using adl_barrier::move_iter;

using adl_barrier::iterable;
using adl_barrier::const_iterable;
using adl_barrier::move_iterable;
using adl_barrier::member_iterable;
using array_iterable = int(&)[5];

using adl_barrier::non_iter;

using namespace elib::aux;

BOOST_AUTO_TEST_SUITE(elib_aux_traits_has_begin_end_test_suite)

BOOST_AUTO_TEST_CASE(has_begin_iterable_test)
{
    ELIB_STATIC_ASSERT(has_begin<iterable>::value);
    ELIB_STATIC_ASSERT(has_begin<iterable const>::value);
    ELIB_STATIC_ASSERT(has_begin<iterable &>::value);
    ELIB_STATIC_ASSERT(has_begin<iterable const &>::value);
    BOOST_CHECK(true);
}

BOOST_AUTO_TEST_CASE(has_begin_const_iterable_test)
{
    ELIB_STATIC_ASSERT(has_begin<const_iterable>::value);
    ELIB_STATIC_ASSERT(has_begin<const_iterable const>::value);
    ELIB_STATIC_ASSERT(has_begin<const_iterable &>::value);
    ELIB_STATIC_ASSERT(has_begin<const_iterable const &>::value);
    BOOST_CHECK(true);
}

BOOST_AUTO_TEST_CASE(has_begin_move_iterable_test)
{
    ELIB_STATIC_ASSERT(has_begin<move_iterable>::value);
    ELIB_STATIC_ASSERT(not has_begin<move_iterable const>::value);
    ELIB_STATIC_ASSERT(not has_begin<move_iterable &>::value);
    ELIB_STATIC_ASSERT(not has_begin<move_iterable const &>::value);
    BOOST_CHECK(true);
}

BOOST_AUTO_TEST_CASE(has_begin_member_iterable_test)
{
    ELIB_STATIC_ASSERT(has_begin<member_iterable>::value);
    ELIB_STATIC_ASSERT(has_begin<member_iterable const>::value);
    ELIB_STATIC_ASSERT(has_begin<member_iterable &>::value);
    ELIB_STATIC_ASSERT(has_begin<member_iterable const &>::value);
    BOOST_CHECK(true);
}

BOOST_AUTO_TEST_CASE(has_begin_array_iterable_test)
{
    ELIB_STATIC_ASSERT(has_begin<array_iterable>::value);
    ELIB_STATIC_ASSERT(has_begin<array_iterable const>::value);
    ELIB_STATIC_ASSERT(has_begin<array_iterable &>::value);
    ELIB_STATIC_ASSERT(has_begin<array_iterable const &>::value);
    BOOST_CHECK(true);
}

BOOST_AUTO_TEST_CASE(has_begin_non_iterable_test)
{
    ELIB_STATIC_ASSERT(not has_begin<non_iter>::value);
    ELIB_STATIC_ASSERT(not has_begin<non_iter const>::value);
    ELIB_STATIC_ASSERT(not has_begin<non_iter &>::value);
    ELIB_STATIC_ASSERT(not has_begin<non_iter const &>::value);
    BOOST_CHECK(true);
}

BOOST_AUTO_TEST_CASE(has_end_iterable_test)
{
    ELIB_STATIC_ASSERT(has_end<iterable>::value);
    ELIB_STATIC_ASSERT(has_end<iterable const>::value);
    ELIB_STATIC_ASSERT(has_end<iterable &>::value);
    ELIB_STATIC_ASSERT(has_end<iterable const &>::value);
    BOOST_CHECK(true);
}

BOOST_AUTO_TEST_CASE(has_end_const_iterable_test)
{
    ELIB_STATIC_ASSERT(has_end<const_iterable>::value);
    ELIB_STATIC_ASSERT(has_end<const_iterable const>::value);
    ELIB_STATIC_ASSERT(has_end<const_iterable &>::value);
    ELIB_STATIC_ASSERT(has_end<const_iterable const &>::value);
    BOOST_CHECK(true);
}

BOOST_AUTO_TEST_CASE(has_end_move_iterable_test)
{
    ELIB_STATIC_ASSERT(has_end<move_iterable>::value);
    ELIB_STATIC_ASSERT(not has_end<move_iterable const>::value);
    ELIB_STATIC_ASSERT(not has_end<move_iterable &>::value);
    ELIB_STATIC_ASSERT(not has_end<move_iterable const &>::value);
    BOOST_CHECK(true);
}

BOOST_AUTO_TEST_CASE(has_end_member_iterable_test)
{
    ELIB_STATIC_ASSERT(has_end<member_iterable>::value);
    ELIB_STATIC_ASSERT(has_end<member_iterable const>::value);
    ELIB_STATIC_ASSERT(has_end<member_iterable &>::value);
    ELIB_STATIC_ASSERT(has_end<member_iterable const &>::value);
    BOOST_CHECK(true);
}

BOOST_AUTO_TEST_CASE(has_end_array_iterable_test)
{
    ELIB_STATIC_ASSERT(has_end<array_iterable>::value);
    ELIB_STATIC_ASSERT(has_end<array_iterable const>::value);
    ELIB_STATIC_ASSERT(has_end<array_iterable &>::value);
    ELIB_STATIC_ASSERT(has_end<array_iterable const &>::value);
    BOOST_CHECK(true);
}

BOOST_AUTO_TEST_CASE(has_end_non_iterable_test)
{
    ELIB_STATIC_ASSERT(not has_end<non_iter>::value);
    ELIB_STATIC_ASSERT(not has_end<non_iter const>::value);
    ELIB_STATIC_ASSERT(not has_end<non_iter &>::value);
    ELIB_STATIC_ASSERT(not has_end<non_iter const &>::value);
    BOOST_CHECK(true);
}


BOOST_AUTO_TEST_SUITE_END()