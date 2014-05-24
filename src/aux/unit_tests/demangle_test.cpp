#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include <elib/aux/demangle.hpp>
#include <string>
#include <typeinfo>

struct plain_struct 
{
};

template <class T1, class T2, class T3>
struct template_struct {};


using plain_alias = template_struct<int, void, int>;

template <class T1, class T2>
using alias_template = template_struct<T1, T2, T1>;


template <class T>
void test_function()
{
    std::string ret;
    
    std::string ret1 = elib::aux::demangle(typeid(T).name());
    BOOST_CHECK(not ret1.empty());
    
    std::string ret2 = elib::aux::demangle(std::string(typeid(T).name()));
    BOOST_CHECK(not ret2.empty());
    
    std::string ret3 = elib::aux::demangle(typeid(T));
    BOOST_CHECK(not ret3.empty());
    
    std::string ret4 = elib::aux::demangle<T>();
    BOOST_CHECK(not ret4.empty());
    
    BOOST_REQUIRE(ret1 == ret2);
    BOOST_REQUIRE(ret1 == ret3);
    BOOST_REQUIRE(ret1 == ret4);
}

BOOST_AUTO_TEST_SUITE(elib_aux_demangle_test_suite)

BOOST_AUTO_TEST_CASE(plain_struct_test)
{
    using T = plain_struct;
    test_function<T>();
    BOOST_CHECK(true);
}

BOOST_AUTO_TEST_CASE(template_struct_test)
{
    // simple
    {
        using T = template_struct<int, long, void>;
        test_function<T>();
    }
    // nested
    {
        using T = template_struct<
            template_struct<long, void, template_struct<long, long, long>>
          , plain_struct
          , void>;
        test_function<T>();
    }
    BOOST_CHECK(true);
}

BOOST_AUTO_TEST_CASE(plain_function_test)
{
    using T = int(plain_struct, long, template_struct<long, long, int()>);
    test_function<T>();
}

BOOST_AUTO_TEST_CASE(function_pointer_test)
{
    using T = void(*)(plain_struct, long);
    test_function<T>();
}

BOOST_AUTO_TEST_CASE(member_function_pointer_test)
{
    using T = int(plain_struct::*)(long, plain_struct);
    test_function<T>();
}

BOOST_AUTO_TEST_CASE(plain_alias_test)
{
    using T = plain_alias;
    test_function<T>();
}

BOOST_AUTO_TEST_CASE(template_alias_test)
{
    using T = alias_template<plain_struct, void>;
    test_function<T>();
}

BOOST_AUTO_TEST_CASE(pointer_type_test)
{
    using T = template_struct<void, long, int> const*;
    test_function<T>();
}

BOOST_AUTO_TEST_SUITE_END()