// REQUIRES: ELIB_CORE
#include <elib/optional.hpp>
#include <string>
#include "rapid-cxx-test.hpp"

using opt = elib::optional<std::string>;
using elib::nullopt;
using elib::in_place;

TEST_SUITE(elib_optional_optional_string_test_suite)

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
    std::string const x = "hello";
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
    std::string const x = "hello";
    opt t(x);
    opt t2(static_cast<opt &&>(t));
    TEST_REQUIRE(t2.good());
    TEST_CHECK(t2.value() == x);
}


TEST_CASE(value_copy_ctor_test)
{
    {
        std::string const x = "hello";
        opt t(x);
        TEST_REQUIRE(t.good());
        TEST_CHECK(t.value() == x);
    }{
        std::string const x = "hello";
        const opt t(x);
        TEST_REQUIRE(t.good());
        TEST_CHECK(t.value() == x);
    }
}

TEST_CASE(value_move_ctor_test)
{
    std::string const expect = "hello";
    {
        opt t(std::string("hello"));
        TEST_REQUIRE(t.good());
        TEST_CHECK(t.value() == expect);
    }{
        const opt t(std::string("hello"));
        TEST_REQUIRE(t.good());
        TEST_CHECK(t.value() == expect);
    }
}

TEST_CASE(in_place_ctor_test)
{
    std::string const expect = "hello";
    opt t(in_place, "hello");
    TEST_REQUIRE(t.good());
    TEST_CHECK(t.value() == expect);
}

TEST_CASE(in_place_empty_ctor_test)
{
    opt t(in_place);
    TEST_REQUIRE(t.good());
    TEST_CHECK(t.value() == "");
}

TEST_CASE(initializer_list_in_place_ctor_test)
{
    const opt o1(in_place, {'H', 'e', 'l', 'l', 'o'});
    TEST_REQUIRE(o1.good());
    TEST_CHECK(o1.value() == "Hello");
}

TEST_CASE(uninit_nullopt_assign_test)
{
    opt t;
    t = nullopt;
    TEST_CHECK(not t.good());
}

TEST_CASE(init_nullopt_assign_test)
{
    std::string const x;
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
    opt t2("hello");
    t2 = t1;
    TEST_CHECK(not t2.good());
}

TEST_CASE(copy_assign_non_empty_to_empty_test)
{
    opt const t1("hello");
    opt t2;
    t2 = t1;
    TEST_REQUIRE(t1.good() && t2.good());
    TEST_CHECK(t2.value() == "hello");
}

TEST_CASE(copy_assign_non_empty_to_non_empty_test)
{
    opt const t1("hello");
    opt t2("world");
    t2 = t1;
    TEST_REQUIRE(t2.good() && t1.good());
    TEST_CHECK(t2.value() == "hello");
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
    opt t2("hello");
    t2 = static_cast<opt &&>(t1);
    TEST_REQUIRE(not t2.good());
}

TEST_CASE(move_assign_non_empty_to_empty_test)
{
    opt t1("hello");
    opt t2;
    t2 = static_cast<opt &&>(t1);
    TEST_REQUIRE(t2.good());
    TEST_CHECK(t2.value() == "hello");
}

TEST_CASE(move_assign_non_empty_to_non_empty_test)
{
    opt t1("hello");
    opt t2("bad");
    t2 = static_cast<opt &&>(t1);
    TEST_REQUIRE(t2.good());
    TEST_CHECK(t2.value() == "hello");
}


TEST_CASE(assign_value_to_empty_test)
{
    opt t;
    t = std::string("hello");
    TEST_REQUIRE(t.good());
    TEST_CHECK(t.value() == "hello");
}

TEST_CASE(assign_value_to_non_empty_test)
{
    opt t("bad");
    t = std::string("hello");
    TEST_REQUIRE(t.good());
    TEST_CHECK(t.value() == "hello");
}

TEST_CASE(emplace_test)
{
    opt t;
    t.emplace("hello");
    TEST_REQUIRE(t.good());
    TEST_CHECK(t.value() == "hello");
}

