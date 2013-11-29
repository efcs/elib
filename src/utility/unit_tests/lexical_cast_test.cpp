#define BOOST_DYN_TEST_LINK
#include <boost/test/unit_test.hpp>

#include "elib/utility/lexical_cast.hpp"

#include <string>
#include <cstring>

using namespace elib;

BOOST_AUTO_TEST_SUITE(lexical_cast_test_suite)


BOOST_AUTO_TEST_CASE(string_to_int_test)
{
    int x = 10;
    int dest = 0;
    std::string s = "10";
    
    dest = lexical_cast<int>(s);
    BOOST_CHECK(x == dest);
    
    x = 0;
    dest = 1;
    s = "0";
    dest = lexical_cast<int>(s);
    BOOST_CHECK(x == dest);
}


BOOST_AUTO_TEST_CASE(string_to_float_test)
{
    float x, dest;
    std::string s;
    
    x = 1.0;
    s = "1.0";
    dest = lexical_cast<float>(s);
    BOOST_CHECK(x == dest);
    
    x = 1.234;
    s = "1.234";
    dest = lexical_cast<float>(s);
    BOOST_CHECK(x == dest);
}

BOOST_AUTO_TEST_CASE(int_to_string_test)
{
    int x;
    std::string dest, s;
    
    x = 10;
    s = "10";
    dest = lexical_cast<std::string>(x);
    BOOST_CHECK(s == dest);
}

BOOST_AUTO_TEST_CASE(float_to_string_test)
{
    float x;
    std::string dest, s;
    
    x = 1.234;
    s = "1.234";
    dest = lexical_cast<std::string>(x);
    BOOST_CHECK(s == dest);
}

BOOST_AUTO_TEST_CASE(bool_specialization_test)
{
    bool dest;
    std::string s;
    
    s = "true false";
    dest = lexical_cast<bool>(s);
    BOOST_CHECK(dest == true);
    
    s = "false true";
    dest = lexical_cast<bool>(s);
    BOOST_CHECK(dest == false);
    
    
    s = "1";
    dest = lexical_cast<bool>(s);
    BOOST_CHECK(dest == true);
    
    s = "0 true";
    dest = lexical_cast<bool>(s);
    BOOST_CHECK(dest == false);
    
    dest = lexical_cast<bool>("true");
    BOOST_CHECK(dest == true);
    
    dest = lexical_cast<bool>("false");
    BOOST_CHECK(dest == false);
}

BOOST_AUTO_TEST_CASE(bool_specialization_reverse_test)
{
    bool x;
    std::string dest;
    
    x = true;
    dest = lexical_cast<std::string>(x);
    BOOST_CHECK(dest == "true");
    
    x = false;
    dest = lexical_cast<std::string>(x);
    BOOST_CHECK(dest == "false");
}

BOOST_AUTO_TEST_SUITE_END()