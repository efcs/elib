#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include <elib/aux/swap.hpp>
#include <elib/aux/static_assert.hpp>

using namespace elib;

namespace adl_blocker
{
    struct swap_t {
        int value;
        
        explicit swap_t(int x) : value(x) {}
        swap_t(swap_t &&) = delete;
    };
    
    void swap(swap_t & lhs, swap_t & rhs) 
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
    
    void swap(nothrow_swap_t & lhs, nothrow_swap_t & rhs) noexcept
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
}                                                           // namespace adl_blocker

using adl_blocker::swap_t;
using adl_blocker::nothrow_swap_t;
using adl_blocker::default_swap_t;
using adl_blocker::non_swap_t;

BOOST_AUTO_TEST_SUITE(elib_aux_swap_test_suite)

BOOST_AUTO_TEST_CASE(get_swap_pass_has_swap_test)
{
    auto ret = aux::get_swap<swap_t, swap_t>();
    BOOST_REQUIRE(ret);
    
    swap_t lhs{0};
    swap_t rhs{1};
    ret(lhs, rhs);
    BOOST_CHECK(lhs.value == 1);
    BOOST_CHECK(rhs.value == 0);
}

BOOST_AUTO_TEST_CASE(get_swap_pass_default_swap_test)
{
    auto ret = aux::get_swap<default_swap_t, default_swap_t>();
    BOOST_REQUIRE(ret);
    
    default_swap_t lhs{0};
    default_swap_t rhs{1};
    ret(lhs, rhs);
    BOOST_CHECK(lhs.value == 1);
    BOOST_CHECK(rhs.value == 0);
}

BOOST_AUTO_TEST_CASE(get_swap_ptr_pass_has_swap_test)
{
    auto ret = aux::get_swap_ptr<swap_t, swap_t>();
    BOOST_REQUIRE(ret);
    
    swap_t lhs{0};
    swap_t rhs{1};
    ret(lhs, rhs);
    BOOST_CHECK(lhs.value == 1);
    BOOST_CHECK(rhs.value == 0);
}

BOOST_AUTO_TEST_CASE(get_swap_ptr_pass_default_swap_test)
{
    auto ret = aux::get_swap_ptr<default_swap_t, default_swap_t>();
    BOOST_REQUIRE(ret);
    
    default_swap_t lhs{0};
    default_swap_t rhs{1};
    ret(lhs, rhs);
    BOOST_CHECK(lhs.value == 1);
    BOOST_CHECK(rhs.value == 0);
}

BOOST_AUTO_TEST_CASE(get_swap_ptr_fail_test)
{
    auto ret = aux::get_swap_ptr<non_swap_t, non_swap_t>();
    BOOST_CHECK(not ret);
}

BOOST_AUTO_TEST_CASE(get_noexcept_swap_pass_test)
{
    auto ret = aux::get_noexcept_swap<nothrow_swap_t, nothrow_swap_t>();
    BOOST_REQUIRE(ret);
    
    nothrow_swap_t lhs{0};
    nothrow_swap_t rhs{1};
    ret(lhs, rhs);
    BOOST_CHECK(lhs.value == 1);
    BOOST_CHECK(rhs.value == 0);
}

BOOST_AUTO_TEST_CASE(get_noexcept_swap_pass_default_swap_test)
{
    auto ret = aux::get_noexcept_swap<default_swap_t, default_swap_t>();
    BOOST_REQUIRE(ret);
    
    default_swap_t lhs{0};
    default_swap_t rhs{1};
    ret(lhs, rhs);
    BOOST_CHECK(lhs.value == 1);
    BOOST_CHECK(rhs.value == 0);
}

BOOST_AUTO_TEST_CASE(get_noexcept_swap_ptr_pass_test)
{
    auto ret = aux::get_noexcept_swap_ptr<nothrow_swap_t, nothrow_swap_t>();
    BOOST_REQUIRE(ret);
    
    nothrow_swap_t lhs{0};
    nothrow_swap_t rhs{1};
    ret(lhs, rhs);
    BOOST_CHECK(lhs.value == 1);
    BOOST_CHECK(rhs.value == 0);
}

BOOST_AUTO_TEST_CASE(get_noexcept_swap_ptr_pass_default_swap_test)
{
    auto ret = aux::get_noexcept_swap_ptr<default_swap_t, default_swap_t>();
    BOOST_REQUIRE(ret);
    
    default_swap_t lhs{0};
    default_swap_t rhs{1};
    ret(lhs, rhs);
    BOOST_CHECK(lhs.value == 1);
    BOOST_CHECK(rhs.value == 0);
}

BOOST_AUTO_TEST_CASE(get_noexcept_swap_ptr_fail_not_noexcept_test)
{
    auto ret = aux::get_noexcept_swap_ptr<swap_t, swap_t>();
    BOOST_CHECK(not ret);
}

BOOST_AUTO_TEST_CASE(get_noexcept_swap_ptr_fail_not_swappable_test)
{
    auto ret = aux::get_noexcept_swap_ptr<non_swap_t, non_swap_t>();
    BOOST_CHECK(not ret);
}

BOOST_AUTO_TEST_CASE(adl_swap_has_swap_test)
{
    swap_t lhs{0};
    swap_t rhs{1};
    
    elib::adl_swap(lhs, rhs);
    BOOST_CHECK(lhs.value == 1);
    BOOST_CHECK(rhs.value == 0);
}

BOOST_AUTO_TEST_CASE(adl_swap_default_swap_test)
{
    default_swap_t lhs{0};
    default_swap_t rhs{1};
    
    elib::adl_swap(lhs, rhs);
    BOOST_CHECK(lhs.value == 1);
    BOOST_CHECK(rhs.value == 0);
}

BOOST_AUTO_TEST_SUITE_END()