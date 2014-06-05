#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include <iostream>
#include <string>

#include <elib/config.hpp>
#include <elib/optional.hpp>


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

BOOST_AUTO_TEST_CASE(trivial_default_ctor_test)
{
    using opt = elib::optional<int>;
    opt o;
    BOOST_CHECK(not o.good());
}

BOOST_AUTO_TEST_CASE(non_trivial_default_ctor_test)
{
    using opt = elib::optional<std::string>;
    opt o;
    BOOST_CHECK(not o.good());
}

BOOST_AUTO_TEST_CASE(ref_default_ctor_test)
{
    using opt = elib::optional<int &>;
    opt o;
    BOOST_CHECK(not o.good());
}

BOOST_AUTO_TEST_CASE(trivial_nullopt_ctor_test)
{
    using opt = elib::optional<int>;
    opt o(nullopt);
    BOOST_CHECK(not o.good());
}

BOOST_AUTO_TEST_CASE(non_trivial_nullopt_ctor_test)
{
    using opt = elib::optional<std::string>;
    opt o(nullopt);
    BOOST_CHECK(not o.good());
}

BOOST_AUTO_TEST_CASE(ref_nullopt_ctor_test)
{
    using opt = elib::optional<int &>;
    opt o(nullopt);
    BOOST_CHECK(not o.good());
}

BOOST_AUTO_TEST_CASE(trivial_copy_ctor_test)
{
    using opt = elib::optional<int>;
    {
        opt const o1;
        opt o2(o1);
        BOOST_CHECK(not o2.good());
    }{
        opt const o1(42);
        opt o2(o1);
        BOOST_REQUIRE(o2.good());
        BOOST_CHECK(o2.value() == 42);
    }
}

BOOST_AUTO_TEST_CASE(non_trivial_copy_ctor_test)
{
    using opt = elib::optional<std::string>;
    {
        opt const o1;
        opt o2(o1);
        BOOST_CHECK(not o2.good());
    }{
        opt const o1("hello");
        opt o2(o1);
        BOOST_REQUIRE(o2.good());
        BOOST_CHECK(o2.value() == "hello");
    }
}

BOOST_AUTO_TEST_CASE(ref_copy_ctor_test)
{
    using opt = elib::optional<int &>;
    {
        opt const o1;
        opt o2(o1);
        BOOST_CHECK(not o2.good());
    }{
        int x;
        opt const o1(x);
        opt o2(o1);
        BOOST_REQUIRE(o2.good());
        BOOST_CHECK(&o2.value() == &x);
    }
}

BOOST_AUTO_TEST_CASE(trivial_move_ctor_test)
{
    using opt = elib::optional<int>;
    {
        opt o1;
        opt o2(static_cast<opt &&>(o1));
        BOOST_CHECK(not o2.good());
    }{
        opt o1(42);
        opt o2(static_cast<opt &&>(o1));
        BOOST_REQUIRE(o2.good());
        BOOST_CHECK(o2.value() == 42);
    }
}

