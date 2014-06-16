// REQUIRES: ELIB_SOURCE
#include <elib/optional.hpp>
#include "rapid-cxx-test.hpp"

using opt = elib::optional<int>;
using elib::nullopt;
using elib::in_place;

/// Test the reference version of optional
TEST_SUITE(elib_optional_int_test_suite)

TEST_CASE(default_ctor_test)
{
    {
        opt t;
        TEST_CHECK(not t.good());
    }{
        const opt t;
        TEST_CHECK(not t.good());
    }
}

TEST_CASE(nullopt_ctor_test)
{
    {
        opt t(nullopt);
        TEST_CHECK(not t.good());
    }{
        const opt t(nullopt);
        TEST_CHECK(not t.good());
    }
}

TEST_CASE(uninit_copy_ctor_test)
{
    opt const t;
    opt t2(t);
    TEST_CHECK(not t2.good());
}

TEST_CASE(init_copy_ctor_test)
{
    int x = 1;
    opt const t(x);
    opt t2(t);
    TEST_REQUIRE(t.good() && t2.good());
    TEST_CHECK(t.value() == t2.value());
    TEST_CHECK(t2.value() == x);
}

TEST_CASE(uninit_move_ctor_test)
{
    opt t;
    opt t2(static_cast<opt &&>(t));
    TEST_CHECK(not t2.good());
}

TEST_CASE(init_move_ctor_test)
{
    int x = 1;
    opt t(x);
    opt t2(static_cast<opt &&>(t));
    TEST_REQUIRE(t2.good());
    TEST_CHECK(t2.value() == x);
}

TEST_CASE(value_copy_ctor_test)
{
    {
        int x = 1;
        opt t(x);
        TEST_REQUIRE(t.good());
        TEST_CHECK(t.value() == x);
    }{
        int x = 1;
        const opt t(x);
        TEST_REQUIRE(t.good());
        TEST_CHECK(t.value() == x);
    }
}

TEST_CASE(value_move_ctor_test)
{
    int const expect = 1;
    {
        opt t(1);
        TEST_REQUIRE(t.good());
        TEST_CHECK(t.value() == expect);
    }{
        const opt t(1);
        TEST_REQUIRE(t.good());
        TEST_CHECK(t.value() == expect);
    }
}


TEST_CASE(in_place_ctor_test)
{
    int x = 1;
    opt t(in_place, x);
    TEST_REQUIRE(t.good());
    TEST_CHECK(t.value() == x);
}

TEST_CASE(in_place_empty_ctor_test)
{
    opt t(in_place);
    TEST_REQUIRE(t.good());
    TEST_CHECK(t.value() == 0);
}

TEST_CASE(uninit_nullopt_assign_test)
{
    opt t;
    t = nullopt;
    TEST_CHECK(not t.good());
}

TEST_CASE(init_nullopt_assign_test)
{
    int x = 1;
    opt t(x);
    t = nullopt;
    TEST_CHECK(not t.good());
}

TEST_CASE(copy_assign_empty_to_empty_test)
{
    opt const t1;
    opt t2;
    t2 = t1;
    TEST_CHECK(not t2.good());
}

TEST_CASE(copy_assign_empty_to_non_empty)
{
    opt const t1;
    opt t2(1);
    t2 = t1;
    TEST_CHECK(not t2.good());
}

TEST_CASE(copy_assign_non_empty_to_empty_test)
{
    opt const t1(1);
    opt t2;
    t2 = t1;
    TEST_REQUIRE(t1.good() && t2.good());
    TEST_CHECK(t2.value() == 1);
}

TEST_CASE(copy_assign_non_empty_to_non_empty_test)
{
    opt const t1(1);
    opt t2(0);
    t2 = t1;
    TEST_REQUIRE(t2.good() && t1.good());
    TEST_CHECK(t2.value() == 1);
}


TEST_CASE(move_assign_empty_to_empty_test)
{
    opt t1;
    opt t2;
    t2 = static_cast<opt &&>(t1);
    TEST_CHECK(not t2.good());
}

TEST_CASE(move_assign_empty_to_non_empty_test)
{
    opt t1;
    opt t2(1);
    t2 = static_cast<opt &&>(t1);
    TEST_REQUIRE(not t2.good());
}

TEST_CASE(move_assign_non_empty_to_empty_test)
{
    opt t1(1);
    opt t2;
    t2 = static_cast<opt &&>(t1);
    TEST_REQUIRE(t2.good());
    TEST_CHECK(t2.value() == 1);
}

TEST_CASE(move_assign_non_empty_to_non_empty_test)
{
    opt t1(1);
    opt t2(0);
    t2 = static_cast<opt &&>(t1);
    TEST_REQUIRE(t2.good());
    TEST_CHECK(t2.value() == 1);
}

