#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include <elib/aux/traits/is_string_type.hpp>
#include <elib/aux/static_assert.hpp>
#include <string>

using namespace elib::aux;

BOOST_AUTO_TEST_SUITE(elib_aux_traits_is_string_type_test_suite)

BOOST_AUTO_TEST_CASE(void_pointer_test)
{
    ELIB_STATIC_ASSERT(not is_string_type<void*>::value);
    BOOST_CHECK(true);
}

BOOST_AUTO_TEST_CASE(void_test)
{
    ELIB_STATIC_ASSERT(not is_string_type<void>::value);
    BOOST_CHECK(true);
}

BOOST_AUTO_TEST_CASE(c_string_test)
{
    ELIB_STATIC_ASSERT(is_string_type<char*>::value);
    ELIB_STATIC_ASSERT(is_string_type<const char*>::value);
    ELIB_STATIC_ASSERT(is_string_type<const char* const>::value);
    ELIB_STATIC_ASSERT(is_string_type<char* &>::value);
    ELIB_STATIC_ASSERT(is_string_type<const char* &>::value);
    ELIB_STATIC_ASSERT(is_string_type<const char* const &>::value);
    
    ELIB_STATIC_ASSERT(not is_string_type<volatile char*>::value);
    ELIB_STATIC_ASSERT(not is_string_type<const volatile char*>::value);
    ELIB_STATIC_ASSERT(not is_string_type<volatile char* &>::value);
    ELIB_STATIC_ASSERT(not is_string_type<const volatile char* &>::value);
    
    BOOST_CHECK(true);
}

BOOST_AUTO_TEST_CASE(char_array_test)
{
    ELIB_STATIC_ASSERT(is_string_type<char[]>::value);
    ELIB_STATIC_ASSERT(is_string_type<char[42]>::value);
    ELIB_STATIC_ASSERT(is_string_type<const char[]>::value);
    ELIB_STATIC_ASSERT(is_string_type<const char[42]>::value);
    ELIB_STATIC_ASSERT(is_string_type<char(&)[]>::value);
    ELIB_STATIC_ASSERT(is_string_type<char(&)[42]>::value);
    ELIB_STATIC_ASSERT(is_string_type<const char(&)[]>::value);
    ELIB_STATIC_ASSERT(is_string_type<const char(&)[42]>::value);
    
    ELIB_STATIC_ASSERT(not is_string_type<volatile char[]>::value);
    ELIB_STATIC_ASSERT(not is_string_type<const volatile char[]>::value);
    ELIB_STATIC_ASSERT(not is_string_type<volatile char[42]>::value);
    ELIB_STATIC_ASSERT(not is_string_type<const volatile char[42]>::value);
    ELIB_STATIC_ASSERT(not is_string_type<volatile char(&)[]>::value);
    ELIB_STATIC_ASSERT(not is_string_type<const volatile char(&)[]>::value);
    ELIB_STATIC_ASSERT(not is_string_type<volatile char(&)[42]>::value);
    ELIB_STATIC_ASSERT(not is_string_type<const volatile char(&)[42]>::value);
    
    BOOST_CHECK(true);
}

BOOST_AUTO_TEST_CASE(string_test)
{
    ELIB_STATIC_ASSERT(is_string_type<std::string>::value);
    ELIB_STATIC_ASSERT(is_string_type<const std::string>::value);
    ELIB_STATIC_ASSERT(is_string_type<std::string &>::value);
    ELIB_STATIC_ASSERT(is_string_type<std::string const &>::value);
    ELIB_STATIC_ASSERT(is_string_type<std::string &&>::value);
    ELIB_STATIC_ASSERT(is_string_type<std::string const &&>::value);
    
    BOOST_CHECK(not is_string_type<std::string *>::value);
    
    BOOST_CHECK(true);
}

BOOST_AUTO_TEST_SUITE_END()