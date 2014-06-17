// REQUIRES: ELIB_ENUMERATION_SOURCE
#include <elib/enumeration/basic_traits.hpp>
#include <elib/enumeration/traits.hpp>
#include <map>
#include <string>
#include "rapid-cxx-test.hpp"

#if defined(__clang__)
# pragma clang diagnostic ignored "-Wduplicate-enum"
# pragma clang diagnostic ignored "-Wglobal-constructors"
# pragma clang diagnostic ignored "-Wexit-time-destructors"
#endif

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
    
    const std::map< ::Empty, std::string> basic_enum_traits< ::Empty>::name_map;
    
}}                                                          // namespace elib

using namespace elib::enumeration;

TEST_SUITE(enumeration_traits_test_suite)

TEST_CASE(enumeration_traits_enum_traits_A_test)
{
    using tr = enum_traits<A>;
    static_assert(
        not tr::has_name_map, "no name map"
    );
    static_assert(
        tr::has_default_value, "has default"
    );
     static_assert(
        tr::default_value == A::none, "default == none"
    );
    static_assert(
        tr::has_error_value, "has error"
    );
     static_assert(
        tr::error_value == A::one, "error == one"
    );
    static_assert(
        tr::has_first_value, "has first"
    );
    static_assert(
        tr::first_value == A::none, "first == none"
    );
    static_assert(
        tr::has_last_value, "has last"
    );
    static_assert(
        tr::last_value == A::two, "last == two"
    );
    static_assert(
        tr::has_is_contigious, "has is_contigious"
    );
    static_assert(
        tr::is_contigious, "is contigious"
    );
    TEST_CHECK(true);
}

TEST_CASE(enumeration_traits_enum_traits_B_test)
{
    using tr = enum_traits<B>;
    static_assert(
        not tr::has_name_map, "no name map"
    );
    static_assert(
        tr::has_default_value, "has default"
    );
     static_assert(
        tr::default_value == B::none, "default == none"
    );
    static_assert(
        tr::has_error_value, "has error"
    );
     static_assert(
        tr::error_value == B::one, "error == one"
    );
    static_assert(
        tr::has_first_value, "has first"
    );
    static_assert(
        tr::first_value == B::none, "first == none"
    );
    static_assert(
        tr::has_last_value, "has last"
    );
    static_assert(
        tr::last_value == B::two, "last == two"
    );
    static_assert(
        tr::has_is_contigious, "has is_contigious"
    );
    static_assert(
        tr::is_contigious, "is contigious"
    );
    TEST_CHECK(true);
}

TEST_CASE(enumeration_traits_enum_traits_C_test)
{
    using tr = enum_traits<C>;
    static_assert(
        tr::has_name_map, "has name map"
    );
    static_assert(
        not tr::has_default_value, "does not have default"
    );
    static_assert(
        not tr::has_error_value, "does not have error"
    );
    static_assert(
        not tr::has_first_value, "does not have first"
    );
    static_assert(
        not tr::has_last_value, "does not have last"
    );
    static_assert(
        not tr::has_is_contigious, "does not have is_contigious"
    );
    TEST_CHECK(true);
}

TEST_CASE(enumeration_traits_enum_traits_D_test)
{
    using tr = enum_traits<D>;
    static_assert(
        not tr::has_name_map, "does not have name map"
    );
    static_assert(
        not tr::has_default_value, "does not have default"
    );
    static_assert(
        not tr::has_error_value, "does not have error"
    );
    static_assert(
        not tr::has_first_value, "does not have first"
    );
    static_assert(
        not tr::has_last_value, "does not have last"
    );
    static_assert(
        not tr::has_is_contigious, "does not have is_contigious"
    );
    TEST_CHECK(true);
}

TEST_CASE(enumeration_has_range_test)
{
    static_assert(has_range<A>::value, "A has range");
    static_assert(has_range<B>::value, "C has range");
    static_assert(has_range<C>::value, "B has range");
    static_assert(not has_range<D>::value, "D does not have range");
    TEST_CHECK(true);
}

TEST_CASE(enumeration_has_constexpr_range_test)
{
    static_assert(has_constexpr_range<A>::value, "A has constexpr range");
    static_assert(has_constexpr_range<B>::value, "B has constexpr range");
    static_assert(not has_constexpr_range<C>::value, "C does not have constexpr range");
    static_assert(not has_constexpr_range<D>::value, "D does not have constexpr range");
    TEST_CHECK(true);
}

TEST_CASE(enumeration_default_value_test)
{
    static_assert(
        default_value<A>() == A::none, "default == none"
    );
    static_assert(
        default_value<B>() == B::none, "default == none"
    );
    TEST_CHECK(default_value<A>() == A::none);
    TEST_CHECK(default_value<B>() == B::none);
}

TEST_CASE(enumeration_error_value_test)
{
    static_assert(
        error_value<A>() == A::one, "error == one"
    );
    static_assert(
        error_value<B>() == B::one, "error == one"
    );
    TEST_CHECK(error_value<A>() == A::one);
    TEST_CHECK(error_value<B>() == B::one);
}

TEST_CASE(enumeration_traits_first_value_test)
{
    static_assert(
        first_value<A>() == A::none, "first == none"
    );
    static_assert(
        first_value<B>() == B::none, "first == none"
    );
    TEST_CHECK(first_value<A>() == A::none);
    TEST_CHECK(first_value<B>() == B::none);
    TEST_CHECK(first_value<C>() == C::none);
}


TEST_CASE(enumeration_traits_last_value_test)
{
    static_assert(
        last_value<A>() == A::two, "last == two"
    );
    static_assert(
        last_value<B>() == B::two, "last == two"
    );
    TEST_CHECK(last_value<A>() == A::two);
    TEST_CHECK(last_value<B>() == B::two);
    TEST_CHECK(last_value<C>() == C::two);
}

TEST_CASE(enumeration_traits_size_test)
{
    static_assert(
        size<A>() == 3, "size == 3"
    );
    static_assert(
        size<B>() == 3, "size == 3"
    );
    TEST_CHECK(size<A>() == 3);
    TEST_CHECK(size<B>() == 3);
    TEST_CHECK(size<C>() == 3);
}

TEST_CASE(enumeration_is_contigious_test)
{
    static_assert(
        is_contigious<A>() == true, "is_contigious == true"
    );
    static_assert(
        is_contigious<B>() == true, "is_contigious == true"
    );
    TEST_CHECK(is_contigious<A>());
    TEST_CHECK(is_contigious<B>());
    TEST_CHECK(is_contigious<C>());
}

TEST_CASE(enumeration_in_range_test)
{
    static_assert(
        in_range(A::none), "in range"
    );
    static_assert(
        in_range(A::two), "in range"
    );
    static_assert(
        not in_range(static_cast<A>(3)), "in range"
    );
    static_assert(
        in_range(B::none), "in range"
    );
    static_assert(
        in_range(B::two), "in range"
    );
    static_assert(
        not in_range(static_cast<A>(3)), "in range"
    );
    TEST_CHECK(in_range(A::none));
    TEST_CHECK(in_range(A::two));
    TEST_CHECK(not in_range(static_cast<A>(3)));
    TEST_CHECK(in_range(B::none));
    TEST_CHECK(in_range(B::two));
    TEST_CHECK(not in_range(static_cast<B>(3)));
    TEST_CHECK(in_range(C::none));
    TEST_CHECK(in_range(C::two));
    TEST_CHECK(not in_range(static_cast<C>(3)));
    TEST_CHECK(not in_range(static_cast<Empty>(0)));
}

TEST_SUITE_END()