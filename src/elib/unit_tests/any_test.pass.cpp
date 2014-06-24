// REQUIRES: ELIB_CORE
#include <elib/aux.hpp>
#include <memory>
#include <string>
#include <typeinfo>
#include <elib/any.hpp>
#include "rapid-cxx-test.hpp"

using namespace elib;

template <int Dummy = 0>
struct basic_small_value
{
    basic_small_value() noexcept(false)
      : value(0)
    {}
    
    explicit basic_small_value(int val) noexcept(false)
      : value(val)
    {}
    
    basic_small_value(basic_small_value const & other) noexcept(false)
      : value(other.value)
    {}
    
    basic_small_value(basic_small_value && other) noexcept
      : value(other.value)
    {}
    
    basic_small_value & operator=(basic_small_value const & other) noexcept(false)
    {
        value = other.value;
        return *this;
    }
    
    basic_small_value & operator=(basic_small_value && other) noexcept
    {
        value = other.value;
        return *this;
    }
    
    int value;
};


using small_value = basic_small_value<>;
using small_value2 = basic_small_value<2>;

template <int Dummy = 0>
struct basic_large_value
{
    basic_large_value() noexcept
      : value(0)
    {}
    
    explicit basic_large_value(int val) noexcept
      : value(val)
    {}
    
    basic_large_value(basic_large_value const & other)
      : value(other.value)
    {}
    
    basic_large_value(basic_large_value && other) noexcept
      : value(other.value)
    {}
    
    basic_large_value & operator=(basic_large_value const & other)
    {
        value = other.value;
        return *this;
    }
    
    basic_large_value & operator=(basic_large_value && other) noexcept
    {
        value = other.value;
        return *this;
    }

    int value;
private:
    // sizeof(value) + sizeof(any_buffer_t) is bigger than a small object
    detail::any_buffer_t m_dummy;
};

using large_value = basic_large_value<>;
using large_value2 = basic_large_value<2>;

TEST_SUITE(elib_any_test_suite)

/// Mostly for code coverage
TEST_CASE(bad_any_cast_test)
{
    const elib::bad_any_cast x;
    TEST_CHECK(x.what());
}

TEST_CASE(default_ctor_test)
{
    static_assert(
        noexcept(any())
      , "any must be noexcept default constructible"
      );
    
    const any a;
    TEST_CHECK(a.empty());
    TEST_CHECK(a.type() == typeid(void));
}

TEST_CASE(small_value_ctor_test)
{
    static_assert(
        detail::store_locally<detail::any_storage_type<small_value>>::value
      , "small_value should be stored locally"
      );
    
    const any a(small_value{});
    TEST_CHECK(not a.empty());
    TEST_CHECK(a.type() == typeid(small_value));
}

TEST_CASE(large_value_ctor_test)
{
    static_assert(
        not detail::store_locally<detail::any_storage_type<large_value>>::value
      , "large_value should not be stored locally"
      );
    
    const any a(large_value{});
    TEST_CHECK(not a.empty());
    TEST_CHECK(a.type() == typeid(large_value));
}

TEST_CASE(empty_copy_ctor_test)
{
    const any a;
    const any cp(a);
    TEST_CHECK(cp.empty());
    TEST_CHECK(cp.type() == typeid(void));
}

TEST_CASE(small_value_copy_ctor_test)
{
    const any a(small_value{});
    const any cp(a);
    TEST_CHECK(not cp.empty());
    TEST_CHECK(cp.type() == typeid(small_value));
}

TEST_CASE(large_value_copy_ctor_test)
{
    const any a(large_value{});
    const any cp(a);
    TEST_CHECK(not cp.empty());
    TEST_CHECK(cp.type() == typeid(large_value));
}

TEST_CASE(empty_move_ctor_test)
{
    any a;
    const any cp(elib::move(a));
    TEST_CHECK(cp.empty());
    TEST_CHECK(cp.type() == typeid(void));
}

TEST_CASE(small_value_move_ctor_test)
{
    any a(small_value{});
    const any cp(elib::move(a));
    TEST_CHECK(not cp.empty());
    TEST_CHECK(cp.type() == typeid(small_value));
}

TEST_CASE(large_value_move_ctor_test)
{
    any a(large_value{});
    const any cp(elib::move(a));
    TEST_CHECK(not cp.empty());
    TEST_CHECK(cp.type() == typeid(large_value));
}

TEST_CASE(uses_allocator_ctor_1_test)
{
    const any a(std::allocator_arg, std::allocator<void>{});
    TEST_CHECK(a.empty());
    TEST_CHECK(a.type() == typeid(void));
}

TEST_CASE(uses_allocator_small_value_ctor_test)
{
    const any a(std::allocator_arg, std::allocator<void>{}, small_value{});
    TEST_CHECK(not a.empty());
    TEST_CHECK(a.type() == typeid(small_value));
}

