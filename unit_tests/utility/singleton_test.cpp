#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include "elib/utility/singleton.hpp"


#define COUNT test_struct::count


using namespace elib;

struct test_struct {
    test_struct() { ++count; }
    
    test_struct(int x) { count += x; }
    
    static void reset() { count = 0; }
        
    static int count;
};

int test_struct::count = 0;

typedef static_singleton<test_struct> stest;

BOOST_AUTO_TEST_SUITE(test_singleton)

BOOST_AUTO_TEST_CASE(singleton_test1)
{
    BOOST_CHECK(COUNT == 0);
    stest::construct();
    BOOST_CHECK(COUNT == 1);
    stest::construct(3);
    BOOST_CHECK(COUNT == 4);
}

BOOST_AUTO_TEST_SUITE_END()