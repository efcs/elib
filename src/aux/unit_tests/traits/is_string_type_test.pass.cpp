#define BOOST_TEST_MODULE Main
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include <elib/aux/traits/is_string_type.hpp>
#include <elib/aux/static_assert.hpp>
#include <string>

using namespace elib::aux;

BOOST_AUTO_TEST_SUITE(elib_aux_traits_is_string_type_test_suite)

BOOST_AUTO_TEST_CASE(is_string_type_void_pointer_test)
{
    ELIB_STATIC_ASSERT(not is_string_type<void*>::value);
    BOOST_CHECK(true);
}

BOOST_AUTO_TEST_CASE(is_string_type_void_test)
{
    ELIB_STATIC_ASSERT(not is_string_type<void>::value);
    BOOST_CHECK(true);
}

BOOST_AUTO_TEST_CASE(is_string_type_c_string_test)
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

BOOST_AUTO_TEST_CASE(is_c_string_void_pointer_test)
{
    ELIB_STATIC_ASSERT(not is_c_string<void*>::value);
    BOOST_CHECK(true);
}

BOOST_AUTO_TEST_CASE(is_c_string_void_test)
{
    ELIB_STATIC_ASSERT(not is_c_string<void>::value);
    BOOST_CHECK(true);
}

BOOST_AUTO_TEST_CASE(is_c_string_c_string_test)
{
    ELIB_STATIC_ASSERT(is_c_string<char*>::value);
    ELIB_STATIC_ASSERT(is_c_string<const char*>::value);
    ELIB_STATIC_ASSERT(is_c_string<const char* const>::value);
    ELIB_STATIC_ASSERT(is_c_string<char* &>::value);
    ELIB_STATIC_ASSERT(is_c_string<const char* &>::value);
    ELIB_STATIC_ASSERT(is_c_string<const char* const &>::value);
    
    ELIB_STATIC_ASSERT(not is_c_string<volatile char*>::value);
    ELIB_STATIC_ASSERT(not is_c_string<const volatile char*>::value);
    ELIB_STATIC_ASSERT(not is_c_string<volatile char* &>::value);
    ELIB_STATIC_ASSERT(not is_c_string<const volatile char* &>::value);
    
    BOOST_CHECK(true);
}

BOOST_AUTO_TEST_CASE(is_c_string_char_array_test)
{
    ELIB_STATIC_ASSERT(is_c_string<char[]>::value);
    ELIB_STATIC_ASSERT(is_c_string<char[42]>::value);
    ELIB_STATIC_ASSERT(is_c_string<const char[]>::value);
    ELIB_STATIC_ASSERT(is_c_string<const char[42]>::value);
    ELIB_STATIC_ASSERT(is_c_string<char(&)[]>::value);
    ELIB_STATIC_ASSERT(is_c_string<char(&)[42]>::value);
    ELIB_STATIC_ASSERT(is_c_string<const char(&)[]>::value);
    ELIB_STATIC_ASSERT(is_c_string<const char(&)[42]>::value);
    
    ELIB_STATIC_ASSERT(not is_c_string<volatile char[]>::value);
    ELIB_STATIC_ASSERT(not is_c_string<const volatile char[]>::value);
    ELIB_STATIC_ASSERT(not is_c_string<volatile char[42]>::value);
    ELIB_STATIC_ASSERT(not is_c_string<const volatile char[42]>::value);
    ELIB_STATIC_ASSERT(not is_c_string<volatile char(&)[]>::value);
    ELIB_STATIC_ASSERT(not is_c_string<const volatile char(&)[]>::value);
    ELIB_STATIC_ASSERT(not is_c_string<volatile char(&)[42]>::value);
    ELIB_STATIC_ASSERT(not is_c_string<const volatile char(&)[42]>::value);
    
    BOOST_CHECK(true);
}

BOOST_AUTO_TEST_CASE(is_c_string_string_test)
{
    ELIB_STATIC_ASSERT(not is_c_string<std::string>::value);
    ELIB_STATIC_ASSERT(not is_c_string<const std::string>::value);
    ELIB_STATIC_ASSERT(not is_c_string<std::string &>::value);
    ELIB_STATIC_ASSERT(not is_c_string<std::string const &>::value);
    ELIB_STATIC_ASSERT(not is_c_string<std::string &&>::value);
    ELIB_STATIC_ASSERT(not is_c_string<std::string const &&>::value);
    
    BOOST_CHECK(not is_c_string<std::string *>::value);
    
    BOOST_CHECK(true);
}

BOOST_AUTO_TEST_SUITE_END()