TEST_CASE(uses_allocator_large_value_ctor_test)
{
    const any a(std::allocator_arg, std::allocator<void>{}, large_value{});
    TEST_CHECK(not a.empty());
    TEST_CHECK(a.type() == typeid(large_value));
}

TEST_CASE(copy_assignment_test)
{
    const any a(small_value{});
    any cp;
    cp = a;
    TEST_CHECK(not cp.empty());
    TEST_CHECK(cp.type() == typeid(small_value));
}

TEST_CASE(empty_move_assignment_test)
{
    any a;
    any cp(small_value{});
    cp = elib::move(a);
    TEST_CHECK(cp.empty());
    TEST_CHECK(cp.type() == typeid(void));
}

TEST_CASE(small_value_move_assignment_test)
{
    any a(small_value{});
    any cp;
    cp = elib::move(a);
    TEST_CHECK(not cp.empty());
    TEST_CHECK(cp.type() == typeid(small_value));
}

TEST_CASE(large_value_move_assignment_test)
{
    any a(large_value{});
    any cp;
    cp = elib::move(a);
    TEST_CHECK(not cp.empty());
    TEST_CHECK(cp.type() == typeid(large_value));
}

TEST_CASE(small_value_assignment_test)
{
    // copy
    {
        any a;
        const small_value s{};
        a = s;
        TEST_CHECK(not a.empty());
        TEST_CHECK(a.type() == typeid(small_value));
    }
    // move
    {
        any a;
        small_value s{};
        a = elib::move(s);
        TEST_CHECK(not a.empty());
        TEST_CHECK(a.type() == typeid(small_value));
    }
}

TEST_CASE(large_value_assignment_test)
{
    // copy
    {
        any a;
        const large_value s{};
        a = s;
        TEST_CHECK(not a.empty());
        TEST_CHECK(a.type() == typeid(large_value));
    }
    // move
    {
        any a;
        large_value s{};
        a = elib::move(s);
        TEST_CHECK(not a.empty());
        TEST_CHECK(a.type() == typeid(large_value));
    }
}

TEST_CASE(clear_test)
{
    static_assert(
        noexcept(elib::declval<any>().clear())
      , "clear must be noexcept"
      );
    
    // empty
    {
        any a;
        a.clear();
        TEST_CHECK(a.empty());
        TEST_CHECK(a.type() == typeid(void));
    }
    // small value
    {
        any a(small_value{});
        a.clear();
        TEST_CHECK(a.empty());
        TEST_CHECK(a.type() == typeid(void));
    }
    // large value
    {
        any a(large_value{});
        a.clear();
        TEST_CHECK(a.empty());
        TEST_CHECK(a.type() == typeid(void));
    }
}

TEST_CASE(swap_member_noexcept_test)
{
    static_assert(
        noexcept(elib::declval<any &>().swap(elib::declval<any &>()))
      , "Swap member must be noexcept"
      );
    TEST_CHECK(true);
}

TEST_CASE(empty_empty_swap_member_test)
{
    any a1;
    any a2;
    a1.swap(a2);
    TEST_CHECK(a1.empty());
    TEST_CHECK(a2.empty());
    TEST_CHECK(a1.type() == typeid(void));
    TEST_CHECK(a2.type() == typeid(void));
}

TEST_CASE(empty_small_swap_member_test)
{
    any a1;
    any a2(small_value{});
    a1.swap(a2);
    TEST_CHECK(not a1.empty());
    TEST_CHECK(a2.empty());
    TEST_CHECK(a1.type() == typeid(small_value));
    TEST_CHECK(a2.type() == typeid(void));
}

TEST_CASE(empty_large_swap_member_test)
{
    any a1;
    any a2(large_value{});
    a1.swap(a2);
    TEST_CHECK(not a1.empty());
    TEST_CHECK(a2.empty());
    TEST_CHECK(a1.type() == typeid(large_value));
    TEST_CHECK(a2.type() == typeid(void));
}

TEST_CASE(small_small_swap_member_test)
{
    any a1(small_value{});
    any a2(small_value2{});
    a1.swap(a2);
    TEST_CHECK(not a1.empty());
    TEST_CHECK(not a2.empty());
    TEST_CHECK(a1.type() == typeid(small_value2));
    TEST_CHECK(a2.type() == typeid(small_value));
}

TEST_CASE(small_empty_swap_member_test)
{
    any a1(small_value{});
    any a2;
    a1.swap(a2);
    TEST_CHECK(a1.empty());
    TEST_CHECK(not a2.empty());
    TEST_CHECK(a1.type() == typeid(void));
    TEST_CHECK(a2.type() == typeid(small_value));
}