TEST_CASE(assign_value_to_empty_test)
{
    opt t;
    t = 1;
    TEST_REQUIRE(t.good());
    TEST_CHECK(t.value() == 1);
}

TEST_CASE(assign_value_to_non_empty_test)
{
    opt t(0);
    t = 1;
    TEST_REQUIRE(t.good());
    TEST_CHECK(t.value() == 1);
}


TEST_CASE(emplace_test)
{
    int x = 1;
    opt t;
    t.emplace(x);
    TEST_REQUIRE(t.good());
    TEST_CHECK(t.value() == x);
}

TEST_CASE(empty_emplace_test)
{
    opt t(1);
    t.emplace();
    TEST_REQUIRE(t.good());
    TEST_CHECK(t.value() == 0);
}

TEST_CASE(uninit_swap_test)
{
    opt t1;
    opt t2;
    t1.swap(t2);
    TEST_CHECK(not t1.good() && not t2.good());
}

TEST_CASE(one_init_swap_test)
{
    int x = 1;
    opt t1(x);
    opt t2;
    t1.swap(t2);
    TEST_REQUIRE(not t1.good() && t2.good());
    TEST_CHECK(t2.value() == x);
}

TEST_CASE(both_init_swap_test)
{
    int x = 1;
    int y = 1;
    opt t1(x);
    opt t2(y);
    t1.swap(t2);
    TEST_REQUIRE(t1.good() && t2.good());
    TEST_CHECK(t1.value() == y);
    TEST_CHECK(t2.value() == x);
}

TEST_CASE(const_arrow_operator_test)
{
    int x = 1;
    opt const t(x);
    TEST_REQUIRE(t.operator->());
    TEST_CHECK(*(t.operator->()) == x);
}

TEST_CASE(non_const_arrow_operator_test)
{
    int x = 1;
    opt t(x);
    TEST_REQUIRE(t.operator->());
    TEST_CHECK(*(t.operator->()) == x);
    *(t.operator->()) = 2;
    TEST_CHECK(t.value() == 2);
}

TEST_CASE(const_deref_operator_test)
{
    int x = 1;
    opt const t(x);
    TEST_CHECK(t.operator*() == x);
}

TEST_CASE(non_const_lvalue_deref_operator_test)
{
    int x = 1;
    opt t(x);
    TEST_CHECK(t.operator*() == x);
    t.operator*() = 2;
    TEST_CHECK(t.operator*() == 2);
}

TEST_CASE(rvalue_deref_operator_test)
{
    int x = 1;
    opt t(x);
    TEST_CHECK(static_cast<opt &&>(t).operator*() == x);
}


TEST_CASE(empty_operator_bool_test)
{
    opt const t;
    TEST_CHECK(not bool(t));
}

TEST_CASE(non_empty_operator_bool_test)
{
    int x = 1;
    opt const t(x);
    TEST_CHECK(bool(t));
}

TEST_CASE(empty_good_test)
{
    opt const t;
    TEST_CHECK(not t.good());
}

TEST_CASE(non_empty_good_test)
{
    int x = 1;
    opt const t(x);
    TEST_CHECK(t.good());
}

TEST_CASE(const_value_test)
{
    opt const t(1);
    TEST_CHECK(t.value() == 1);
}

TEST_CASE(empty_const_value_test)
{
    opt const t;
    TEST_CHECK_THROW(elib::bad_optional_access, t.value());
}

TEST_CASE(non_const_value_test)
{
    opt t(1);
    TEST_CHECK(t.value() == 1);
    t.value() = 2;
    TEST_CHECK(t.value() == 2);
}

TEST_CASE(empty_non_const_value_test)
{
    opt t;
    TEST_CHECK_THROW(elib::bad_optional_access, t.value());
}

TEST_CASE(rvalue_value_test)
{
    opt t(1);
    TEST_CHECK(static_cast<opt &&>(t).value() == 1);
}

TEST_CASE(empty_rvalue_value_test)
{
    opt t;
    TEST_CHECK_THROW(elib::bad_optional_access, static_cast<opt &&>(t).value());
}

TEST_CASE(const_value_or_test)
{
    opt const t(1);
    TEST_CHECK(t.value_or(2) == 1);
}

TEST_CASE(empty_const_value_or_test)
{
    opt const t;
    TEST_CHECK(t.value_or(2) == 2);
}

TEST_CASE(rvalue_value_or_test)
{
    opt t(1);
    TEST_CHECK(static_cast<opt &&>(t).value_or(2) == 1);
}

TEST_CASE(empty_rvalue_value_or_test)
{
    opt t;
    TEST_CHECK(static_cast<opt &&>(t).value_or(2) == 2);
}

TEST_SUITE_END()