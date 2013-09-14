#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include "elib/lock/locking_proxy.hpp"

#define GOOD(x) ((bool)x)

using namespace elib::lock;

struct A {
    int m_x;
};

struct B {
    B(int b) { m_x = b; }
    int m_x;
};

BOOST_AUTO_TEST_SUITE(locking_proxy_test_suite)



BOOST_AUTO_TEST_CASE(test_a)
{
    typedef locking_proxy<A> lw;
    A a;
    lw l{a};
    
    auto guard = l.get_guard();
    BOOST_CHECK(! GOOD(guard));
    guard.lock();
    BOOST_CHECK( GOOD(guard));
    guard.unlock();
    BOOST_CHECK( ! GOOD(guard));
    
}


BOOST_AUTO_TEST_SUITE_END()