TEST_CASE(small_large_swap_member_test)
{
    any a1(small_value{});
    any a2(large_value{});
    a1.swap(a2);
    TEST_CHECK(not a1.empty());
    TEST_CHECK(not a2.empty());
    TEST_CHECK(a1.type() == typeid(large_value));
    TEST_CHECK(a2.type() == typeid(small_value));
}

TEST_CASE(large_large_swap_member_test)
{
    any a1(large_value{});
    any a2(large_value2{});
    a1.swap(a2);
    TEST_CHECK(not a1.empty());
    TEST_CHECK(not a2.empty());
    TEST_CHECK(a1.type() == typeid(large_value2));
    TEST_CHECK(a2.type() == typeid(large_value));
}

TEST_CASE(large_empty_swap_member_test)
{
    any a1(large_value{});
    any a2;
    a1.swap(a2);
    TEST_CHECK(a1.empty());
    TEST_CHECK(not a2.empty());
    TEST_CHECK(a1.type() == typeid(void));
    TEST_CHECK(a2.type() == typeid(large_value));
}

TEST_CASE(large_small_swap_member_test)
{
    any a1(large_value{});
    any a2(small_value{});
    a1.swap(a2);
    TEST_CHECK(not a1.empty());
    TEST_CHECK(not a2.empty());
    TEST_CHECK(a1.type() == typeid(small_value));
    TEST_CHECK(a2.type() == typeid(large_value));
}

TEST_CASE(empty_and_bool_test)
{
    // empty
    {
        const any a;
        TEST_CHECK(a.empty());
        TEST_CHECK(not a);
        TEST_CHECK(a.type() == typeid(void));
    }
    // non-empty
    {
        const any a(small_value{});
        TEST_CHECK(not a.empty());
        TEST_CHECK(bool(a));
        TEST_CHECK(a.type() == typeid(small_value));
    }
}

/// This test is mostly for code coverage
TEST_CASE(swap_function_coverage_test)
{
    any a1(small_value{});
    any a2(large_value{});
    swap(a1, a2);
    TEST_CHECK(a1.type() == typeid(large_value));
    TEST_CHECK(a2.type() == typeid(small_value));
}

TEST_CASE(null_nothrow_const_any_cast_test)
{
    any const* any_ptr = nullptr;
    TEST_CHECK(elib::any_cast<small_value>(any_ptr) == nullptr);
}

TEST_CASE(wrong_type_nothrow_const_any_cast_test)
{
    // empty
    {
        const any a;
        small_value const* vptr = elib::any_cast<small_value const>(&a);
        TEST_CHECK(not vptr);
    }
    // non-empty
    {
        const any a(small_value{0});
        large_value const* vptr = elib::any_cast<large_value const>(&a);
        TEST_CHECK(not vptr);
    }
}

TEST_CASE(nothrow_const_any_cast_value_test)
{
    // small
    {
        const any a(small_value{1});
        small_value const *vptr = elib::any_cast<small_value const>(&a);
        TEST_REQUIRE(vptr);
        TEST_CHECK(vptr->value == 1);
    }
    // large
    {
        const any a(large_value{1});
        large_value const *vptr = elib::any_cast<large_value const>(&a);
        TEST_REQUIRE(vptr);
        TEST_CHECK(vptr->value == 1);
    }
}

TEST_CASE(null_nothrow_any_cast_test)
{
    any * any_ptr = nullptr;
    TEST_CHECK(elib::any_cast<small_value>(any_ptr) == nullptr);
}

TEST_CASE(wrong_type_nothrow_any_cast_test)
{
    // empty
    {
        any a;
        small_value* vptr = elib::any_cast<small_value>(&a);
        TEST_CHECK(not vptr);
    }
    // non-empty
    {
        any a(small_value{0});
        large_value* vptr = elib::any_cast<large_value>(&a);
        TEST_CHECK(not vptr);
    }
}

TEST_CASE(nothrow_any_cast_value_test)
{
    // small
    {
        any a(small_value{1});
        small_value *vptr = elib::any_cast<small_value>(&a);
        TEST_REQUIRE(vptr);
        TEST_CHECK(vptr->value == 1);
        vptr->value = 2;
        vptr = elib::any_cast<small_value>(&a);
        TEST_REQUIRE(vptr);
        TEST_CHECK(vptr->value == 2);
    }
    // large
    {
        any a(large_value{1});
        large_value *vptr = elib::any_cast<large_value>(&a);
        TEST_REQUIRE(vptr);
        TEST_CHECK(vptr->value == 1);
        vptr->value = 2;
        vptr = elib::any_cast<large_value>(&a);
        TEST_REQUIRE(vptr);
        TEST_CHECK(vptr->value == 2);
    }
}

