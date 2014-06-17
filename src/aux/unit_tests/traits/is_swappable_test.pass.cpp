// REQUIRES: ELIB_AUX_SOURCE
#include <elib/aux/traits/is_swappable.hpp>
#include "rapid-cxx-test.hpp"
using namespace elib::aux;

#if defined(__clang__)
# pragma clang diagnostic ignored "-Wunneeded-internal-declaration"
# pragma clang diagnostic ignored "-Wunused-member-function"
#endif

namespace { namespace adl_blocker
{
    struct swap_t {
        int value;
        
        explicit swap_t(int x) : value(x) {}
        swap_t(swap_t &&) = delete;
    };
    
    inline void swap(swap_t & lhs, swap_t & rhs) 
    {
        int tmp = lhs.value;
        lhs.value = rhs.value;
        rhs.value = tmp;
    }
    
    struct nothrow_swap_t {
        int value;
        
        explicit nothrow_swap_t(int x) : value(x) {}
        nothrow_swap_t(nothrow_swap_t &&) = delete;
    };
    
    inline void swap(nothrow_swap_t & lhs, nothrow_swap_t & rhs) noexcept
    {
        int tmp = lhs.value;
        lhs.value = rhs.value;
        rhs.value = tmp;
    }
    
    struct default_swap_t {
        int value;
    };
    
    struct non_swap_t {
        non_swap_t() = default;
        non_swap_t(non_swap_t &&) = delete;
    };
}}                                                           // namespace adl_blocker

using adl_blocker::swap_t;
using adl_blocker::nothrow_swap_t;
using adl_blocker::default_swap_t;
using array_swap_t = default_swap_t(&)[42];
using adl_blocker::non_swap_t;


TEST_SUITE(elib_aux_traits_is_swappable_test_suite)

TEST_CASE(swap_type_test)
{
    TEST_STATIC_ASSERT(detail::is_array_swappable<array_swap_t, array_swap_t>::value);
    
    TEST_STATIC_ASSERT(is_swappable<swap_t>::value);
    TEST_STATIC_ASSERT(is_swappable<nothrow_swap_t>::value);
    TEST_STATIC_ASSERT(is_swappable<default_swap_t>::value);
    TEST_STATIC_ASSERT(is_swappable<array_swap_t>::value);
    TEST_STATIC_ASSERT(not is_swappable<non_swap_t>::value);
}

TEST_CASE(swap_const_test)
{
    TEST_STATIC_ASSERT(not is_swappable<swap_t const>::value);
}

TEST_CASE(swap_mixed_type_test)
{
    TEST_STATIC_ASSERT(not is_swappable<swap_t, nothrow_swap_t>::value);
    TEST_STATIC_ASSERT(not is_swappable<default_swap_t, default_swap_t*>::value);
    TEST_STATIC_ASSERT(not is_swappable<swap_t, array_swap_t>::value);
}

TEST_SUITE_END()