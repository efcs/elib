#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include <elib/aux/literals.hpp>
#include <elib/aux/static_assert.hpp>
#include <string>

using namespace elib;
using namespace elib::aux;

#if !defined(ELIB_CONFIG_COVERITY_SCAN)
BOOST_AUTO_TEST_SUITE(elib_aux_literals_test_suite)

BOOST_AUTO_TEST_CASE(binary_literal_test)
{
    ELIB_STATIC_ASSERT(0_bin == 0);
    ELIB_STATIC_ASSERT(00_bin == 0);
    ELIB_STATIC_ASSERT(000_bin == 0);
    
    ELIB_STATIC_ASSERT(1_bin == 1);
    ELIB_STATIC_ASSERT(01_bin == 1);
    ELIB_STATIC_ASSERT(001_bin == 1);
    
    ELIB_STATIC_ASSERT(10_bin == 2);
    ELIB_STATIC_ASSERT(010_bin == 2);
    
    ELIB_STATIC_ASSERT(11_bin == 3);
    ELIB_STATIC_ASSERT(011_bin == 3);
    
    ELIB_STATIC_ASSERT(100_bin == 4);
    ELIB_STATIC_ASSERT(101_bin == 5);
    ELIB_STATIC_ASSERT(111_bin == 7);
    
    BOOST_CHECK(true);
}

BOOST_AUTO_TEST_CASE(string_to_string_literal_test)
{
    BOOST_CHECK(""_str == "");
    BOOST_CHECK(" "_str == " ");
    BOOST_CHECK("Hello World!\n"_str == "Hello World!\n");
}

BOOST_AUTO_TEST_CASE(number_to_string_literal_test)
{
    BOOST_CHECK(0_str == "0");
    BOOST_CHECK(123467890_str == "123467890");
    
    BOOST_CHECK(0.0_str == "0.0");
    BOOST_CHECK(123.456_str == "123.456");
}

BOOST_AUTO_TEST_SUITE_END()
#endif /* ELIB_CONFIG_COVERITY_SCAN */