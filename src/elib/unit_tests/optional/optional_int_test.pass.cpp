// REQUIRES: ELIB_SOURCE, ELIB_BOOST_TEST
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE Main
#include <boost/test/unit_test.hpp>

#include <elib/optional.hpp>
using opt = elib::optional<int>;
using elib::nullopt;
using elib::in_place;

/// Test the reference version of optional
BOOST_AUTO_TEST_SUITE(elib_optional_int_test_suite)

BOOST_AUTO_TEST_CASE(default_ctor_test)
{
    {
        opt t;
        BOOST_CHECK(not t.good());
    }{
        const opt t;
        BOOST_CHECK(not t.good());
    }
}

BOOST_AUTO_TEST_CASE(nullopt_ctor_test)
{
    {
        opt t(nullopt);
        BOOST_CHECK(not t.good());
    }{
        const opt t(nullopt);
        BOOST_CHECK(not t.good());
    }
}

BOOST_AUTO_TEST_CASE(uninit_copy_ctor_test)
{
    opt const t;
    opt t2(t);
    BOOST_CHECK(not t2.good());
}

BOOST_AUTO_TEST_CASE(init_copy_ctor_test)
{
    int x = 1;
    opt const t(x);
    opt t2(t);
    BOOST_REQUIRE(t.good() && t2.good());
    BOOST_CHECK(t.value() == t2.value());
    BOOST_CHECK(t2.value() == x);
}

BOOST_AUTO_TEST_CASE(uninit_move_ctor_test)
{
    opt t;
    opt t2(static_cast<opt &&>(t));
    BOOST_CHECK(not t2.good());
}

BOOST_AUTO_TEST_CASE(init_move_ctor_test)
{
    int x = 1;
    opt t(x);
    opt t2(static_cast<opt &&>(t));
    BOOST_REQUIRE(t2.good());
    BOOST_CHECK(t2.value() == x);
}

BOOST_AUTO_TEST_CASE(value_copy_ctor_test)
{
    {
        int x = 1;
        opt t(x);
        BOOST_REQUIRE(t.good());
        BOOST_CHECK(t.value() == x);
    }{
        int x = 1;
        const opt t(x);
        BOOST_REQUIRE(t.good());
        BOOST_CHECK(t.value() == x);
    }
}

BOOST_AUTO_TEST_CASE(value_move_ctor_test)
{
    int const expect = 1;
    {
        opt t(1);
        BOOST_REQUIRE(t.good());
        BOOST_CHECK(t.value() == expect);
    }{
        const opt t(1);
        BOOST_REQUIRE(t.good());
        BOOST_CHECK(t.value() == expect);
    }
}


BOOST_AUTO_TEST_CASE(in_place_ctor_test)
{
    int x = 1;
    opt t(in_place, x);
    BOOST_REQUIRE(t.good());
    BOOST_CHECK(t.value() == x);
}

BOOST_AUTO_TEST_CASE(in_place_empty_ctor_test)
{
    opt t(in_place);
    BOOST_REQUIRE(t.good());
    BOOST_CHECK(t.value() == 0);
}

BOOST_AUTO_TEST_CASE(uninit_nullopt_assign_test)
{
    opt t;
    t = nullopt;
    BOOST_CHECK(not t.good());
}

BOOST_AUTO_TEST_CASE(init_nullopt_assign_test)
{
    int x = 1;
    opt t(x);
    t = nullopt;
    BOOST_CHECK(not t.good());
}

BOOST_AUTO_TEST_CASE(copy_assign_empty_to_empty_test)
{
    opt const t1;
    opt t2;
    t2 = t1;
    BOOST_CHECK(not t2.good());
}

BOOST_AUTO_TEST_CASE(copy_assign_empty_to_non_empty)
{
    opt const t1;
    opt t2(1);
    t2 = t1;
    BOOST_CHECK(not t2.good());
}

BOOST_AUTO_TEST_CASE(copy_assign_non_empty_to_empty_test)
{
    opt const t1(1);
    opt t2;
    t2 = t1;
    BOOST_REQUIRE(t1.good() && t2.good());
    BOOST_CHECK(t2.value() == 1);
}

BOOST_AUTO_TEST_CASE(copy_assign_non_empty_to_non_empty_test)
{
    opt const t1(1);
    opt t2(0);
    t2 = t1;
    BOOST_REQUIRE(t2.good() && t1.good());
    BOOST_CHECK(t2.value() == 1);
}


BOOST_AUTO_TEST_CASE(move_assign_empty_to_empty_test)
{
    opt t1;
    opt t2;
    t2 = static_cast<opt &&>(t1);
    BOOST_CHECK(not t2.good());
}

BOOST_AUTO_TEST_CASE(move_assign_empty_to_non_empty_test)
{
    opt t1;
    opt t2(1);
    t2 = static_cast<opt &&>(t1);
    BOOST_REQUIRE(not t2.good());
}

BOOST_AUTO_TEST_CASE(move_assign_non_empty_to_empty_test)
{
    opt t1(1);
    opt t2;
    t2 = static_cast<opt &&>(t1);
    BOOST_REQUIRE(t2.good());
    BOOST_CHECK(t2.value() == 1);
}

BOOST_AUTO_TEST_CASE(move_assign_non_empty_to_non_empty_test)
{
    opt t1(1);
    opt t2(0);
    t2 = static_cast<opt &&>(t1);
    BOOST_REQUIRE(t2.good());
    BOOST_CHECK(t2.value() == 1);
}

