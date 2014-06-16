// REQUIRES: ELIB_AUX_SOURCE
#include <elib/aux.hpp>
#include "rapid-cxx-test.hpp"

using namespace elib;

struct move_type
{
    move_type() {}
    move_type(move_type const &)  = delete;
    move_type(move_type &&) noexcept {}
};

struct copy_type
{
    copy_type() {}
    copy_type(copy_type const &) {}
    copy_type(copy_type &&) = delete;
};

struct except_move
{
    except_move() {}
    except_move(except_move const &) {}
    except_move(except_move &&) noexcept(false) {}
};

struct dummy_t {};

TEST_SUITE(aux_move_test_suite)

TEST_CASE(aux_move_test)
{
    dummy_t d;
    elib::move(d);
    static_assert(
        aux::is_rvalue_reference<decltype(elib::move(d))>::value
      , "Must be rvalue"
      );
    
    elib::move(dummy_t{});
    static_assert(
        aux::is_rvalue_reference<decltype(elib::move(dummy_t{}))>::value
      , "Must be rvalue"
      );
    
    // DUMMY
    TEST_CHECK(true);
}

TEST_CASE(aux_move_move_type)
{
    move_type t;
    elib::move_if_noexcept(t);
    static_assert(
        aux::is_rvalue_reference<decltype(elib::move_if_noexcept(t))>::value
      , "Must return rvalue"
      );
    
    // DUMMY
    TEST_CHECK(true);
}

TEST_CASE(aux_move_copy_type)
{
    copy_type t;
    elib::move_if_noexcept(t);
    static_assert(
        aux::is_lvalue_reference<decltype(elib::move_if_noexcept(t))>::value
      , "Must return lvalue"
      );
    
    // DUMMY
    TEST_CHECK(true);
}

TEST_CASE(aux_move_except_move)
{
    except_move t;
    elib::move_if_noexcept(t);
    static_assert(
        aux::is_lvalue_reference<decltype(elib::move_if_noexcept(t))>::value
      , "Must return lvalue"
      );
    
    // DUMMY
    TEST_CHECK(true);
}


TEST_SUITE_END()