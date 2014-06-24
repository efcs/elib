// REQUIRES: ELIB_AUX
#include <elib/aux/addressof.hpp>
#include <elib/aux/static_assert.hpp>
#include "rapid-cxx-test.hpp"

#if defined(__GNUC__)
# pragma GCC diagnostic ignored "-Waddress"
#endif

struct has_overload
{
    constexpr has_overload() {}
    
    has_overload* address() { return this; }
    has_overload const * address() const { return this; }
    
    has_overload* operator&() { return nullptr; }
    has_overload const* operator&() const { return nullptr; }
};

struct no_overload
{
    constexpr no_overload() {}
};

using namespace elib::aux;



TEST_SUITE(elib_aux_addressof_test_suite)

TEST_CASE(has_overload_addressof_test)
{
    using detail::has_overload_addressof;
    ELIB_STATIC_ASSERT(not has_overload_addressof<int>::value);
    ELIB_STATIC_ASSERT(not has_overload_addressof<no_overload>::value);
    ELIB_STATIC_ASSERT(has_overload_addressof<has_overload>::value);
}

TEST_CASE(no_overload_constexpr_test)
{
    // int test
    {
        static constexpr int x = 0;
        constexpr int const* xptr1 = &x;
        constexpr int const* xptr2 = addressof(x);
        TEST_CHECK(xptr1);
        TEST_CHECK(xptr2);
        TEST_CHECK(xptr1 == xptr2);
    }
    // no_overload test
    {
        static constexpr no_overload x;
        constexpr no_overload const* xptr1 = addressof(x);
        constexpr no_overload const* xptr2 = &x;
        TEST_CHECK(xptr1);
        TEST_CHECK(xptr2);
        TEST_CHECK(xptr1 == xptr2);
    }
}

TEST_CASE(has_overload_test)
{
    // non-const
    {
        has_overload x;
        // check that operator& is called
        TEST_REQUIRE(&x == nullptr);
        has_overload * xptr1 = x.address();
        has_overload * xptr2 = addressof(x);
        TEST_CHECK(xptr1);
        TEST_CHECK(xptr2);
        TEST_CHECK(xptr1 == xptr2);
    }
    // const
    {
        const has_overload x;
        // check that operator& is called
        TEST_REQUIRE(&x == nullptr);
        has_overload const* xptr1 = x.address();
        has_overload const* xptr2 = addressof(x);
        TEST_CHECK(xptr1);
        TEST_CHECK(xptr2);
        TEST_CHECK(xptr1 == xptr2);
    }
}

TEST_SUITE_END()