#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include <iostream>
#include <string>

#include "elib/optional.hpp"


// instantiation tests
namespace elib
{
    template class optional<int>;
    template class optional<std::string>;
    template class optional<int &>;
    template class optional<std::string &>;
}


using namespace elib;


#if defined(ELIB_CONFIG_COVERITY_SCAN)
# define ELIB_OPTIONAL_CONSTEXPR
#else
# define ELIB_OPTIONAL_CONSTEXPR constexpr
#endif
/// Try and create constexpr optional instances
namespace cexpr_test
{
    using opt = optional<int>;
    ELIB_OPTIONAL_CONSTEXPR int x = 0;
    
    ELIB_OPTIONAL_CONSTEXPR opt o1;
    ELIB_OPTIONAL_CONSTEXPR opt o2(nullopt);
    ELIB_OPTIONAL_CONSTEXPR opt o3(x);
    ELIB_OPTIONAL_CONSTEXPR opt o4(0);
    ELIB_OPTIONAL_CONSTEXPR opt o5(in_place, x);
    ELIB_OPTIONAL_CONSTEXPR opt o6(in_place, 0);
}
#undef ELIB_OPTIONAL_CONSTEXPR

    
BOOST_AUTO_TEST_SUITE(optional_test_suite)

BOOST_AUTO_TEST_CASE(nullopt_ctor_tests)
{
    // trivial type
    {
        using opt = optional<int>;
        
        const opt o1;
        BOOST_CHECK( not o1 );
        BOOST_CHECK( not o1.good() );
        BOOST_CHECK_THROW(o1.value(), bad_optional_access);
        BOOST_CHECK( o1.value_or(1) == 1 );
        
        const opt o2(nullopt);
        BOOST_CHECK( not o2 );
        BOOST_CHECK( not o2.good() );
        BOOST_CHECK_THROW(o2.value(), bad_optional_access);
        BOOST_CHECK( o2.value_or(1) == 1 );
    }
    // non-trivial type
    {
        using opt = optional<std::string>;
        
        std::string s = "Hello";
        
        const opt o1;
        BOOST_CHECK( not o1 );
        BOOST_CHECK( not o1.good() );
        BOOST_CHECK_THROW(o1.value(), bad_optional_access);
        BOOST_CHECK(o1.value_or(s) == s);
        BOOST_CHECK(o1.value_or("Hello") == s);
        
        opt o2(nullopt);
        BOOST_CHECK( not o2 );
        BOOST_CHECK( not o2.good() );
        BOOST_CHECK_THROW(o2.value(), bad_optional_access);
        BOOST_CHECK(o2.value_or(s) == s);
        BOOST_CHECK(o2.value_or("Hello") == s);
    }
    // reference type
    {
        using opt = optional<int &>;
        
        const opt o1;
        BOOST_CHECK( not o1 );
        BOOST_CHECK( not o1.good() );
        BOOST_CHECK_THROW(o1.value(), bad_optional_access);
    }
}

