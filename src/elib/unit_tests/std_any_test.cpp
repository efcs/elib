#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include <elib/std_any.hpp>
#include <string>

using namespace elib;

BOOST_AUTO_TEST_SUITE(elib_std_any_test_suite)

BOOST_AUTO_TEST_CASE(elib_std_any_empty_test)
{
    const std_any a;
    BOOST_CHECK(a.type() == typeid(void));
    BOOST_CHECK(a.empty());
    BOOST_CHECK( !((bool)a) );
}

BOOST_AUTO_TEST_CASE(elib_std_any_int_value_test)
{
    std_any a = 3;
    BOOST_CHECK(!a.empty());
    BOOST_CHECK( ((bool)a) );
    BOOST_REQUIRE(a.type() == typeid(int));
    BOOST_CHECK(std_any_cast<int>(a) == 3);
    
    int bi = 5;
    std_any b = bi;
    BOOST_CHECK(!b.empty());
    BOOST_CHECK( ((bool)b) );
    BOOST_REQUIRE(b.type() == typeid(int));
    BOOST_CHECK(std_any_cast<int>(b) == 5);
    
    swap(a, b);
    BOOST_CHECK(!a.empty() && !b.empty());
    BOOST_CHECK(a.type() == typeid(int));
    BOOST_CHECK(b.type() == typeid(int));
    BOOST_CHECK(std_any_cast<int>(a) == 5);
    BOOST_CHECK(std_any_cast<int>(b) == 3);
}

BOOST_AUTO_TEST_CASE(elib_std_any_cast_test)
{
    std_any a1(3);
    
    BOOST_CHECK( std_any_cast<int>(a1) == 3 );
    int & a1_ref = std_any_cast<int &>(a1);
    a1_ref = 5;
    BOOST_CHECK( std_any_cast<int>(a1) == 5 );
    BOOST_CHECK( &a1_ref == &std_any_cast<int &>(a1) );
    
    BOOST_CHECK_THROW(std_any_cast<float>(a1), bad_std_any_cast);
    BOOST_CHECK_THROW(std_any_cast<int*>(a1), bad_std_any_cast);
    BOOST_CHECK_THROW(std_any_cast<std::string>(a1), bad_std_any_cast);
    
    BOOST_CHECK(std_any_cast<float>(&a1) == nullptr);
    BOOST_CHECK(std_any_cast<int*>(&a1) == nullptr);
    BOOST_CHECK(std_any_cast<std::string>(&a1) == nullptr);
}

BOOST_AUTO_TEST_SUITE_END()