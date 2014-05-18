#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include <elib/any.hpp>
#include <elib/aux.hpp>
#include <memory>
#include <string>
#include <typeinfo>

using namespace elib;

template <int Dummy = 0>
struct basic_small_value
{
    basic_small_value() noexcept(false) 
    {}
    
    basic_small_value(basic_small_value const &) noexcept(false)
    {}
    
    basic_small_value(basic_small_value &&) noexcept
    {}
    
    basic_small_value & operator=(basic_small_value const &) noexcept(false)
    {
        return *this;
    }
    
    basic_small_value & operator=(basic_small_value &&) noexcept
    {
        return *this;
    }
};

using small_value = basic_small_value<>;
using small_value2 = basic_small_value<2>;

template <int Dummy = 0>
struct basic_large_value
{
    basic_large_value() = default;
    basic_large_value(basic_large_value const &) = default;
    basic_large_value(basic_large_value &&) = default;
    
    basic_large_value & operator=(basic_large_value const &) = default;
    basic_large_value & operator=(basic_large_value &&) = default;

private:
    char m_dummy[1024];
};

using large_value = basic_large_value<>;
using large_value2 = basic_large_value<2>;

BOOST_AUTO_TEST_SUITE(elib_any_test_suite)

BOOST_AUTO_TEST_CASE(default_ctor_test)
{
    static_assert(
        noexcept(noexcept(any()))
      , "any must be noexcept default constructible"
      );
    
    const any a;
    BOOST_CHECK(a.empty());
    BOOST_CHECK(a.type() == typeid(void));
}

BOOST_AUTO_TEST_CASE(small_value_ctor_test)
{
    static_assert(
        detail::store_locally<detail::any_storage_type<small_value>>::value
      , "small_value should be stored locally"
      );
    
    const any a(small_value{});
    BOOST_CHECK(not a.empty());
    BOOST_CHECK(a.type() == typeid(small_value));
}

BOOST_AUTO_TEST_CASE(large_value_ctor_test)
{
    static_assert(
        not detail::store_locally<detail::any_storage_type<large_value>>::value
      , "large_value should not be stored locally"
      );
    
    const any a(large_value{});
    BOOST_CHECK(not a.empty());
    BOOST_CHECK(a.type() == typeid(large_value));
}

BOOST_AUTO_TEST_CASE(empty_copy_ctor_test)
{
    const any a;
    const any cp(a);
    BOOST_CHECK(cp.empty());
    BOOST_CHECK(cp.type() == typeid(void));
}

BOOST_AUTO_TEST_CASE(small_value_copy_ctor_test)
{
    const any a(small_value{});
    const any cp(a);
    BOOST_CHECK(not cp.empty());
    BOOST_CHECK(cp.type() == typeid(small_value));
}

BOOST_AUTO_TEST_CASE(large_value_copy_ctor_test)
{
    const any a(large_value{});
    const any cp(a);
    BOOST_CHECK(not cp.empty());
    BOOST_CHECK(cp.type() == typeid(large_value));
}

BOOST_AUTO_TEST_CASE(empty_move_ctor_test)
{
    any a;
    const any cp(elib::move(a));
    BOOST_CHECK(cp.empty());
    BOOST_CHECK(cp.type() == typeid(void));
}

BOOST_AUTO_TEST_CASE(small_value_move_ctor_test)
{
    any a(small_value{});
    const any cp(elib::move(a));
    BOOST_CHECK(not cp.empty());
    BOOST_CHECK(cp.type() == typeid(small_value));
}

BOOST_AUTO_TEST_CASE(large_value_move_ctor_test)
{
    any a(large_value{});
    const any cp(elib::move(a));
    BOOST_CHECK(not cp.empty());
    BOOST_CHECK(cp.type() == typeid(large_value));
}

BOOST_AUTO_TEST_CASE(uses_allocator_ctor_1_test)
{
    const any a(std::allocator_arg, std::allocator<void>{});
    BOOST_CHECK(a.empty());
    BOOST_CHECK(a.type() == typeid(void));
}

BOOST_AUTO_TEST_CASE(uses_allocator_small_value_ctor_test)
{
    const any a(std::allocator_arg, std::allocator<void>{}, small_value{});
    BOOST_CHECK(not a.empty());
    BOOST_CHECK(a.type() == typeid(small_value));
}

BOOST_AUTO_TEST_CASE(uses_allocator_large_value_ctor_test)
{
    const any a(std::allocator_arg, std::allocator<void>{}, large_value{});
    BOOST_CHECK(not a.empty());
    BOOST_CHECK(a.type() == typeid(large_value));
}

BOOST_AUTO_TEST_CASE(copy_assignment_test)
{
    const any a(small_value{});
    any cp;
    cp = a;
    BOOST_CHECK(not cp.empty());
    BOOST_CHECK(cp.type() == typeid(small_value));
}

BOOST_AUTO_TEST_CASE(empty_move_assignment_test)
{
    any a;
    any cp(small_value{});
    cp = elib::move(a);
    BOOST_CHECK(cp.empty());
    BOOST_CHECK(cp.type() == typeid(void));
}

BOOST_AUTO_TEST_CASE(small_value_move_assignment_test)
{
    any a(small_value{});
    any cp;
    cp = elib::move(a);
    BOOST_CHECK(not cp.empty());
    BOOST_CHECK(cp.type() == typeid(small_value));
}

BOOST_AUTO_TEST_CASE(large_value_move_assignment_test)
{
    any a(large_value{});
    any cp;
    cp = elib::move(a);
    BOOST_CHECK(not cp.empty());
    BOOST_CHECK(cp.type() == typeid(large_value));
}