BOOST_AUTO_TEST_CASE(non_trivial_move_ctor_test)
{
    using opt = elib::optional<std::string>;
    {
        opt o1;
        opt o2(static_cast<opt &&>(o1));
        BOOST_CHECK(not o2.good());
    }{
        opt o1("hello");
        opt o2(static_cast<opt &&>(o1));
        BOOST_REQUIRE(o2.good());
        BOOST_CHECK(o2.value() == "hello");
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

BOOST_AUTO_TEST_CASE(non_trivial_copy_assign_test)
{
    using opt = optional<std::string>;
    
    std::string const bad = "bad";
    std::string const value = "hello";
    
    // to init
    {
        opt to(value);
        opt from;
        to = from;
        BOOST_CHECK(not to.good());
    }{ /* from init */
        opt to;
        opt from(value);
        to = from;
        BOOST_REQUIRE(to.good());
        BOOST_CHECK(to.value() == value);
    }{ /* both init */
        opt to(bad);
        opt from(value);
        to = from;
        BOOST_REQUIRE(to.good());
        BOOST_CHECK(to.value() == value);
    }
}

BOOST_AUTO_TEST_CASE(trivial_copy_assign_test)
{
    using opt = optional<int>;
    
    int const bad = -1;
    int const value = 42;
    
    // to init
    {
        opt to(value);
        opt from;
        to = from;
        BOOST_CHECK(not to.good());
    }{ /* from init */
        opt to;
        opt from(value);
        to = from;
        BOOST_REQUIRE(to.good());
        BOOST_CHECK(to.value() == value);
    }{ /* both init */
        opt to(bad);
        opt from(value);
        to = from;
        BOOST_REQUIRE(to.good());
        BOOST_CHECK(to.value() == value);
    }
}


BOOST_AUTO_TEST_CASE(non_trivial_move_assign_test)
{
    using opt = optional<std::string>;
    
    std::string const bad = "bad";
    std::string const value = "hello";
    
    // to init
    {
        opt to(value);
        opt from;
        to = static_cast<opt &&>(from);
        BOOST_CHECK(not to.good());
    }{ /* from init */
        opt to;
        opt from(value);
        to = static_cast<opt &&>(from);
        BOOST_REQUIRE(to.good());
        BOOST_CHECK(to.value() == value);
    }{ /* both init */
        opt to(bad);
        opt from(value);
        to = static_cast<opt &&>(from);
        BOOST_REQUIRE(to.good());
        BOOST_CHECK(to.value() == value);
    }
}

BOOST_AUTO_TEST_CASE(trivial_move_assign_test)
{
    using opt = optional<int>;
    
    int const bad = -1;
    int const value = 42;
    
    // to init
    {
        opt to(value);
        opt from;
        to = static_cast<opt &&>(from);
        BOOST_CHECK(not to.good());
    }{ /* from init */
        opt to;
        opt from(value);
        to = static_cast<opt &&>(from);
        BOOST_REQUIRE(to.good());
        BOOST_CHECK(to.value() == value);
    }{ /* both init */
        opt to(bad);
        opt from(value);
        to = static_cast<opt &&>(from);
        BOOST_REQUIRE(to.good());
        BOOST_CHECK(to.value() == value);
    }
}

BOOST_AUTO_TEST_CASE(non_trivial_value_assign_test)
{
    using opt = elib::optional<std::string>;
    
    std::string bad("bad");
    std::string s("hello");
    {
        opt o;
        o = s;
        BOOST_REQUIRE(o.good());
        BOOST_CHECK(o.value() == s);
    }{
        opt o(bad);
        o = s;
        BOOST_REQUIRE(o.good());
        BOOST_CHECK(o.value() == s);
    }
}

BOOST_AUTO_TEST_CASE(trivial_value_assign_test)
{
    using opt = elib::optional<int>;
    
    int bad = -1;
    int n = 42;
    {
        opt o;
        o = n;
        BOOST_REQUIRE(o.good());
        BOOST_CHECK(o.value() == n);
    }{
        opt o(bad);
        o = n;
        BOOST_REQUIRE(o.good());
        BOOST_CHECK(o.value() == n);
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

#if !defined(ELIB_CONFIG_NO_REF_QUALIFIERS)
BOOST_AUTO_TEST_CASE(trivial_deref_rvalue_test)
{
    using opt = elib::optional<int>;
    opt t(1);
    int x = *static_cast<opt &&>(t);
    BOOST_CHECK(x == 1);
}

BOOST_AUTO_TEST_CASE(trivial_value_rvalue_test)
{
    using opt = elib::optional<int>;
    opt t(1);
    int x = static_cast<opt &&>(t).value();
    BOOST_CHECK(x == 1);
}

BOOST_AUTO_TEST_CASE(trivial_value_rvalue_throw_test)
{
    using opt = elib::optional<int>;
    opt t;
    BOOST_CHECK_THROW(static_cast<opt &&>(t).value(), elib::bad_optional_access);
}
#endif

#if !defined(ELIB_CONFIG_NO_REF_QUALIFIERS)
BOOST_AUTO_TEST_CASE(non_trivial_value_or_test_rvalue)
{
    using opt = elib::optional<std::string>;
    std::string const value = "hello";
    std::string const other = "world";
    {
        opt o;
        auto ret = static_cast<opt &&>(o).value_or(other);
        BOOST_CHECK(ret == other);
    }{
        opt o(value);
        auto ret = static_cast<opt &&>(o).value_or(other);
        BOOST_CHECK(ret == value);
    }
}

BOOST_AUTO_TEST_CASE(trivial_value_or_test_rvalue)
{
    using opt = elib::optional<int>;
    int const value = 42;
    int const other = -1;
    {
        opt o;
        auto ret = static_cast<opt &&>(o).value_or(other);
        BOOST_CHECK(ret == other);
    }{
        opt o(value);
        auto ret = static_cast<opt &&>(o).value_or(other);
        BOOST_CHECK(ret == value);
    }
}
# endif


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