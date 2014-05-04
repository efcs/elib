#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include <elib/exception/error_info.hpp>
#include <elib/aux.hpp>

#include <string>

using namespace elib;
using namespace elib::except;

BOOST_AUTO_TEST_SUITE(except_error_info_test_suite)

BOOST_AUTO_TEST_CASE(except_error_info_throw_types)
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

// NOTE: only test failing cases
BOOST_AUTO_TEST_CASE(except_is_error_info_test)
{
    BOOST_CHECK(!is_error_info<void>::value);
    BOOST_CHECK(!is_error_info<int>::value);
}

BOOST_AUTO_TEST_SUITE_END()