TEST_CASE(empty_emplace_test)
{
    opt t("bad");
    t.emplace();
    TEST_REQUIRE(t.good());
    TEST_CHECK(t.value() == "");
}

TEST_CASE(initializer_list_emplace_test)
{
    opt t;
    t.emplace({'h', 'e', 'l', 'l', 'o'});
    TEST_REQUIRE(t.good());
    TEST_CHECK(t.value() == "hello");
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
    std::string const x = "opt1";
    opt t1(x);
    opt t2;
    t1.swap(t2);
    TEST_REQUIRE(not t1.good() && t2.good());
    TEST_CHECK(t2.value() == x);
}

TEST_CASE(both_init_swap_test)
{
    std::string const x = "opt1";
    std::string const y = "opt2";
    opt t1(x);
    opt t2(y);
    t1.swap(t2);
    TEST_REQUIRE(t1.good() && t2.good());
    TEST_CHECK(t1.value() == y);
    TEST_CHECK(t2.value() == x);
}

TEST_CASE(const_arrow_operator_test)
{
    std::string const x = "hello";
    opt const t(x);
    TEST_REQUIRE(t.operator->());
    TEST_CHECK(*(t.operator->()) == x);
}

TEST_CASE(non_const_arrow_operator_test)
{
    std::string const x = "hello";
    opt t(x);
    TEST_REQUIRE(t.operator->());
    TEST_CHECK(*(t.operator->()) == x);
    *(t.operator->()) = "world";
    TEST_CHECK(t.value() == "world");
}

TEST_CASE(const_deref_operator_test)
{
    std::string const x = "hello";
    opt const t(x);
    TEST_CHECK(t.operator*() == x);
}

TEST_CASE(non_const_lvalue_deref_operator_test)
{
    std::string const x = "hello";
    opt t(x);
    TEST_CHECK(t.operator*() == x);
    t.operator*() = "world";
    TEST_CHECK(t.operator*() == "world");
}

TEST_CASE(rvalue_deref_operator_test)
{
    std::string const x = "hello";
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
    opt const t("test");
    TEST_CHECK(bool(t));
}

TEST_CASE(empty_good_test)
{
    opt const t;
    TEST_CHECK(not t.good());
}

TEST_CASE(non_empty_good_test)
{
    opt const t("test");
    TEST_CHECK(t.good());
}

TEST_CASE(const_value_test)
{
    opt const t("hello");
    TEST_CHECK(t.value() == "hello");
}

TEST_CASE(empty_const_value_test)
{
    opt const t;
    TEST_CHECK_THROW(elib::bad_optional_access, t.value());
}

TEST_CASE(non_const_value_test)
{
    opt t("hello");
    TEST_CHECK(t.value() == "hello");
    t.value() = "world";
    TEST_CHECK(t.value() == "world");
}

TEST_CASE(empty_non_const_value_test)
{
    opt t;
    TEST_CHECK_THROW(elib::bad_optional_access, t.value());
}

TEST_CASE(rvalue_value_test)
{
    opt t("hello");
    TEST_CHECK(static_cast<opt &&>(t).value() == "hello");
}

TEST_CASE(empty_rvalue_value_test)
{
    opt t;
    TEST_CHECK_THROW(elib::bad_optional_access, static_cast<opt &&>(t).value());
}

TEST_CASE(const_value_or_test)
{
    opt const t("hello");
    TEST_CHECK(t.value_or("world") == "hello");
}

TEST_CASE(empty_const_value_or_test)
{
    opt const t;
    TEST_CHECK(t.value_or("world") == "world");
}

TEST_CASE(rvalue_value_or_test)
{
    opt t("hello");
    TEST_CHECK(static_cast<opt &&>(t).value_or("world") == "hello");
}

TEST_CASE(empty_rvalue_value_or_test)
{
    opt t;
    TEST_CHECK(static_cast<opt &&>(t).value_or("world") == "world");
}

TEST_SUITE_END()