#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include <elib/aux/exchange.hpp>
using namespace elib::aux;

struct from_type
{
    from_type() : x(0) {}
    explicit from_type(int xx) : x(xx) {}
    int x;
};

struct dest_nothrow_from_lvalue
{
    dest_nothrow_from_lvalue() : x(0) {}
    explicit dest_nothrow_from_lvalue(int xx) : x(xx) {}
    dest_nothrow_from_lvalue & operator=(from_type const & f) noexcept 
    { 
        x = f.x;
        return *this;
    }
    int x;
};

struct dest_nothrow_from_rvalue
{
    dest_nothrow_from_rvalue() : x(0) {}
    explicit dest_nothrow_from_rvalue(int xx) : x(xx) {}
    dest_nothrow_from_rvalue & operator=(from_type && f) noexcept 
    {
        x = f.x; 
        f.x = -1;
        return *this;
    }
    int x;
};

struct dest_throws_from_lvalue
{
    dest_throws_from_lvalue() : x(0) {}
    explicit dest_throws_from_lvalue(int xx) : x(xx) {}
    dest_throws_from_lvalue & operator=(from_type const & f) noexcept(false) 
    { 
        x = f.x;
        return *this;
    }
        
    int x;
};

struct dest_throws_from_rvalue
{
    dest_throws_from_rvalue() {}
    explicit dest_throws_from_rvalue(int xx) : x(xx) {}
    dest_throws_from_rvalue & operator=(from_type && f) noexcept(false) 
    { 
        x = f.x; 
        f.x = -1;
        return *this;
    }
    int x;
};

BOOST_AUTO_TEST_SUITE(elib_aux_exchange_test_suite)

BOOST_AUTO_TEST_CASE(nothrow_from_lvalue_test)
{
    dest_nothrow_from_lvalue obj(1);
    from_type from(2);
    dest_nothrow_from_lvalue old = elib::aux::exchange(obj, from);
    BOOST_CHECK(obj.x == 2);
    BOOST_CHECK(old.x == 1);
}

BOOST_AUTO_TEST_CASE(nothrow_from_rvalue_test)
{
    dest_nothrow_from_rvalue obj(1);
    dest_nothrow_from_rvalue old = elib::aux::exchange(obj, from_type(2));
    BOOST_CHECK(obj.x == 2);
    BOOST_CHECK(old.x == 1);
}

BOOST_AUTO_TEST_CASE(throws_from_lvalue_test)
{
    dest_throws_from_lvalue obj(1);
    from_type from(2);
    dest_throws_from_lvalue old = elib::aux::exchange(obj, from);
    BOOST_CHECK(obj.x == 2);
    BOOST_CHECK(old.x == 1);
}

BOOST_AUTO_TEST_CASE(throws_from_rvalue_test)
{
    dest_throws_from_rvalue obj(1);
    dest_throws_from_rvalue old = elib::aux::exchange(obj, from_type(2));
    BOOST_CHECK(obj.x == 2);
    BOOST_CHECK(old.x == 1);
}

BOOST_AUTO_TEST_SUITE_END()