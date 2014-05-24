#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include <elib/aux/traits/begin_end_result.hpp>
#include <elib/aux/traits/is_same.hpp>
#include <elib/aux/static_assert.hpp>

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
using const_array_iterable  = int const(&)[5];

using adl_barrier::non_iter;

using namespace elib::aux;

#define CHECK_SAME(...) ELIB_STATIC_ASSERT(is_same<__VA_ARGS__>::value)

BOOST_AUTO_TEST_SUITE(elib_aux_traits_begin_end_result_test_suite)

BOOST_AUTO_TEST_CASE(iterable_test)
{
    CHECK_SAME(begin_result_t<iterable &>, iter);
    CHECK_SAME(end_result_t<iterable &>, iter);
    CHECK_SAME(begin_result_t<iterable const &>, const_iter);
    CHECK_SAME(end_result_t<iterable const &>, const_iter);
    BOOST_CHECK(true);
}

BOOST_AUTO_TEST_CASE(const_iterable_test)
{
    CHECK_SAME(begin_result_t<const_iterable &>, const_iter);
    CHECK_SAME(end_result_t<const_iterable &>, const_iter);
    CHECK_SAME(begin_result_t<const_iterable const &>, const_iter);
    CHECK_SAME(end_result_t<const_iterable const &>, const_iter);
    BOOST_CHECK(true);
}

BOOST_AUTO_TEST_CASE(move_iterable_test)
{
    CHECK_SAME(begin_result_t<move_iterable>, move_iter);
    CHECK_SAME(end_result_t<move_iterable>, move_iter);
    BOOST_CHECK(true);
}

BOOST_AUTO_TEST_CASE(member_iterable_test)
{
    CHECK_SAME(begin_result_t<member_iterable &>, iter);
    CHECK_SAME(end_result_t<member_iterable &>, iter);
    CHECK_SAME(begin_result_t<member_iterable const &>, const_iter);
    CHECK_SAME(end_result_t<member_iterable const &>, const_iter);
    BOOST_CHECK(true);
}

BOOST_AUTO_TEST_CASE(array_iterable_test)
{
    CHECK_SAME(begin_result_t<array_iterable>, int*);
    CHECK_SAME(end_result_t<array_iterable>, int*);
    BOOST_CHECK(true);
}

BOOST_AUTO_TEST_CASE(const_array_iterable_test)
{
    CHECK_SAME(begin_result_t<const_array_iterable>, int const*);
    CHECK_SAME(end_result_t<const_array_iterable>, int const*);
    BOOST_CHECK(true);
}

BOOST_AUTO_TEST_SUITE_END()