TEST_CASE(empty_throwing_any_cast_test)
{
    // const to-value test
    {
        const any a;
        TEST_CHECK_THROW(elib::bad_any_cast, elib::any_cast<small_value>(a));
    }
    // const to-ref test
    {
        const any a;
        TEST_CHECK_THROW(elib::bad_any_cast, elib::any_cast<small_value const &>(a));
    }
    // to-value test
    {
        any a;
        TEST_CHECK_THROW(elib::bad_any_cast, elib::any_cast<small_value>(a));
    }
    // to-ref test
    {
        any a;
        TEST_CHECK_THROW(elib::bad_any_cast, elib::any_cast<small_value &>(a));
    }
}

TEST_CASE(wrong_type_throwing_any_cast_test)
{
    // const to-value test
    {
        const any a(large_value{});
        TEST_CHECK_THROW(elib::bad_any_cast, elib::any_cast<small_value>(a));
    }
    // const to-ref test
    {
        const any a(large_value{});
        TEST_CHECK_THROW(elib::bad_any_cast, elib::any_cast<small_value const &>(a));
    }
    // to-value test
    {
        any a(large_value{});
        TEST_CHECK_THROW(elib::bad_any_cast, elib::any_cast<small_value>(a));
    }
    // to-ref test
    {
        any a(large_value{});
        TEST_CHECK_THROW(elib::bad_any_cast, elib::any_cast<small_value &>(a));
    }
}

TEST_CASE(small_value_throwing_any_cast_test)
{
    // const to-value test
    {
        const any a(small_value{1});
        small_value cp = elib::any_cast<small_value>(a);
        TEST_CHECK(cp.value == 1);
        
        static_assert(
            not aux::is_reference<decltype(elib::any_cast<small_value>(a))>::value
          , "Return type should not be reference"
          );
    }
    // const to-ref test
    {
        const any a(small_value{1});
        small_value const & ref = elib::any_cast<small_value const &>(a);
        TEST_CHECK(ref.value == 1);
        
        static_assert(
            aux::is_reference<decltype(elib::any_cast<small_value const &>(a))>::value
          , "Return type should be reference"
          );
    }
    // to-value test
    {
        any a(small_value{1});
        small_value cp = elib::any_cast<small_value>(a);
        TEST_CHECK(cp.value == 1);
        
        static_assert(
            not aux::is_reference<decltype(elib::any_cast<small_value>(a))>::value
          , "Return type should not be reference"
          );
    }
    // to-ref test
    {
        any a(small_value{1});
        small_value & ref = elib::any_cast<small_value &>(a);
        TEST_CHECK(ref.value == 1);
        ref.value = 2;
        small_value & ref2 = elib::any_cast<small_value &>(a);
        TEST_CHECK(ref2.value == 2);
        ref2.value = 3;
        TEST_CHECK(ref.value == 3);
        static_assert(
            aux::is_reference<decltype(elib::any_cast<small_value &>(a))>::value
          , "Return type should be reference"
          );
    }
}

TEST_CASE(large_value_throwing_any_cast_test)
{
    // const to-value test
    {
        const any a(large_value{1});
        large_value cp = elib::any_cast<large_value>(a);
        TEST_CHECK(cp.value == 1);
        
        static_assert(
            not aux::is_reference<decltype(elib::any_cast<large_value>(a))>::value
          , "Return type should not be reference"
          );
    }
    // const to-ref test
    {
        const any a(large_value{1});
        large_value const & ref = elib::any_cast<large_value const &>(a);
        TEST_CHECK(ref.value == 1);
        
        static_assert(
            aux::is_reference<decltype(elib::any_cast<large_value const &>(a))>::value
          , "Return type should be reference"
          );
    }
    // to-value test
    {
        any a(large_value{1});
        large_value cp = elib::any_cast<large_value>(a);
        TEST_CHECK(cp.value == 1);
        
        static_assert(
            not aux::is_reference<decltype(elib::any_cast<large_value>(a))>::value
          , "Return type should not be reference"
          );
    }
    // to-ref test
    {
        any a(large_value{1});
        large_value & ref = elib::any_cast<large_value &>(a);
        TEST_CHECK(ref.value == 1);
        ref.value = 2;
        large_value & ref2 = elib::any_cast<large_value &>(a);
        TEST_CHECK(ref2.value == 2);
        ref2.value = 3;
        TEST_CHECK(ref.value == 3);
        static_assert(
            aux::is_reference<decltype(elib::any_cast<large_value &>(a))>::value
          , "Return type should be reference"
          );
    }
}

/// Rvalue version is the same as all the lvalue versions
/// This test is for coverage only
TEST_CASE(throwing_rvalue_any_cast_test)
{
    any a(small_value{});
    TEST_CHECK_NO_THROW(elib::any_cast<small_value>(elib::move(a)));
}

TEST_SUITE_END()