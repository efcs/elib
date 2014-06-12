#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE Main
#include <boost/test/unit_test.hpp>

#include <elib/enumeration/basic_traits.hpp>
#include <elib/enumeration/iterator.hpp>
#include <elib/aux.hpp>
#include <iterator>

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

    enum class Empty
    {
    };

}                                                           // namespace
namespace elib { namespace enumeration
{
    
    template <>
    struct basic_enum_traits< ::B>
    {
        static const std::map< ::B, std::string> name_map;
    };
    
    const std::map< ::B, std::string> basic_enum_traits< ::B>::name_map = 
        {
            {::B::none, "none"}
          , {::B::one, "one"}
          , {::B::two, "two"}
        };
        
    template <>
    struct basic_enum_traits< ::Empty>
    {
        static const std::map< ::Empty, std::string> name_map;
    };
    
    const std::map< ::Empty, std::string> basic_enum_traits< ::Empty>::name_map;
}}                                                          // namespace elib

using namespace elib;
using namespace elib::enumeration;

using AIter   = enum_iterator<A>;
using ATraits = std::iterator_traits<AIter>;
using BIter   = enum_iterator<B>;
using BTraits = std::iterator_traits<BIter>;

BOOST_AUTO_TEST_SUITE(enumeration_iterator_test_suite)

BOOST_AUTO_TEST_CASE(traits_test)
{
    static_assert(
        aux::is_same<ATraits::value_type, A const>::value
        , "ATraits::value_type == A"
        );
    static_assert(
        aux::is_same<ATraits::pointer, A const *>::value
        , "ATraits::pointer == A const *"
        );
    static_assert(
        aux::is_same<ATraits::reference, A const &>::value
      , "ATraits::reference == A const &"
      );
    static_assert(
        aux::is_same<ATraits::iterator_category, std::bidirectional_iterator_tag>::value
      , "ATraits::iterator_category == std::bidirectional_iterator_tag"
      );
    
    static_assert(
        aux::is_same<BTraits::value_type, B const>::value
        , "BTraits::value_type == B"
        );
    static_assert(
        aux::is_same<BTraits::pointer, B const *>::value
        , "BTraits::pointer == B const *"
        );
    static_assert(
        aux::is_same<BTraits::reference, B const &>::value
      , "BTraits::reference == B const &"
      );
    static_assert(
        aux::is_same<BTraits::iterator_category, std::bidirectional_iterator_tag>::value
      , "BTraits::iterator_category == std::bidirectional_iterator_tag"
      );
    
    BOOST_CHECK(true);
}

BOOST_AUTO_TEST_CASE(constructor_test)
{
    {
        AIter last;
        AIter first(A::none);
        BOOST_CHECK(*first == A::none);
    }
    {
        BIter last;
        BIter first(B::none);
        BOOST_CHECK(*first == B::none);
    }
}

BOOST_AUTO_TEST_CASE(dereference_test)
{
    {
        const AIter it(A::none);
        BOOST_CHECK(*it == A::none);
        const AIter it2(A::two);
        BOOST_CHECK(*it2 == A::two);
    }
    {
        const BIter it(B::none);
        BOOST_CHECK(*it == B::none);
        const BIter it2(B::two);
        BOOST_CHECK(*it2 == B::two);
    }
}

BOOST_AUTO_TEST_CASE(equality_test)
{
    {
        const AIter last;
        const AIter first(A::none);
        BOOST_CHECK(last == last);
        BOOST_CHECK(first == first);
        BOOST_CHECK(first != last);
    }
    {
        const BIter last;
        const BIter first(B::none);
        BOOST_CHECK(last == last);
        BOOST_CHECK(first == first);
        BOOST_CHECK(first != last);
    }
}

BOOST_AUTO_TEST_CASE(prefix_increment_test)
{
    {
        const AIter last;
        AIter it(A::one);
        BOOST_CHECK(*it == A::one);
        BOOST_CHECK(it != last);
        ++it;
        BOOST_CHECK(*it == A::two);
        BOOST_CHECK(it != last);
        ++it;
        BOOST_CHECK(it == last);
    }
    {
        const BIter last;
        BIter it(B::one);
        BOOST_CHECK(*it == B::one);
        BOOST_CHECK(it != last);
        ++it;
        BOOST_CHECK(*it == B::two);
        BOOST_CHECK(it != last);
        ++it;
        BOOST_CHECK(it == last);
    }
}

