#define BOOST_DYN_TEST_LINK
#include <boost/test/unit_test.hpp>

#include "elib/static_string.h"

#include <string>
#include <cstring>

using namespace elib;

BOOST_AUTO_TEST_SUITE(static_string_test_suite)

constexpr static_string empty{""};
constexpr static_string s{"abcd"};
constexpr static_string copy = s;

BOOST_AUTO_TEST_CASE(test_construct)
{
    
    BOOST_CHECK(strcmp(empty, "") == 0);
    BOOST_CHECK(strcmp(s, "abcd") == 0);
    BOOST_CHECK(strcmp(s, copy) == 0);
}

BOOST_AUTO_TEST_CASE(test_constexpr_access)
{
    {
        constexpr char c = empty[0];
        BOOST_CHECK(c == '\0');
    }
    
    {
        constexpr char c = s[0];
        BOOST_CHECK(c == 'a');
    }
    
    {
        constexpr char c = s[4];
        BOOST_CHECK(c == '\0');
    }
    
    {
        constexpr char c = copy[1];
        BOOST_CHECK(c == 'b');
    }
    
}

BOOST_AUTO_TEST_CASE(test_size)
{
    BOOST_CHECK(empty.size() == 0);
    BOOST_CHECK(s.size() == 4);
    BOOST_CHECK(copy.size() == s.size());
}

BOOST_AUTO_TEST_SUITE_END()