BOOST_AUTO_TEST_CASE(small_value_assignment_test)
{
    // copy
    {
        any a;
        const small_value s{};
        a = s;
        BOOST_CHECK(not a.empty());
        BOOST_CHECK(a.type() == typeid(small_value));
    }
    // move
    {
        any a;
        small_value s{};
        a = elib::move(s);
        BOOST_CHECK(not a.empty());
        BOOST_CHECK(a.type() == typeid(small_value));
    }
}

BOOST_AUTO_TEST_CASE(large_value_assignment_test)
{
    // copy
    {
        any a;
        const large_value s{};
        a = s;
        BOOST_CHECK(not a.empty());
        BOOST_CHECK(a.type() == typeid(large_value));
    }
    // move
    {
        any a;
        large_value s{};
        a = elib::move(s);
        BOOST_CHECK(not a.empty());
        BOOST_CHECK(a.type() == typeid(large_value));
    }
}

BOOST_AUTO_TEST_CASE(clear_test)
{
    static_assert(
        noexcept(noexcept(elib::declval<any>().clear()))
      , "clear must be noexcept"
      );
    
    // empty
    {
        any a;
        a.clear();
        BOOST_CHECK(a.empty());
        BOOST_CHECK(a.type() == typeid(void));
    }
    // small value
    {
        any a(small_value{});
        a.clear();
        BOOST_CHECK(a.empty());
        BOOST_CHECK(a.type() == typeid(void));
    }
    // large value
    {
        any a(large_value{});
        a.clear();
        BOOST_CHECK(a.empty());
        BOOST_CHECK(a.type() == typeid(void));
    }
}

BOOST_AUTO_TEST_CASE(swap_member_noexcept_test)
{
    static_assert(
        noexcept(noexcept(elib::declval<any &>().swap(elib::declval<any &>())))
      , "Swap member must be noexcept"
      );
    BOOST_CHECK(true);
}

BOOST_AUTO_TEST_CASE(empty_empty_swap_member_test)
{
    any a1;
    any a2;
    a1.swap(a2);
    BOOST_CHECK(a1.empty());
    BOOST_CHECK(a2.empty());
    BOOST_CHECK(a1.type() == typeid(void));
    BOOST_CHECK(a2.type() == typeid(void));
}

BOOST_AUTO_TEST_CASE(small_small_swap_member_test)
{
    any a1(small_value{});
    any a2(small_value2{});
    a1.swap(a2);
    BOOST_CHECK(not a1.empty());
    BOOST_CHECK(not a2.empty());
    BOOST_CHECK(a1.type() == typeid(small_value2));
    BOOST_CHECK(a2.type() == typeid(small_value));
}

BOOST_AUTO_TEST_CASE(small_empty_swap_member_test)
{
    any a1(small_value{});
    any a2;
    a1.swap(a2);
    BOOST_CHECK(a1.empty());
    BOOST_CHECK(not a2.empty());
    BOOST_CHECK(a1.type() == typeid(void));
    BOOST_CHECK(a2.type() == typeid(small_value));
}

BOOST_AUTO_TEST_CASE(small_large_swap_member_test)
{
    any a1(small_value{});
    any a2(large_value{});
    a1.swap(a2);
    BOOST_CHECK(not a1.empty());
    BOOST_CHECK(not a2.empty());
    BOOST_CHECK(a1.type() == typeid(large_value));
    BOOST_CHECK(a2.type() == typeid(small_value));
}

BOOST_AUTO_TEST_CASE(large_large_swap_member_test)
{
    any a1(large_value{});
    any a2(large_value2{});
    a1.swap(a2);
    BOOST_CHECK(not a1.empty());
    BOOST_CHECK(not a2.empty());
    BOOST_CHECK(a1.type() == typeid(large_value2));
    BOOST_CHECK(a2.type() == typeid(large_value));
}

BOOST_AUTO_TEST_CASE(large_empty_swap_member_test)
{
    any a1(large_value{});
    any a2;
    a1.swap(a2);
    BOOST_CHECK(a1.empty());
    BOOST_CHECK(not a2.empty());
    BOOST_CHECK(a1.type() == typeid(void));
    BOOST_CHECK(a2.type() == typeid(large_value));
}

BOOST_AUTO_TEST_CASE(large_small_swap_member_test)
{
    any a1(large_value{});
    any a2(small_value{});
    a1.swap(a2);
    BOOST_CHECK(not a1.empty());
    BOOST_CHECK(not a2.empty());
    BOOST_CHECK(a1.type() == typeid(small_value));
    BOOST_CHECK(a2.type() == typeid(large_value));
}

BOOST_AUTO_TEST_CASE(empty_and_bool_test)
{
    // empty
    {
        const any a;
        BOOST_CHECK(a.empty());
        BOOST_CHECK(not a);
        BOOST_CHECK(a.type() == typeid(void));
    }
    // non-empty
    {
        const any a(small_value{});
        BOOST_CHECK(not a.empty());
        BOOST_CHECK(bool(a));
        BOOST_CHECK(a.type() == typeid(small_value));
    }
}

/// This test is mostly for code coverage
BOOST_AUTO_TEST_CASE(swap_function_coverage_test)
{
    any a1(small_value{});
    any a2(large_value{});
    swap(a1, a2);
    BOOST_CHECK(a1.type() == typeid(large_value));
    BOOST_CHECK(a2.type() == typeid(small_value));
}

BOOST_AUTO_TEST_SUITE_END()