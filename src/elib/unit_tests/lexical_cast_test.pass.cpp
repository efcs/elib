// REQUIRES: ELIB_SOURCE, ELIB_BOOST_TEST
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE Main
#include <boost/test/unit_test.hpp>

#include <elib/lexical_cast.hpp>

#include <string>
#include <cstring>

using namespace elib;

BOOST_AUTO_TEST_SUITE(lexical_cast_test_suite)


BOOST_AUTO_TEST_CASE(string_to_int_test)
{
    int x = 10;
    int dest = 0;
    std::string s = "10";
    
    {
        dest = lexical_cast<int>(s);
        BOOST_CHECK(x == dest);
    }{
        dest = -1;
        BOOST_REQUIRE(lexical_cast(s, dest));
        BOOST_REQUIRE(dest == x);
    }
    
    x = 0;
    s = "0";
    {
        
        dest = lexical_cast<int>(s);
        BOOST_CHECK(x == dest);
    }{
        dest = -1;
        BOOST_REQUIRE(lexical_cast(s, dest));
        BOOST_CHECK(dest == x);
    }
}

BOOST_AUTO_TEST_CASE(string_to_int_throw_test)
{
    std::string s = "abcd";
    int dest = -1;
    
    BOOST_REQUIRE_THROW(lexical_cast<int>(s), bad_lexical_cast);
    BOOST_REQUIRE(not lexical_cast(s, dest));
}

BOOST_AUTO_TEST_CASE(string_to_float_test)
{
    float x, dest;
    std::string s;
    
    x = 1.0;
    s = "1.0";
    {
        dest = lexical_cast<float>(s);
        BOOST_CHECK(x - dest <= 0.005f || x - dest >= 0.005f);
    }{
        dest = -1.0f;
        BOOST_REQUIRE(lexical_cast(s, dest));
        BOOST_CHECK(x - dest <= 0.005f || x - dest >= 0.005f);
    }
    
    x = 1.234f;
    s = "1.234";
    {
        dest = lexical_cast<float>(s);
        BOOST_CHECK(x - dest <= 0.005f || x - dest >= 0.005f);
    }{
        dest = -1.0f;
        BOOST_REQUIRE(lexical_cast(s, dest));
        BOOST_CHECK(x - dest <= 0.005f || x - dest >= 0.005f);
    }
}

BOOST_AUTO_TEST_CASE(string_to_float_throw_test)
{
    std::string s = "abcd";
    float dest{};
    
    BOOST_REQUIRE_THROW(lexical_cast<float>(s), bad_lexical_cast);
    BOOST_REQUIRE(not lexical_cast(s, dest));
}

BOOST_AUTO_TEST_CASE(int_to_string_test)
{
    int x;
    std::string dest, s;
    
    x = 10;
    s = "10";
    {
        dest = lexical_cast<std::string>(x);
        BOOST_CHECK(s == dest);
    }{
        dest = "";
        BOOST_REQUIRE(lexical_cast(x, dest));
        BOOST_CHECK(dest == s);
    }
}

BOOST_AUTO_TEST_CASE(float_to_string_test)
{
    float x;
    std::string dest, s;
    
    x = 1.234f;
    s = "1.234";
    {
        dest = lexical_cast<std::string>(x);
        BOOST_CHECK(s == dest);
    }{
        dest = "";
        BOOST_REQUIRE(lexical_cast(x, dest));
        BOOST_REQUIRE(dest == s);
    }
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

BOOST_AUTO_TEST_CASE(bool_specialization_nothrow_test)
{
    bool dest;
    std::string s;
    
    s = "true false";
    BOOST_REQUIRE(lexical_cast(s, dest));
    BOOST_CHECK(dest == true);
    
    s = "false true";
    BOOST_REQUIRE(lexical_cast(s, dest));
    BOOST_CHECK(dest == false);
    
    s = "1";
    BOOST_REQUIRE(lexical_cast(s, dest));
    BOOST_CHECK(dest == true);
    
    s = "0 true";
    BOOST_REQUIRE(lexical_cast(s, dest));
    BOOST_CHECK(dest == false);
    
    BOOST_REQUIRE(lexical_cast("true", dest));
    BOOST_CHECK(dest == true);
    
    BOOST_REQUIRE(lexical_cast("false", dest));
    BOOST_CHECK(dest == false);
}

BOOST_AUTO_TEST_CASE(bool_specialization_throw_test)
{
    const std::string s = "abcd";
    bool dest{};
    
    BOOST_REQUIRE_THROW(lexical_cast<bool>(s), bad_lexical_cast);
    BOOST_CHECK(not lexical_cast(s, dest));
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

BOOST_AUTO_TEST_CASE(bool_specialization_reverse_nothrow_test)
{
    std::string dest;
    bool x{};
    
    x = true;
    BOOST_REQUIRE(lexical_cast(x, dest));
    BOOST_CHECK(dest == "true");
    
    x = false;
    BOOST_REQUIRE(lexical_cast(x, dest));
    BOOST_CHECK(dest == "false");
}

BOOST_AUTO_TEST_CASE(string_to_string_test)
{
    std::string const expect = "Hello World!";
    
    std::string dest;
    {
        dest = lexical_cast<std::string>(expect);
        BOOST_CHECK(dest == expect);
    }{
        dest = lexical_cast<std::string>("Hello World!");
        BOOST_CHECK(dest == expect);
    }{ 
        dest.clear();
        BOOST_REQUIRE(lexical_cast(expect, dest));
        BOOST_CHECK(dest == expect);
    }{
        dest.clear();
        BOOST_REQUIRE(lexical_cast("Hello World!", dest));
        BOOST_CHECK(dest == expect);
    }
}

BOOST_AUTO_TEST_SUITE_END()