BOOST_AUTO_TEST_CASE(postfix_increment_test)
{
    {
        const AIter last;
        AIter it(A::one);
        BOOST_CHECK(*it == A::one);
        BOOST_CHECK(it != last);
        AIter cp = it++;
        BOOST_CHECK(*it == A::two);
        BOOST_CHECK(*cp == A::one);
        cp = it++;
        BOOST_CHECK(it == last);
        BOOST_CHECK(*cp == A::two);
    }
    {
        const BIter last;
        BIter it(B::one);
        BOOST_CHECK(*it == B::one);
        BOOST_CHECK(it != last);
        BIter cp = it++;
        BOOST_CHECK(*it == B::two);
        BOOST_CHECK(*cp == B::one);
        cp = it++;
        BOOST_CHECK(it == last);
        BOOST_CHECK(*cp == B::two);
    }
}

BOOST_AUTO_TEST_CASE(prefix_decrement_test)
{
    {
        AIter first(A::none);
        AIter last;
        AIter it;
        BOOST_CHECK(it == last);
        --it;
        BOOST_REQUIRE(it != last);
        BOOST_CHECK(it != first);
        BOOST_CHECK(*it == A::two);
        --it;
        BOOST_CHECK(it != first);
        BOOST_CHECK(*it == A::one);
        --it;
        BOOST_CHECK(it == first);
        BOOST_CHECK(*it == A::none);
    }
    {
        BIter first(B::none);
        BIter last;
        BIter it;
        BOOST_CHECK(it == last);
        --it;
        BOOST_REQUIRE(it != last);
        BOOST_CHECK(it != first);
        BOOST_CHECK(*it == B::two);
        --it;
        BOOST_CHECK(it != first);
        BOOST_CHECK(*it == B::one);
        --it;
        BOOST_CHECK(it == first);
        BOOST_CHECK(*it == B::none);
    }
}

BOOST_AUTO_TEST_CASE(postfix_decrement_test)
{
    {
        const AIter last;
        const AIter first(A::none);
        AIter it(last);
        BOOST_CHECK(it == last);
        BOOST_CHECK(it != first);
        AIter cp = it--;
        BOOST_CHECK(cp == last);
        BOOST_CHECK(cp != first);
        BOOST_REQUIRE(it != last);
        BOOST_CHECK(it != first);
        BOOST_CHECK(*it == A::two);
        cp = it--;
        BOOST_CHECK(cp != last);
        BOOST_CHECK(it != first);
        BOOST_CHECK(*cp == A::two);
        BOOST_CHECK(*it == A::one);
        cp = it--;
        BOOST_CHECK(cp != last);
        BOOST_CHECK(cp != first);
        BOOST_CHECK(it != last);
        BOOST_CHECK(it == first);
        BOOST_CHECK(*cp == A::one);
        BOOST_CHECK(*it == A::none);
    }
    {
        const BIter last;
        const BIter first(B::none);
        BIter it(last);
        BOOST_CHECK(it == last);
        BOOST_CHECK(it != first);
        BIter cp = it--;
        BOOST_CHECK(cp == last);
        BOOST_CHECK(cp != first);
        BOOST_REQUIRE(it != last);
        BOOST_CHECK(it != first);
        BOOST_CHECK(*it == B::two);
        cp = it--;
        BOOST_CHECK(cp != last);
        BOOST_CHECK(it != first);
        BOOST_CHECK(*cp == B::two);
        BOOST_CHECK(*it == B::one);
        cp = it--;
        BOOST_CHECK(cp != last);
        BOOST_CHECK(cp != first);
        BOOST_CHECK(it != last);
        BOOST_CHECK(it == first);
        BOOST_CHECK(*cp == B::one);
        BOOST_CHECK(*it == B::none);
    }
}

BOOST_AUTO_TEST_SUITE_END()