BOOST_AUTO_TEST_CASE(assign_value_to_empty_test)
{
    opt t;
    t = 1;
    BOOST_REQUIRE(t.good());
    BOOST_CHECK(t.value() == 1);
}

BOOST_AUTO_TEST_CASE(assign_value_to_non_empty_test)
{
    opt t(0);
    t = 1;
    BOOST_REQUIRE(t.good());
    BOOST_CHECK(t.value() == 1);
}


BOOST_AUTO_TEST_CASE(emplace_test)
{
    int x = 1;
    opt t;
    t.emplace(x);
    BOOST_REQUIRE(t.good());
    BOOST_CHECK(t.value() == x);
}

BOOST_AUTO_TEST_CASE(empty_emplace_test)
{
    opt t(1);
    t.emplace();
    BOOST_REQUIRE(t.good());
    BOOST_CHECK(t.value() == 0);
}

BOOST_AUTO_TEST_CASE(uninit_swap_test)
{
    opt t1;
    opt t2;
    t1.swap(t2);
    BOOST_CHECK(not t1.good() && not t2.good());
}

BOOST_AUTO_TEST_CASE(one_init_swap_test)
{
    int x = 1;
    opt t1(x);
    opt t2;
    t1.swap(t2);
    BOOST_REQUIRE(not t1.good() && t2.good());
    BOOST_CHECK(t2.value() == x);
}

BOOST_AUTO_TEST_CASE(both_init_swap_test)
{
    int x = 1;
    int y = 1;
    opt t1(x);
    opt t2(y);
    t1.swap(t2);
    BOOST_REQUIRE(t1.good() && t2.good());
    BOOST_CHECK(t1.value() == y);
    BOOST_CHECK(t2.value() == x);
}

BOOST_AUTO_TEST_CASE(const_arrow_operator_test)
{
    int x = 1;
    opt const t(x);
    BOOST_REQUIRE(t.operator->());
    BOOST_CHECK(*(t.operator->()) == x);
}

BOOST_AUTO_TEST_CASE(non_const_arrow_operator_test)
{
    int x = 1;
    opt t(x);
    BOOST_REQUIRE(t.operator->());
    BOOST_CHECK(*(t.operator->()) == x);
    *(t.operator->()) = 2;
    BOOST_CHECK(t.value() == 2);
}

BOOST_AUTO_TEST_CASE(const_deref_operator_test)
{
    int x = 1;
    opt const t(x);
    BOOST_CHECK(t.operator*() == x);
}

BOOST_AUTO_TEST_CASE(non_const_lvalue_deref_operator_test)
{
    int x = 1;
    opt t(x);
    BOOST_CHECK(t.operator*() == x);
    t.operator*() = 2;
    BOOST_CHECK(t.operator*() == 2);
}

BOOST_AUTO_TEST_CASE(rvalue_deref_operator_test)
{
    int x = 1;
    opt t(x);
    BOOST_CHECK(static_cast<opt &&>(t).operator*() == x);
}


BOOST_AUTO_TEST_CASE(empty_operator_bool_test)
{
    opt const t;
    BOOST_CHECK(not bool(t));
}

BOOST_AUTO_TEST_CASE(non_empty_operator_bool_test)
{
    int x = 1;
    opt const t(x);
    BOOST_CHECK(bool(t));
}

BOOST_AUTO_TEST_CASE(empty_good_test)
{
    opt const t;
    BOOST_CHECK(not t.good());
}

BOOST_AUTO_TEST_CASE(non_empty_good_test)
{
    int x = 1;
    opt const t(x);
    BOOST_CHECK(t.good());
}

BOOST_AUTO_TEST_CASE(const_value_test)
{
    opt const t(1);
    BOOST_CHECK(t.value() == 1);
}

BOOST_AUTO_TEST_CASE(empty_const_value_test)
{
    opt const t;
    BOOST_CHECK_THROW(t.value(), elib::bad_optional_access);
}

BOOST_AUTO_TEST_CASE(non_const_value_test)
{
    opt t(1);
    BOOST_CHECK(t.value() == 1);
    t.value() = 2;
    BOOST_CHECK(t.value() == 2);
}

BOOST_AUTO_TEST_CASE(empty_non_const_value_test)
{
    opt t;
    BOOST_CHECK_THROW(t.value(), elib::bad_optional_access);
}

BOOST_AUTO_TEST_CASE(rvalue_value_test)
{
    opt t(1);
    BOOST_CHECK(static_cast<opt &&>(t).value() == 1);
}

BOOST_AUTO_TEST_CASE(empty_rvalue_value_test)
{
    opt t;
    BOOST_CHECK_THROW(static_cast<opt &&>(t).value(), elib::bad_optional_access);
}

BOOST_AUTO_TEST_CASE(const_value_or_test)
{
    opt const t(1);
    BOOST_CHECK(t.value_or(2) == 1);
}

BOOST_AUTO_TEST_CASE(empty_const_value_or_test)
{
    opt const t;
    BOOST_CHECK(t.value_or(2) == 2);
}

BOOST_AUTO_TEST_CASE(rvalue_value_or_test)
{
    opt t(1);
    BOOST_CHECK(static_cast<opt &&>(t).value_or(2) == 1);
}

BOOST_AUTO_TEST_CASE(empty_rvalue_value_or_test)
{
    opt t;
    BOOST_CHECK(static_cast<opt &&>(t).value_or(2) == 2);
}

BOOST_AUTO_TEST_SUITE_END()