// REQUIRES: ELIB_EXCEPTION
#include <elib/exception/error_info.hpp>
#include <elib/aux.hpp>
#include <string>
#include "rapid-cxx-test.hpp"

using namespace elib;
using namespace elib::except;

struct DummyTag {};
using Info = error_info<DummyTag, std::string>;

TEST_SUITE(except_error_info_test_suite)

TEST_CASE(is_error_info_test)
{
    static_assert(
        not is_error_info<void>::value, "Void is not error info"
    );
    static_assert(
        is_error_info<Info>::value, "Info is error info"
    );
}

TEST_CASE(constructor_test)
{
    // from lvalue
    {
        const std::string s("Hello");
        Info i(s);
        TEST_CHECK(i.value() == s);
    }
    // from rvalue
    {
        std::string s("Hello");
        Info i(elib::move(s));
        TEST_CHECK(i.value() == "Hello");
    }
}

TEST_CASE(value_test)
{
    const std::string s("Hello");
    //const value test
    {
        const Info i(s);
        TEST_CHECK(i.value() == s);
    }
    // non-const value test
    {
        Info i(s);
        TEST_CHECK(i.value() == s);
        i.value() = "Not Hello";
        TEST_CHECK(i.value() != s);
    }
}

TEST_CASE(throw_types_test)
{
    throw_func func(__func__);
    TEST_CHECK(func.value() == std::string{__func__});
    TEST_CHECK((aux::is_same<typename throw_func::tag_type, tags::throw_func>::value));
    TEST_CHECK((aux::is_same<typename throw_func::value_type, const char*>::value));
    TEST_CHECK(is_error_info<throw_func>::value);
    
    throw_line line(__LINE__);
    TEST_CHECK(line.value() == __LINE__ - 1);
    TEST_CHECK((aux::is_same<typename throw_line::tag_type, tags::throw_line>::value));
    TEST_CHECK((aux::is_same<typename throw_line::value_type, unsigned>::value));
    TEST_CHECK(is_error_info<throw_line>::value);
    
    throw_file file(__FILE__);
    TEST_CHECK(file.value() == std::string{__FILE__});
    TEST_CHECK((aux::is_same<typename throw_file::tag_type, tags::throw_file>::value));
    TEST_CHECK((aux::is_same<typename throw_file::value_type, const char*>::value));
    TEST_CHECK(is_error_info<throw_file>::value);
}

TEST_SUITE_END()