BOOST_AUTO_TEST_CASE(value_construct_ctor)
{
    // trivial type
    {
        using opt = optional<int>;
        
        int x = 1;
        
        {
            const opt o1(x);
            BOOST_CHECK( o1 );
            BOOST_CHECK( o1.good() );
            BOOST_REQUIRE_NO_THROW( o1.value() );
            BOOST_CHECK( o1.value() == 1);
            BOOST_CHECK( *o1 == 1);
        }
        {
            opt o1(x);
            BOOST_CHECK( o1 );
            BOOST_CHECK( o1.good() );
            BOOST_REQUIRE_NO_THROW( o1.value() );
            BOOST_CHECK( o1.value() == 1);
            BOOST_CHECK( *o1 == 1);
        }
        {
            const opt o1(1);
            BOOST_CHECK( o1 );
            BOOST_CHECK( o1.good() );
            BOOST_REQUIRE_NO_THROW( o1.value() );
            BOOST_CHECK( o1.value() == 1);
            BOOST_CHECK( *o1 == 1);
        }
        {
            opt o1(1);
            BOOST_CHECK( o1 );
            BOOST_CHECK( o1.good() );
            BOOST_REQUIRE_NO_THROW( o1.value() );
            BOOST_CHECK( o1.value() == 1);
            BOOST_CHECK( *o1 == 1);
        }
        {
            const opt o1(in_place, x);
            BOOST_CHECK( o1 );
            BOOST_CHECK( o1.good() );
            BOOST_REQUIRE_NO_THROW( o1.value() );
            BOOST_CHECK( o1.value() == 1);
            BOOST_CHECK( *o1 == 1);
        }
        {
            opt o1(in_place, x);
            BOOST_CHECK( o1 );
            BOOST_CHECK( o1.good() );
            BOOST_REQUIRE_NO_THROW( o1.value() );
            BOOST_CHECK( o1.value() == 1);
            BOOST_CHECK( *o1 == 1);
        }
        {
            const opt o1(in_place, 1);
            BOOST_CHECK( o1 );
            BOOST_CHECK( o1.good() );
            BOOST_REQUIRE_NO_THROW( o1.value() );
            BOOST_CHECK( o1.value() == 1);
            BOOST_CHECK( *o1 == 1);
        }
        {
            opt o1(in_place, 1);
            BOOST_CHECK( o1 );
            BOOST_CHECK( o1.good() );
            BOOST_REQUIRE_NO_THROW( o1.value() );
            BOOST_CHECK( o1.value() == 1);
            BOOST_CHECK( *o1 == 1);
        }
        
    }
    // non-trivial test
    {
        using opt = optional<std::string>;
        
        const std::string s("Hello");
        
        {
            const opt o1(s);
            BOOST_CHECK( o1 );
            BOOST_CHECK( o1.good() );
            BOOST_CHECK_NO_THROW( o1.value() );
            BOOST_CHECK( o1.value() == s);
            BOOST_CHECK( *o1 == s );
            BOOST_CHECK( o1->c_str() == s);
        }
        {
            opt o1(s);
            BOOST_CHECK( o1 );
            BOOST_CHECK( o1.good() );
            BOOST_CHECK_NO_THROW( o1.value() );
            BOOST_CHECK( o1.value() == s);
            BOOST_CHECK( *o1 == s );
            BOOST_CHECK( o1->c_str() == s);
        }
        {
            const opt o1(std::string{"Hello"});
            BOOST_CHECK( o1 );
            BOOST_CHECK( o1.good() );
            BOOST_CHECK_NO_THROW( o1.value() );
            BOOST_CHECK( o1.value() == s);
            BOOST_CHECK( *o1 == s );
            BOOST_CHECK( o1->c_str() == s);
        }
        {
            opt o1(std::string{"Hello"});
            BOOST_CHECK( o1 );
            BOOST_CHECK( o1.good() );
            BOOST_CHECK_NO_THROW( o1.value() );
            BOOST_CHECK( o1.value() == s);
            BOOST_CHECK( *o1 == s );
            BOOST_CHECK( o1->c_str() == s);
        }
        {
            const opt o1("Hello");
            BOOST_CHECK( o1 );
            BOOST_CHECK( o1.good() );
            BOOST_CHECK_NO_THROW( o1.value() );
            BOOST_CHECK( o1.value() == s);
            BOOST_CHECK( *o1 == s );
            BOOST_CHECK( o1->c_str() == s);
        }
        {
            opt o1("Hello");
            BOOST_CHECK( o1 );
            BOOST_CHECK( o1.good() );
            BOOST_CHECK_NO_THROW( o1.value() );
            BOOST_CHECK( o1.value() == s);
            BOOST_CHECK( *o1 == s );
            BOOST_CHECK( o1->c_str() == s);
        }
        {
            const opt o1(in_place, s);
            BOOST_CHECK( o1 );
            BOOST_CHECK( o1.good() );
            BOOST_CHECK_NO_THROW( o1.value() );
            BOOST_CHECK( o1.value() == s);
            BOOST_CHECK( *o1 == s );
            BOOST_CHECK( o1->c_str() == s);
        }
        {
            opt o1(in_place, s);
            BOOST_CHECK( o1 );
            BOOST_CHECK( o1.good() );
            BOOST_CHECK_NO_THROW( o1.value() );
            BOOST_CHECK( o1.value() == s);
            BOOST_CHECK( *o1 == s );
            BOOST_CHECK( o1->c_str() == s);
        }
        {
            const opt o1(in_place, "Hello");
            BOOST_CHECK( o1 );
            BOOST_CHECK( o1.good() );
            BOOST_CHECK_NO_THROW( o1.value() );
            BOOST_CHECK( o1.value() == s);
            BOOST_CHECK( *o1 == s );
            BOOST_CHECK( o1->c_str() == s);
        }
        {
            opt o1(in_place, "Hello");
            BOOST_CHECK( o1 );
            BOOST_CHECK( o1.good() );
            BOOST_CHECK_NO_THROW( o1.value() );
            BOOST_CHECK( o1.value() == s);
            BOOST_CHECK( *o1 == s );
            BOOST_CHECK( o1->c_str() == s);
        }
        {
            const opt o1(in_place, {'H', 'e', 'l', 'l', 'o'});
            BOOST_CHECK( o1 );
            BOOST_CHECK( o1.good() );
            BOOST_CHECK_NO_THROW( o1.value() );
            BOOST_CHECK( o1.value() == s);
            BOOST_CHECK( *o1 == s );
            BOOST_CHECK( o1->c_str() == s);
        }
        {
            opt o1(in_place, {'H', 'e', 'l', 'l', 'o'});
            BOOST_CHECK( o1 );
            BOOST_CHECK( o1.good() );
            BOOST_CHECK_NO_THROW( o1.value() );
            BOOST_CHECK( o1.value() == s);
            BOOST_CHECK( *o1 == s );
            BOOST_CHECK( o1->c_str() == s);
        }
    }
    // ref type
    {
        using opt = optional<int &>;
        
        int x = 0;
        
        {
            const opt o1(x);
            BOOST_CHECK( o1 );
            BOOST_CHECK( o1.good() );
            BOOST_REQUIRE_NO_THROW( o1.value() );
            BOOST_CHECK( o1.value() == x );
            BOOST_CHECK( &o1.value() == &x );
            BOOST_CHECK( *o1 == x );
            BOOST_CHECK( &(*o1) == & x);
        }
        {
            opt o1(x);
            BOOST_CHECK( o1 );
            BOOST_CHECK( o1.good() );
            BOOST_REQUIRE_NO_THROW( o1.value() );
            BOOST_CHECK( o1.value() == x );
            BOOST_CHECK( &o1.value() == &x );
            BOOST_CHECK( *o1 == x );
            BOOST_CHECK( &(*o1) == & x);
        }
        {
            const opt o1(in_place, x);
            BOOST_CHECK( o1 );
            BOOST_CHECK( o1.good() );
            BOOST_REQUIRE_NO_THROW( o1.value() );
            BOOST_CHECK( o1.value() == x );
            BOOST_CHECK( &o1.value() == &x );
            BOOST_CHECK( *o1 == x );
            BOOST_CHECK( &(*o1) == & x);
        }
        {
            opt o1(in_place, x);
            BOOST_CHECK( o1 );
            BOOST_CHECK( o1.good() );
            BOOST_REQUIRE_NO_THROW( o1.value() );
            BOOST_CHECK( o1.value() == x );
            BOOST_CHECK( &o1.value() == &x );
            BOOST_CHECK( *o1 == x );
            BOOST_CHECK( &(*o1) == & x);
        }
    }
}

