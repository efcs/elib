// REQUIRES: ELIB_AUX_SOURCE, ELIB_BOOST_TEST
#define BOOST_TEST_MODULE Main
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include <elib/aux/addressof.hpp>
#include <elib/aux/static_assert.hpp>

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



BOOST_AUTO_TEST_SUITE(elib_aux_addressof_test_suite)

BOOST_AUTO_TEST_CASE(has_overload_addressof_test)
{
    using detail::has_overload_addressof;
    ELIB_STATIC_ASSERT(not has_overload_addressof<int>::value);
    ELIB_STATIC_ASSERT(not has_overload_addressof<no_overload>::value);
    ELIB_STATIC_ASSERT(has_overload_addressof<has_overload>::value);
    BOOST_CHECK(true);
}

BOOST_AUTO_TEST_CASE(no_overload_constexpr_test)
{
    // int test
    {
        static constexpr int x = 0;
        constexpr int const* xptr1 = &x;
        constexpr int const* xptr2 = addressof(x);
        BOOST_CHECK(xptr1);
        BOOST_CHECK(xptr2);
        BOOST_CHECK(xptr1 == xptr2);
    }
    // no_overload test
    {
        static constexpr no_overload x;
        constexpr no_overload const* xptr1 = addressof(x);
        constexpr no_overload const* xptr2 = &x;
        BOOST_CHECK(xptr1);
        BOOST_CHECK(xptr2);
        BOOST_CHECK(xptr1 == xptr2);
    }
}

BOOST_AUTO_TEST_CASE(has_overload_test)
{
    // non-const
    {
        has_overload x;
        // check that operator& is called
        BOOST_REQUIRE(&x == nullptr);
        has_overload * xptr1 = x.address();
        has_overload * xptr2 = addressof(x);
        BOOST_CHECK(xptr1);
        BOOST_CHECK(xptr2);
        BOOST_CHECK(xptr1 == xptr2);
    }
    // const
    {
        const has_overload x;
        // check that operator& is called
        BOOST_REQUIRE(&x == nullptr);
        has_overload const* xptr1 = x.address();
        has_overload const* xptr2 = addressof(x);
        BOOST_CHECK(xptr1);
        BOOST_CHECK(xptr2);
        BOOST_CHECK(xptr1 == xptr2);
    }
}

BOOST_AUTO_TEST_SUITE_END()