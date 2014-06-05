#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include <elib/optional.hpp>
#include <string>
using opt = elib::optional<std::string>;
using elib::nullopt;
using elib::in_place;

BOOST_AUTO_TEST_SUITE(elib_optional_optional_string_test_suite)

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
    std::string const x = "hello";
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
    std::string const x = "hello";
    opt t(x);
    opt t2(static_cast<opt &&>(t));
    BOOST_REQUIRE(t2.good());
    BOOST_CHECK(t2.value() == x);
}


BOOST_AUTO_TEST_CASE(value_copy_ctor_test)
{
    {
        std::string const x = "hello";
        opt t(x);
        BOOST_REQUIRE(t.good());
        BOOST_CHECK(t.value() == x);
    }{
        std::string const x = "hello";
        const opt t(x);
        BOOST_REQUIRE(t.good());
        BOOST_CHECK(t.value() == x);
    }
}

BOOST_AUTO_TEST_CASE(value_move_ctor_test)
{
    std::string const expect = "hello";
    {
        opt t(std::string("hello"));
        BOOST_REQUIRE(t.good());
        BOOST_CHECK(t.value() == expect);
    }{
        const opt t(std::string("hello"));
        BOOST_REQUIRE(t.good());
        BOOST_CHECK(t.value() == expect);
    }
}

BOOST_AUTO_TEST_CASE(in_place_ctor_test)
{
    std::string const expect = "hello";
    opt t(in_place, "hello");
    BOOST_REQUIRE(t.good());
    BOOST_CHECK(t.value() == expect);
}

BOOST_AUTO_TEST_CASE(in_place_empty_ctor_test)
{
    opt t(in_place);
    BOOST_REQUIRE(t.good());
    BOOST_CHECK(t.value() == "");
}

BOOST_AUTO_TEST_CASE(initializer_list_in_place_ctor_test)
{
    const opt o1(in_place, {'H', 'e', 'l', 'l', 'o'});
    BOOST_REQUIRE(o1.good());
    BOOST_CHECK(o1.value() == "Hello");
}

BOOST_AUTO_TEST_CASE(uninit_nullopt_assign_test)
{
    opt t;
    t = nullopt;
    BOOST_CHECK(not t.good());
}

BOOST_AUTO_TEST_CASE(init_nullopt_assign_test)
{
    std::string const x;
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
    opt t2("hello");
    t2 = t1;
    BOOST_CHECK(not t2.good());
}

BOOST_AUTO_TEST_CASE(copy_assign_non_empty_to_empty_test)
{
    opt const t1("hello");
    opt t2;
    t2 = t1;
    BOOST_REQUIRE(t1.good() && t2.good());
    BOOST_CHECK(t2.value() == "hello");
}

BOOST_AUTO_TEST_CASE(copy_assign_non_empty_to_non_empty_test)
{
    opt const t1("hello");
    opt t2("world");
    t2 = t1;
    BOOST_REQUIRE(t2.good() && t1.good());
    BOOST_CHECK(t2.value() == "hello");
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
    opt t2("hello");
    t2 = static_cast<opt &&>(t1);
    BOOST_REQUIRE(not t2.good());
}

BOOST_AUTO_TEST_CASE(move_assign_non_empty_to_empty_test)
{
    opt t1("hello");
    opt t2;
    t2 = static_cast<opt &&>(t1);
    BOOST_REQUIRE(t2.good());
    BOOST_CHECK(t2.value() == "hello");
}

BOOST_AUTO_TEST_CASE(move_assign_non_empty_to_non_empty_test)
{
    opt t1("hello");
    opt t2("bad");
    t2 = static_cast<opt &&>(t1);
    BOOST_REQUIRE(t2.good());
    BOOST_CHECK(t2.value() == "hello");
}


BOOST_AUTO_TEST_CASE(assign_value_to_empty_test)
{
    opt t;
    t = std::string("hello");
    BOOST_REQUIRE(t.good());
    BOOST_CHECK(t.value() == "hello");
}

BOOST_AUTO_TEST_CASE(assign_value_to_non_empty_test)
{
    opt t("bad");
    t = std::string("hello");
    BOOST_REQUIRE(t.good());
    BOOST_CHECK(t.value() == "hello");
}

BOOST_AUTO_TEST_CASE(emplace_test)
{
    opt t;
    t.emplace("hello");
    BOOST_REQUIRE(t.good());
    BOOST_CHECK(t.value() == "hello");
}