BOOST_AUTO_TEST_CASE(assign_test)
{
    using opt = optional<int>;
    
    // nullopt
    {
        opt o(0);
        o = nullopt;
        BOOST_CHECK(not o);
    }
    // empty brackets
    {
        opt o(0);
        o = {};
        BOOST_CHECK(not o);
    }
    // copy-empty
    {
        opt o;
        const opt o1;
        o = o1;
        BOOST_CHECK(not o);
    }
    // copy non-empty
    {
        opt o;
        const opt o1(0);
        o = o1;
        BOOST_CHECK(o);
    }
    // move empty
    {
        opt o;
        o = opt();
        BOOST_CHECK(not o);
    }
    // move non-empty
    {
        opt o;
        o = opt(0);
        BOOST_CHECK(o);
    }
    // value copy
    {
        opt o;
        int x = 0;
        o = x;
        BOOST_CHECK(o);
    }
    // value move
    {
        opt o;
        o = 0;
        BOOST_CHECK(o);
    }
}

BOOST_AUTO_TEST_CASE(emplace_test)
{
    using opt = optional<std::string>;
    const std::string s("Hello");
    
    // emplace copy
    {
        opt o;
        o.emplace(s);
        BOOST_CHECK(o == s);
    }
    // emplace move
    {
        opt o;
        o.emplace(std::string(s));
        BOOST_CHECK(o == s);
    }
    // emplace c_str
    {
        opt o;
        o.emplace("Hello");
        BOOST_CHECK(o == s);
    }
}

