// REQUIRES: ELIB_SOURCE
#include <elib/lexical_cast.hpp>
#include <string>
#include <cstring>
#include "rapid-cxx-test.hpp"

using namespace elib;

TEST_SUITE(lexical_cast_test_suite)


TEST_CASE(string_to_int_test)
{
    int x = 10;
    int dest = 0;
    std::string s = "10";
    
    {
        dest = lexical_cast<int>(s);
        TEST_CHECK(x == dest);
    }{
        dest = -1;
        TEST_REQUIRE(lexical_cast(s, dest));
        TEST_REQUIRE(dest == x);
    }
    
    x = 0;
    s = "0";
    {
        
        dest = lexical_cast<int>(s);
        TEST_CHECK(x == dest);
    }{
        dest = -1;
        TEST_REQUIRE(lexical_cast(s, dest));
        TEST_CHECK(dest == x);
    }
}

TEST_CASE(string_to_int_throw_test)
{
    std::string s = "abcd";
    int dest = -1;
    
    TEST_REQUIRE_THROW(bad_lexical_cast, lexical_cast<int>(s));
    TEST_REQUIRE(not lexical_cast(s, dest));
}

TEST_CASE(string_to_float_test)
{
    float x, dest;
    std::string s;
    
    x = 1.0;
    s = "1.0";
    {
        dest = lexical_cast<float>(s);
        TEST_CHECK(x - dest <= 0.005f || x - dest >= 0.005f);
    }{
        dest = -1.0f;
        TEST_REQUIRE(lexical_cast(s, dest));
        TEST_CHECK(x - dest <= 0.005f || x - dest >= 0.005f);
    }
    
    x = 1.234f;
    s = "1.234";
    {
        dest = lexical_cast<float>(s);
        TEST_CHECK(x - dest <= 0.005f || x - dest >= 0.005f);
    }{
        dest = -1.0f;
        TEST_REQUIRE(lexical_cast(s, dest));
        TEST_CHECK(x - dest <= 0.005f || x - dest >= 0.005f);
    }
}

TEST_CASE(string_to_float_throw_test)
{
    std::string s = "abcd";
    float dest{};
    
    TEST_REQUIRE_THROW(bad_lexical_cast, lexical_cast<float>(s));
    TEST_REQUIRE(not lexical_cast(s, dest));
}

TEST_CASE(int_to_string_test)
{
    int x;
    std::string dest, s;
    
    x = 10;
    s = "10";
    {
        dest = lexical_cast<std::string>(x);
        TEST_CHECK(s == dest);
    }{
        dest = "";
        TEST_REQUIRE(lexical_cast(x, dest));
        TEST_CHECK(dest == s);
    }
}

TEST_CASE(float_to_string_test)
{
    float x;
    std::string dest, s;
    
    x = 1.234f;
    s = "1.234";
    {
        dest = lexical_cast<std::string>(x);
        TEST_CHECK(s == dest);
    }{
        dest = "";
        TEST_REQUIRE(lexical_cast(x, dest));
        TEST_REQUIRE(dest == s);
    }
}

TEST_CASE(bool_specialization_test)
{
    bool dest;
    std::string s;
    
    s = "true false";
    dest = lexical_cast<bool>(s);
    TEST_CHECK(dest == true);
    
    s = "false true";
    dest = lexical_cast<bool>(s);
    TEST_CHECK(dest == false);
    
    s = "1";
    dest = lexical_cast<bool>(s);
    TEST_CHECK(dest == true);
    
    s = "0 true";
    dest = lexical_cast<bool>(s);
    TEST_CHECK(dest == false);
    
    dest = lexical_cast<bool>("true");
    TEST_CHECK(dest == true);
    
    dest = lexical_cast<bool>("false");
    TEST_CHECK(dest == false);
}

TEST_CASE(bool_specialization_nothrow_test)
{
    bool dest;
    std::string s;
    
    s = "true false";
    TEST_REQUIRE(lexical_cast(s, dest));
    TEST_CHECK(dest == true);
    
    s = "false true";
    TEST_REQUIRE(lexical_cast(s, dest));
    TEST_CHECK(dest == false);
    
    s = "1";
    TEST_REQUIRE(lexical_cast(s, dest));
    TEST_CHECK(dest == true);
    
    s = "0 true";
    TEST_REQUIRE(lexical_cast(s, dest));
    TEST_CHECK(dest == false);
    
    TEST_REQUIRE(lexical_cast("true", dest));
    TEST_CHECK(dest == true);
    
    TEST_REQUIRE(lexical_cast("false", dest));
    TEST_CHECK(dest == false);
}

TEST_CASE(bool_specialization_throw_test)
{
    const std::string s = "abcd";
    bool dest{};
    
    TEST_REQUIRE_THROW(bad_lexical_cast, lexical_cast<bool>(s));
    TEST_CHECK(not lexical_cast(s, dest));
}

TEST_CASE(bool_specialization_reverse_test)
{
    bool x;
    std::string dest;
    
    x = true;
    dest = lexical_cast<std::string>(x);
    TEST_CHECK(dest == "true");
    
    x = false;
    dest = lexical_cast<std::string>(x);
    TEST_CHECK(dest == "false");
}

TEST_CASE(bool_specialization_reverse_nothrow_test)
{
    std::string dest;
    bool x{};
    
    x = true;
    TEST_REQUIRE(lexical_cast(x, dest));
    TEST_CHECK(dest == "true");
    
    x = false;
    TEST_REQUIRE(lexical_cast(x, dest));
    TEST_CHECK(dest == "false");
}

TEST_CASE(string_to_string_test)
{
    std::string const expect = "Hello World!";
    
    std::string dest;
    {
        dest = lexical_cast<std::string>(expect);
        TEST_CHECK(dest == expect);
    }{
        dest = lexical_cast<std::string>("Hello World!");
        TEST_CHECK(dest == expect);
    }{ 
        dest.clear();
        TEST_REQUIRE(lexical_cast(expect, dest));
        TEST_CHECK(dest == expect);
    }{
        dest.clear();
        TEST_REQUIRE(lexical_cast("Hello World!", dest));
        TEST_CHECK(dest == expect);
    }
}

TEST_SUITE_END()