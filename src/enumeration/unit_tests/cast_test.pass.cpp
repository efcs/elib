// REQUIRES: ELIB_ENUMERATION_SOURCE
#include <elib/enumeration/basic_traits.hpp>
#include <elib/enumeration/cast.hpp>
#include <elib/enumeration/traits.hpp>
#include "test/helper.hpp"

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
    
    const std::map< ::Empty, std::string> basic_enum_traits< ::Empty>::name_map;
}}                                                          // namespace elib

using namespace elib::enumeration;

TEST_CASE(enumeration_cast_test_suite)
{

    // enumeration_cast_bad_enum_cast_coverage_test)
    {
        bad_enum_cast e1("Hello");
        TEST_CHECK(e1.what() == std::string("Hello"));
        bad_enum_cast e2(std::string("Hello"));
        TEST_CHECK(e2.what() == std::string("Hello"));
    }

    // enumeration_enum_cast_enum_to_integral)
    {
        int dest = 1;
        TEST_CHECK(enum_cast<int>(A::none, dest));
        TEST_CHECK(dest == 0);
        TEST_CHECK(enum_cast<int>(A::one) == 1);
    }

    // enumeration_enum_cast_integral_or_enum_to_enum)
    {
        {
            A dest = A::none;
            TEST_CHECK(enum_cast(1, dest));
            TEST_CHECK(dest == A::one);
            TEST_CHECK(not enum_cast(5, dest));
            dest = A::none;
            TEST_CHECK(enum_cast(B::one, dest));
            TEST_CHECK(dest == A::one);
            TEST_CHECK(not enum_cast(static_cast<B>(5), dest));
        }
        {
            C dest = C::none;
            TEST_CHECK(enum_cast(1, dest));
            TEST_CHECK(dest == C::one);
            TEST_CHECK(not enum_cast(5, dest));
            dest = C::none;
            TEST_CHECK(enum_cast(B::one, dest));
            TEST_CHECK(dest == C::one);
            TEST_CHECK(not enum_cast(static_cast<B>(5), dest));
        }
        {
            TEST_CHECK(enum_cast<A>(1) == A::one);
            TEST_THROWS(enum_cast<A>(5), bad_enum_cast);
            TEST_CHECK(enum_cast<A>(B::one) == A::one);
            TEST_THROWS(enum_cast<A>(static_cast<B>(5)), bad_enum_cast);
        }
        {
            TEST_CHECK(enum_cast<C>(1) == C::one);
            TEST_THROWS(enum_cast<C>(5), bad_enum_cast);
            TEST_CHECK(enum_cast<C>(B::one) == C::one);
            TEST_THROWS(enum_cast<C>(static_cast<B>(5)), bad_enum_cast);
        }
    }

    // enumeration_enum_cast_enum_to_string)
    {
        TEST_CHECK(enum_cast<std::string>(C::none) == "none");
        TEST_CHECK(enum_cast<std::string>(C::two) == "two");
        TEST_THROWS(enum_cast<std::string>(static_cast<C>(5)), bad_enum_cast);
    }

    // enumeration_enum_cast_string_to_enum)
    {
        TEST_CHECK(enum_cast<C>("none") == C::none);
        TEST_CHECK(enum_cast<C>("two") == C::two);
        TEST_THROWS(enum_cast<C>(""), bad_enum_cast);
        TEST_THROWS(enum_cast<C>("three"), bad_enum_cast);
        
        C dest = C::none;
        TEST_CHECK(enum_cast("one", dest));
        TEST_CHECK(dest == C::one);
        dest = C::none;
        TEST_CHECK(not enum_cast("", dest));
        TEST_CHECK(not enum_cast("three", dest));
    }
}