BOOST_AUTO_TEST_CASE(empty_emplace_test)
{
    opt t("bad");
    t.emplace();
    BOOST_REQUIRE(t.good());
    BOOST_CHECK(t.value() == "");
}

BOOST_AUTO_TEST_CASE(initializer_list_emplace_test)
{
    opt t;
    t.emplace({'h', 'e', 'l', 'l', 'o'});
    BOOST_REQUIRE(t.good());
    BOOST_CHECK(t.value() == "hello");
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
    std::string const x = "opt1";
    opt t1(x);
    opt t2;
    t1.swap(t2);
    BOOST_REQUIRE(not t1.good() && t2.good());
    BOOST_CHECK(t2.value() == x);
}

BOOST_AUTO_TEST_CASE(both_init_swap_test)
{
    std::string const x = "opt1";
    std::string const y = "opt2";
    opt t1(x);
    opt t2(y);
    t1.swap(t2);
    BOOST_REQUIRE(t1.good() && t2.good());
    BOOST_CHECK(t1.value() == y);
    BOOST_CHECK(t2.value() == x);
}

BOOST_AUTO_TEST_CASE(const_arrow_operator_test)
{
    std::string const x = "hello";
    opt const t(x);
    BOOST_REQUIRE(t.operator->());
    BOOST_CHECK(*(t.operator->()) == x);
}

BOOST_AUTO_TEST_CASE(non_const_arrow_operator_test)
{
    std::string const x = "hello";
    opt t(x);
    BOOST_REQUIRE(t.operator->());
    BOOST_CHECK(*(t.operator->()) == x);
    *(t.operator->()) = "world";
    BOOST_CHECK(t.value() == "world");
}

BOOST_AUTO_TEST_CASE(const_deref_operator_test)
{
    std::string const x = "hello";
    opt const t(x);
    BOOST_CHECK(t.operator*() == x);
}

BOOST_AUTO_TEST_CASE(non_const_lvalue_deref_operator_test)
{
    std::string const x = "hello";
    opt t(x);
    BOOST_CHECK(t.operator*() == x);
    t.operator*() = "world";
    BOOST_CHECK(t.operator*() == "world");
}

BOOST_AUTO_TEST_CASE(rvalue_deref_operator_test)
{
    std::string const x = "hello";
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
    opt const t("test");
    BOOST_CHECK(bool(t));
}

BOOST_AUTO_TEST_CASE(empty_good_test)
{
    opt const t;
    BOOST_CHECK(not t.good());
}

BOOST_AUTO_TEST_CASE(non_empty_good_test)
{
    opt const t("test");
    BOOST_CHECK(t.good());
}

BOOST_AUTO_TEST_CASE(const_value_test)
{
    opt const t("hello");
    BOOST_CHECK(t.value() == "hello");
}

BOOST_AUTO_TEST_CASE(empty_const_value_test)
{
    opt const t;
    BOOST_CHECK_THROW(t.value(), elib::bad_optional_access);
}

BOOST_AUTO_TEST_CASE(non_const_value_test)
{
    opt t("hello");
    BOOST_CHECK(t.value() == "hello");
    t.value() = "world";
    BOOST_CHECK(t.value() == "world");
}

BOOST_AUTO_TEST_CASE(empty_non_const_value_test)
{
    opt t;
    BOOST_CHECK_THROW(t.value(), elib::bad_optional_access);
}

BOOST_AUTO_TEST_CASE(rvalue_value_test)
{
    opt t("hello");
    BOOST_CHECK(static_cast<opt &&>(t).value() == "hello");
}

BOOST_AUTO_TEST_CASE(empty_rvalue_value_test)
{
    opt t;
    BOOST_CHECK_THROW(static_cast<opt &&>(t).value(), elib::bad_optional_access);
}

BOOST_AUTO_TEST_CASE(const_value_or_test)
{
    opt const t("hello");
    BOOST_CHECK(t.value_or("world") == "hello");
}

BOOST_AUTO_TEST_CASE(empty_const_value_or_test)
{
    opt const t;
    BOOST_CHECK(t.value_or("world") == "world");
}

BOOST_AUTO_TEST_CASE(rvalue_value_or_test)
{
    opt t("hello");
    BOOST_CHECK(static_cast<opt &&>(t).value_or("world") == "hello");
}

BOOST_AUTO_TEST_CASE(empty_rvalue_value_or_test)
{
    opt t;
    BOOST_CHECK(static_cast<opt &&>(t).value_or("world") == "world");
}

BOOST_AUTO_TEST_SUITE_END()