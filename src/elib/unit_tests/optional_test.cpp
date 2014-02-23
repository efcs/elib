#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include "elib/optional.hpp"
#include "elib/aux.hpp"

#include <string>

using namespace elib;

BOOST_AUTO_TEST_SUITE(elib_optional_test_suite)

BOOST_AUTO_TEST_CASE(elib_optional_ctor_tests)
{
    // ctor 1
    optional<int> o1;
    BOOST_CHECK(!o1);
    
    // ctor 2
    optional<int> o2(nullopt);
    BOOST_CHECK(!o2);
    
    // ctor 3 (copy)
    optional<int> o3(o2);
    BOOST_CHECK(!o3);
    
    // ctor 4 (move)
    optional<int> o4(elib::move(o3));
    BOOST_CHECK(!o4);
    
    // ctor 5 (copy value)
    optional<int> o5(1);
    BOOST_CHECK(bool(o5));
    BOOST_CHECK(o5.value() == 1);
    
    // ctor 6 (move value)
    int x = 1;
    const optional<int> o6(elib::move(x));
    BOOST_CHECK(bool(o6));
    BOOST_CHECK(*o6 == 1);
    
    // ctor 7 (inplace)
    optional<int> o7(in_place, 1);
    BOOST_CHECK(bool(o7));
    BOOST_CHECK(*o7 == 1);
    
    //TODO
    // ctor 8 (inplace, init list)
    // optional<> o8(in_place, std::initializer_list<int>{0, 1});
}

BOOST_AUTO_TEST_SUITE_END()