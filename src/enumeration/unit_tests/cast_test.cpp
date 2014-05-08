#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include <elib/enumeration/basic_traits.hpp>
#include <elib/enumeration/cast.hpp>
#include <elib/enumeration/traits.hpp>

namespace 
{
    enum class A
    {
        none, one, two, 
        ELIB_ENUM_DEFAULT_VALUE = none, 
        ELIB_ENUM_ERROR_VALUE = one, 
        ELIB_ENUM_FIRST_VALUE = none, 
        ELIB_ENUM_LAST_VALUE = two, 
        ELIB_ENUM_IS_CONTIGIOUS = true
    };

    enum class B
    {
        none, one, two
    };

    enum class C
    {
        none, one, two
    };

    enum class D
    {
        none, one, two
    };

    enum class Empty
    {
    };

}                                                           // namespace
namespace elib { namespace enumeration
{
    template <>
    struct basic_enum_traits< ::B>
    {
        static constexpr ::B ELIB_ENUM_DEFAULT_VALUE = ::B::none; 
        static constexpr ::B ELIB_ENUM_ERROR_VALUE = ::B::one;
        
        static constexpr ::B ELIB_ENUM_FIRST_VALUE = ::B::none;
        static constexpr ::B ELIB_ENUM_LAST_VALUE = ::B::two;
        static constexpr bool ELIB_ENUM_IS_CONTIGIOUS = true;
    };
    
    template <>
    struct basic_enum_traits< ::C>
    {
        static const std::map< ::C, std::string> name_map;
    };
    
    const std::map< ::C, std::string> basic_enum_traits< ::C>::name_map = 
        {
            {::C::none, "none"}
          , {::C::one, "one"}
          , {::C::two, "two"}
        };
        
    template <>
    struct basic_enum_traits< ::Empty>
    {
        static const std::map< ::Empty, std::string> name_map;
    };
    
    const std::map< ::Empty, std::string> basic_enum_traits< ::Empty>::name_map = 
        {
        };
}}                                                          // namespace elib

using namespace elib::enumeration;

BOOST_AUTO_TEST_SUITE(enumeration_cast_test_suite)

BOOST_AUTO_TEST_CASE(enumeration_cast_bad_enum_cast_coverage_test)
{
    bad_enum_cast e1("Hello");
    BOOST_CHECK(e1.what() == std::string("Hello"));
    bad_enum_cast e2(std::string("Hello"));
    BOOST_CHECK(e2.what() == std::string("Hello"));
}

BOOST_AUTO_TEST_CASE(enumeration_enum_cast_enum_to_integral)
{
    int dest = 1;
    BOOST_CHECK(enum_cast<int>(A::none, dest));
    BOOST_CHECK(dest == 0);
    BOOST_CHECK(enum_cast<int>(A::one) == 1);
}

BOOST_AUTO_TEST_CASE(enumeration_enum_cast_integral_or_enum_to_enum)
{
    {
        A dest = A::none;
        BOOST_CHECK(enum_cast(1, dest));
        BOOST_CHECK(dest == A::one);
        BOOST_CHECK(not enum_cast(5, dest));
        dest = A::none;
        BOOST_CHECK(enum_cast(B::one, dest));
        BOOST_CHECK(dest == A::one);
        BOOST_CHECK(not enum_cast(static_cast<B>(5), dest));
    }
    {
        C dest = C::none;
        BOOST_CHECK(enum_cast(1, dest));
        BOOST_CHECK(dest == C::one);
        BOOST_CHECK(not enum_cast(5, dest));
        dest = C::none;
        BOOST_CHECK(enum_cast(B::one, dest));
        BOOST_CHECK(dest == C::one);
        BOOST_CHECK(not enum_cast(static_cast<B>(5), dest));
    }
    {
        BOOST_CHECK(enum_cast<A>(1) == A::one);
        BOOST_CHECK_THROW(enum_cast<A>(5), bad_enum_cast);
        BOOST_CHECK(enum_cast<A>(B::one) == A::one);
        BOOST_CHECK_THROW(enum_cast<A>(static_cast<B>(5)), bad_enum_cast);
    }
    {
        BOOST_CHECK(enum_cast<C>(1) == C::one);
        BOOST_CHECK_THROW(enum_cast<C>(5), bad_enum_cast);
        BOOST_CHECK(enum_cast<C>(B::one) == C::one);
        BOOST_CHECK_THROW(enum_cast<C>(static_cast<B>(5)), bad_enum_cast);
    }
}

BOOST_AUTO_TEST_CASE(enumeration_enum_cast_enum_to_string)
{
    BOOST_CHECK(enum_cast<std::string>(C::none) == "none");
    BOOST_CHECK(enum_cast<std::string>(C::two) == "two");
    BOOST_CHECK_THROW(enum_cast<std::string>(static_cast<C>(5)), bad_enum_cast);
}

BOOST_AUTO_TEST_CASE(enumeration_enum_cast_string_to_enum)
{
    BOOST_CHECK(enum_cast<C>("none") == C::none);
    BOOST_CHECK(enum_cast<C>("two") == C::two);
    BOOST_CHECK_THROW(enum_cast<C>(""), bad_enum_cast);
    BOOST_CHECK_THROW(enum_cast<C>("three"), bad_enum_cast);
    
    C dest = C::none;
    BOOST_CHECK(enum_cast("one", dest));
    BOOST_CHECK(dest == C::one);
    dest = C::none;
    BOOST_CHECK(not enum_cast("", dest));
    BOOST_CHECK(not enum_cast("three", dest));
    
    
}

BOOST_AUTO_TEST_SUITE_END()