// REQUIRES: ELIB_AUX
#include <elib/aux/traits/is_string_type.hpp>
#include <string>
#include "rapid-cxx-test.hpp"

using namespace elib::aux;

TEST_SUITE(elib_aux_traits_is_string_type_test_suite)

TEST_CASE(is_string_type_void_pointer_test)
{
    TEST_STATIC_ASSERT(not is_string_type<void*>::value);
}

TEST_CASE(is_string_type_void_test)
{
    TEST_STATIC_ASSERT(not is_string_type<void>::value);
}

TEST_CASE(is_string_type_c_string_test)
{
    TEST_STATIC_ASSERT(is_string_type<char*>::value);
    TEST_STATIC_ASSERT(is_string_type<const char*>::value);
    TEST_STATIC_ASSERT(is_string_type<const char* const>::value);
    TEST_STATIC_ASSERT(is_string_type<char* &>::value);
    TEST_STATIC_ASSERT(is_string_type<const char* &>::value);
    TEST_STATIC_ASSERT(is_string_type<const char* const &>::value);
    
    TEST_STATIC_ASSERT(not is_string_type<volatile char*>::value);
    TEST_STATIC_ASSERT(not is_string_type<const volatile char*>::value);
    TEST_STATIC_ASSERT(not is_string_type<volatile char* &>::value);
    TEST_STATIC_ASSERT(not is_string_type<const volatile char* &>::value);
    
}

TEST_CASE(char_array_test)
{
    TEST_STATIC_ASSERT(is_string_type<char[]>::value);
    TEST_STATIC_ASSERT(is_string_type<char[42]>::value);
    TEST_STATIC_ASSERT(is_string_type<const char[]>::value);
    TEST_STATIC_ASSERT(is_string_type<const char[42]>::value);
    TEST_STATIC_ASSERT(is_string_type<char(&)[]>::value);
    TEST_STATIC_ASSERT(is_string_type<char(&)[42]>::value);
    TEST_STATIC_ASSERT(is_string_type<const char(&)[]>::value);
    TEST_STATIC_ASSERT(is_string_type<const char(&)[42]>::value);
    
    TEST_STATIC_ASSERT(not is_string_type<volatile char[]>::value);
    TEST_STATIC_ASSERT(not is_string_type<const volatile char[]>::value);
    TEST_STATIC_ASSERT(not is_string_type<volatile char[42]>::value);
    TEST_STATIC_ASSERT(not is_string_type<const volatile char[42]>::value);
    TEST_STATIC_ASSERT(not is_string_type<volatile char(&)[]>::value);
    TEST_STATIC_ASSERT(not is_string_type<const volatile char(&)[]>::value);
    TEST_STATIC_ASSERT(not is_string_type<volatile char(&)[42]>::value);
    TEST_STATIC_ASSERT(not is_string_type<const volatile char(&)[42]>::value);
    
}

TEST_CASE(string_test)
{
    TEST_STATIC_ASSERT(is_string_type<std::string>::value);
    TEST_STATIC_ASSERT(is_string_type<const std::string>::value);
    TEST_STATIC_ASSERT(is_string_type<std::string &>::value);
    TEST_STATIC_ASSERT(is_string_type<std::string const &>::value);
    TEST_STATIC_ASSERT(is_string_type<std::string &&>::value);
    TEST_STATIC_ASSERT(is_string_type<std::string const &&>::value);
    
    TEST_CHECK(not is_string_type<std::string *>::value);
    
}

TEST_CASE(is_c_string_void_pointer_test)
{
    TEST_STATIC_ASSERT(not is_c_string<void*>::value);
}

TEST_CASE(is_c_string_void_test)
{
    TEST_STATIC_ASSERT(not is_c_string<void>::value);
}

TEST_CASE(is_c_string_c_string_test)
{
    TEST_STATIC_ASSERT(is_c_string<char*>::value);
    TEST_STATIC_ASSERT(is_c_string<const char*>::value);
    TEST_STATIC_ASSERT(is_c_string<const char* const>::value);
    TEST_STATIC_ASSERT(is_c_string<char* &>::value);
    TEST_STATIC_ASSERT(is_c_string<const char* &>::value);
    TEST_STATIC_ASSERT(is_c_string<const char* const &>::value);
    
    TEST_STATIC_ASSERT(not is_c_string<volatile char*>::value);
    TEST_STATIC_ASSERT(not is_c_string<const volatile char*>::value);
    TEST_STATIC_ASSERT(not is_c_string<volatile char* &>::value);
    TEST_STATIC_ASSERT(not is_c_string<const volatile char* &>::value);
    
}

TEST_CASE(is_c_string_char_array_test)
{
    TEST_STATIC_ASSERT(is_c_string<char[]>::value);
    TEST_STATIC_ASSERT(is_c_string<char[42]>::value);
    TEST_STATIC_ASSERT(is_c_string<const char[]>::value);
    TEST_STATIC_ASSERT(is_c_string<const char[42]>::value);
    TEST_STATIC_ASSERT(is_c_string<char(&)[]>::value);
    TEST_STATIC_ASSERT(is_c_string<char(&)[42]>::value);
    TEST_STATIC_ASSERT(is_c_string<const char(&)[]>::value);
    TEST_STATIC_ASSERT(is_c_string<const char(&)[42]>::value);
    
    TEST_STATIC_ASSERT(not is_c_string<volatile char[]>::value);
    TEST_STATIC_ASSERT(not is_c_string<const volatile char[]>::value);
    TEST_STATIC_ASSERT(not is_c_string<volatile char[42]>::value);
    TEST_STATIC_ASSERT(not is_c_string<const volatile char[42]>::value);
    TEST_STATIC_ASSERT(not is_c_string<volatile char(&)[]>::value);
    TEST_STATIC_ASSERT(not is_c_string<const volatile char(&)[]>::value);
    TEST_STATIC_ASSERT(not is_c_string<volatile char(&)[42]>::value);
    TEST_STATIC_ASSERT(not is_c_string<const volatile char(&)[42]>::value);
    
}

TEST_CASE(is_c_string_string_test)
{
    TEST_STATIC_ASSERT(not is_c_string<std::string>::value);
    TEST_STATIC_ASSERT(not is_c_string<const std::string>::value);
    TEST_STATIC_ASSERT(not is_c_string<std::string &>::value);
    TEST_STATIC_ASSERT(not is_c_string<std::string const &>::value);
    TEST_STATIC_ASSERT(not is_c_string<std::string &&>::value);
    TEST_STATIC_ASSERT(not is_c_string<std::string const &&>::value);
    
    TEST_CHECK(not is_c_string<std::string *>::value);
    
}

TEST_SUITE_END()