BOOST_AUTO_TEST_CASE(equality_test)
{
    const optional<int> o1;
    const optional<int> o2(0);
    const optional<int> o3(1);
    
    // identity compare
    {
        BOOST_CHECK( o1 == o1 );
        BOOST_CHECK( o2 == o2 );
        
        BOOST_CHECK( not (o1 != o1) );
        BOOST_CHECK( not (o2 != o2) );
        
        BOOST_CHECK( not (o1 < o1) );
        BOOST_CHECK( not (o2 < o2) );
        
        BOOST_CHECK( not (o1 > o1) );
        BOOST_CHECK( not (o2 > o2) );
        
        BOOST_CHECK( o1 <= o1 );
        BOOST_CHECK( o2 <= o2 );
        
        BOOST_CHECK( o1 >= o1 );
        BOOST_CHECK( o2 >= o2 );
    }
    // compare against empty
    {
        BOOST_CHECK( not (o1 == o2) );
        BOOST_CHECK( not (o2 == o1) );
        
        BOOST_CHECK( o1 != o2 );
        BOOST_CHECK( o2 != o1 );
        
        BOOST_CHECK( o1 < o2 );
        BOOST_CHECK( not (o2 < o1) );
        
        BOOST_CHECK( not (o1 > o2) );
        BOOST_CHECK( o2 > o1 );
        
        BOOST_CHECK( o1 <= o2 );
        BOOST_CHECK( not (o2 <= o1) );
        
        BOOST_CHECK( not (o1 >= o2) );
        BOOST_CHECK( o2 >= o1 );
    }
    // compare against different non-empty
    {
        BOOST_CHECK( not (o2 == o3) );
        BOOST_CHECK( not (o3 == o2) );
        
        BOOST_CHECK( o2 != o3 );
        BOOST_CHECK( o3 != o2 );
        
        BOOST_CHECK( o2 < o3 );
        BOOST_CHECK( not (o3 < o2) );
        
        BOOST_CHECK( not (o2 > o3) );
        BOOST_CHECK( o3 > o2 );
        
        BOOST_CHECK( o2 <= o3 );
        BOOST_CHECK( not (o3 <= o2) );
        
        BOOST_CHECK( not (o2 >= o3) );
        BOOST_CHECK( o3 >= o2 );
    }
    // nullopt compare empty
    {
        BOOST_CHECK( o1 == nullopt );
        BOOST_CHECK( nullopt == o1 );
        
        BOOST_CHECK( not (o1 != nullopt) );
        BOOST_CHECK( not (nullopt != o1) );
        
        BOOST_CHECK( not (o1 < nullopt) );
        BOOST_CHECK( not (nullopt < o1) );
        
        BOOST_CHECK( not (o1 > nullopt) );
        BOOST_CHECK( not (nullopt > o1) );
        
        BOOST_CHECK( o1 <= nullopt );
        BOOST_CHECK( nullopt <= o1 );
        
        BOOST_CHECK( o1 >= nullopt );
        BOOST_CHECK( nullopt >= o1 );
    }
    // nullopt compare not empty
    {
        BOOST_CHECK( not (o2 == nullopt) );
        BOOST_CHECK( not (nullopt == o2) );
        
        BOOST_CHECK( o2 != nullopt );
        BOOST_CHECK( nullopt != o2 );
        
        BOOST_CHECK( not (o2 < nullopt) );
        BOOST_CHECK( nullopt < o2 );
        
        BOOST_CHECK( o2 > nullopt );
        BOOST_CHECK( not (nullopt > o2) );
        
        BOOST_CHECK( not (o2 <= nullopt) );
        BOOST_CHECK( nullopt <= o2 );
        
        BOOST_CHECK( o2 >= nullopt );
        BOOST_CHECK( not (nullopt >= o2) );
    }
    // empty compare value
    {
        BOOST_CHECK( not (o1 == 0) );
        BOOST_CHECK( not (0 == o1) );
        
        BOOST_CHECK( o1 != 0 );
        BOOST_CHECK( 0 != o1 );
        
        BOOST_CHECK( o1 < 0 );
        BOOST_CHECK( not (0 < o1) );
        
        BOOST_CHECK( not (o1 > 0) );
        BOOST_CHECK( 0 > o1 );
        
        BOOST_CHECK( o1 <= 0 );
        BOOST_CHECK( not (0 <= o1) );
        
        BOOST_CHECK( not (o1 >= 0) );
        BOOST_CHECK( 0 >= o1 );
    }
    // non-empty compare with value
    {
        BOOST_CHECK( o2 == 0 );
        BOOST_CHECK( 0 == o2 );
        BOOST_CHECK( not (o2 == 1) );
        BOOST_CHECK( not (1 == o2) );
        
        BOOST_CHECK( not (o2 != 0) );
        BOOST_CHECK( not (0 != o2) );
        BOOST_CHECK( o2 != 1 );
        BOOST_CHECK( 1 != o2 );
        
        BOOST_CHECK( not (o2 < 0) );
        BOOST_CHECK( not (0 < o2) );
        BOOST_CHECK( -1 < o2 );
        BOOST_CHECK( not (1 < o2) );
        BOOST_CHECK( o2 < 1 );
        BOOST_CHECK( not (o2 < -1) );
        
        BOOST_CHECK( not (o2 > 0) );
        BOOST_CHECK( not (0 > o2) );
        BOOST_CHECK( 1 > o2 );
        BOOST_CHECK( not (-1 > o2) );
        BOOST_CHECK( o2 > -1 );
        BOOST_CHECK( not (o2 > 1) );
        
        BOOST_CHECK( o2 <= 0 );
        BOOST_CHECK( 0 <= o2 );
        BOOST_CHECK( -1 <= o2 );
        BOOST_CHECK( not (1 <= o2) );
        BOOST_CHECK( o2 <= 1 );
        BOOST_CHECK( not (o2 <= -1) );
        
        BOOST_CHECK( o2 >= 0 );
        BOOST_CHECK( 0 >= o2 );
        BOOST_CHECK( 1 >= o2 );
        BOOST_CHECK( not (-1 >= o2) );
        BOOST_CHECK( o2 >= -1 );
        BOOST_CHECK( not (o2 >= 1) );
    }
}

