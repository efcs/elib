// REQUIRES: ELIB_EXCEPTION_SOURCE, ELIB_BOOST_TEST
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE Main
#include <boost/test/unit_test.hpp>

#include <elib/exception/error_info.hpp>
#include <elib/aux.hpp>

#include <string>

using namespace elib;
using namespace elib::except;

struct DummyTag {};
using Info = error_info<DummyTag, std::string>;

BOOST_AUTO_TEST_SUITE(except_error_info_test_suite)

BOOST_AUTO_TEST_CASE(is_error_info_test)
{
    static_assert(
        not is_error_info<void>::value, "Void is not error info"
    );
    static_assert(
        is_error_info<Info>::value, "Info is error info"
    );
    BOOST_CHECK(true);
}

BOOST_AUTO_TEST_CASE(constructor_test)
{
    // from lvalue
    {
        const std::string s("Hello");
        Info i(s);
        BOOST_CHECK(i.value() == s);
    }
    // from rvalue
    {
        std::string s("Hello");
        Info i(elib::move(s));
        BOOST_CHECK(i.value() == "Hello");
    }
}

BOOST_AUTO_TEST_CASE(value_test)
{
    const std::string s("Hello");
    //const value test
    {
        const Info i(s);
        BOOST_CHECK(i.value() == s);
    }
    // non-const value test
    {
        Info i(s);
        BOOST_CHECK(i.value() == s);
        i.value() = "Not Hello";
        BOOST_CHECK(i.value() != s);
    }
}

BOOST_AUTO_TEST_CASE(throw_types_test)
{
    throw_func func(__func__);
    BOOST_CHECK(func.value() == std::string{__func__});
    BOOST_CHECK((aux::is_same<typename throw_func::tag_type, tags::throw_func>::value));
    BOOST_CHECK((aux::is_same<typename throw_func::value_type, const char*>::value));
    BOOST_CHECK(is_error_info<throw_func>::value);
    
    throw_line line(__LINE__);
    BOOST_CHECK(line.value() == __LINE__ - 1);
    BOOST_CHECK((aux::is_same<typename throw_line::tag_type, tags::throw_line>::value));
    BOOST_CHECK((aux::is_same<typename throw_line::value_type, unsigned>::value));
    BOOST_CHECK(is_error_info<throw_line>::value);
    
    throw_file file(__FILE__);
    BOOST_CHECK(file.value() == std::string{__FILE__});
    BOOST_CHECK((aux::is_same<typename throw_file::tag_type, tags::throw_file>::value));
    BOOST_CHECK((aux::is_same<typename throw_file::value_type, const char*>::value));
    BOOST_CHECK(is_error_info<throw_file>::value);
}

BOOST_AUTO_TEST_SUITE_END()