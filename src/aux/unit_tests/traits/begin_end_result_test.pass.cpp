// REQUIRES: ELIB_AUX
#include <elib/aux/traits/begin_end_result.hpp>
#include "rapid-cxx-test.hpp"

#if defined(__clang__)
# pragma clang diagnostic ignored "-Wunneeded-internal-declaration"
# pragma clang diagnostic ignored "-Wunused-function"
# pragma clang diagnostic ignored "-Wunused-member-function"
# endif

namespace { namespace adl_barrier
{
    struct iter {};
    struct const_iter {};
    struct move_iter {};
    
    struct iterable {
        constexpr iterable() noexcept {}
    };
    inline iter begin(iterable &) { return {}; }
    inline iter end(iterable &) { return {}; }
    inline const_iter begin(iterable const &) { return {}; }
    inline const_iter end(iterable const &) { return {}; }
    
    struct move_iterable {
        constexpr move_iterable() noexcept {}
    };
    inline move_iter begin(move_iterable &&) { return {}; }
    inline move_iter end(move_iterable &&) { return {}; }
    
    struct const_iterable {
        constexpr const_iterable() noexcept {}
    };
    inline const_iter begin(const_iterable const &) { return {}; }
    inline const_iter end(const_iterable const &) { return {}; }
    
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

TEST_SUITE(elib_aux_traits_begin_end_result_test_suite)

TEST_CASE(iterable_test)
{
    TEST_SAME_TYPE(begin_result_t<iterable &>, iter);
    TEST_SAME_TYPE(end_result_t<iterable &>, iter);
    TEST_SAME_TYPE(begin_result_t<iterable const &>, const_iter);
    TEST_SAME_TYPE(end_result_t<iterable const &>, const_iter);
}

TEST_CASE(const_iterable_test)
{
    TEST_SAME_TYPE(begin_result_t<const_iterable &>, const_iter);
    TEST_SAME_TYPE(end_result_t<const_iterable &>, const_iter);
    TEST_SAME_TYPE(begin_result_t<const_iterable const &>, const_iter);
    TEST_SAME_TYPE(end_result_t<const_iterable const &>, const_iter);
}

TEST_CASE(move_iterable_test)
{
    TEST_SAME_TYPE(begin_result_t<move_iterable>, move_iter);
    TEST_SAME_TYPE(end_result_t<move_iterable>, move_iter);
}

TEST_CASE(member_iterable_test)
{
    TEST_SAME_TYPE(begin_result_t<member_iterable &>, iter);
    TEST_SAME_TYPE(end_result_t<member_iterable &>, iter);
    TEST_SAME_TYPE(begin_result_t<member_iterable const &>, const_iter);
    TEST_SAME_TYPE(end_result_t<member_iterable const &>, const_iter);
}

TEST_CASE(array_iterable_test)
{
    TEST_SAME_TYPE(begin_result_t<array_iterable>, int*);
    TEST_SAME_TYPE(end_result_t<array_iterable>, int*);
}

TEST_CASE(const_array_iterable_test)
{
    TEST_SAME_TYPE(begin_result_t<const_array_iterable>, int const*);
    TEST_SAME_TYPE(end_result_t<const_array_iterable>, int const*);
}

TEST_SUITE_END()