BOOST_AUTO_TEST_CASE(swap_test)
{
    // non-init values
    {
        
        optional<int> o1;
        optional<int> o2;
        o1.swap(o2);
            
        BOOST_CHECK(not o1);
        BOOST_CHECK(not o2);
            
        swap(o1, o2);
        BOOST_CHECK(not o1);
        BOOST_CHECK(not o2);
    }
    // one init value
    {
        optional<int> o1;
        BOOST_CHECK(not o1);
        
        optional<int> o2(1);
        BOOST_CHECK(o2);
        
        o1.swap(o2);
        BOOST_CHECK(o1);
        BOOST_CHECK(not o2);
        BOOST_REQUIRE_NO_THROW(o1.value());
        BOOST_CHECK(*o1 == 1);
        
        swap(o1, o2);
        BOOST_CHECK(not o1);
        BOOST_CHECK(o2);
        BOOST_REQUIRE_NO_THROW(o2.value());
        BOOST_CHECK(*o2 == 1);
    }
    // both init
    {
        optional<int> o1(1);
        optional<int> o2(2);
        BOOST_CHECK(o1);
        BOOST_CHECK(o2);
        
        o1.swap(o2);
        BOOST_CHECK(o1);
        BOOST_CHECK(o2);
        BOOST_REQUIRE_NO_THROW(o1.value());
        BOOST_REQUIRE_NO_THROW(o2.value());
        BOOST_CHECK(*o1 == 2);
        BOOST_CHECK(*o2 == 1);
        
        swap(o1, o2);
        BOOST_CHECK(o1);
        BOOST_CHECK(o2);
        BOOST_REQUIRE_NO_THROW(o1.value());
        BOOST_REQUIRE_NO_THROW(o2.value());
        BOOST_CHECK(*o1 == 1);
        BOOST_CHECK(*o2 == 2);
    }
}

BOOST_AUTO_TEST_CASE(make_optional_test)
{
    using opt = optional<std::string>;
    std::string s("Hello");
    
    const opt o1(s);
    const opt o2 = make_optional(s);
    BOOST_CHECK(o2);
    BOOST_CHECK(o1 == o2);
}

BOOST_AUTO_TEST_CASE(hash_test)
{
    using opt = optional<std::string>;
    using opt_hash = std::hash<opt>;
    using val_hash = std::hash<std::string>;
    using result_type = opt_hash::result_type;
    
    // empty
    {
        const opt o;
        const opt_hash h{};
        BOOST_CHECK(h(o) == result_type{});
    }
    // non-empty
    {
        const std::string s("Hello");
        const opt o(s);
        const opt_hash oh{};
        const val_hash vh{};
        BOOST_CHECK(oh(o) == vh(s));
    }
}

BOOST_AUTO_TEST_SUITE_END()