#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include <elib/compressed_pair.hpp>
#include <elib/aux/static_assert.hpp>
#include <elib/aux/move.hpp>
#include <cstdlib>
using namespace elib;

// weird constructor hopefully prevent compilers eliding it.
struct empty1 {
    empty1() {
        static int x = std::rand();
        ((void)x);
    }
};
struct empty2 {
    empty2() {
        static int x = std::rand();
        ((void)x);
    }
};
struct t1 {
    t1() {
        static int xx = std::rand();
        ((void)xx);
    }
    int x {};
};
struct t2 {
    t2() {
        static int xx = std::rand();
        ((void)xx);
    }
    int x {};
};

#define OPERATORS(Class)                                              \
    constexpr bool operator==(Class const &, Class const &) noexcept  \
    { return true; }                                                  \
                                                                      \
    constexpr bool operator !=(Class const &, Class const &) noexcept \
    { return false; }                                                 \
                                                                      \
    constexpr bool operator<(Class const &, Class const &) noexcept   \
    { return false; }
#

OPERATORS(empty1)
OPERATORS(empty2)
OPERATORS(t1)
OPERATORS(t2)

#undef OPERATORS


// neither compressed
namespace elib 
{
    template class compressed_pair<t1, t2>;
    template class compressed_pair<empty1, t1>;
    template class compressed_pair<t1, empty1>;
    template class compressed_pair<empty1, empty2>;
    template class compressed_pair<empty1, empty1>;
    template class compressed_pair<t1, t1>;
    
}                                                           // namespace elib

using pair1 = compressed_pair<t1, t2>;
using pair2 = compressed_pair<empty1, t1>;
using pair3 = compressed_pair<t1, empty1>;
using pair4 = compressed_pair<empty1, empty2>;
using pair5 = compressed_pair<empty1, empty1>;
using pair6 = compressed_pair<t1, t1>;
    

BOOST_AUTO_TEST_SUITE(elib_compressed_pair_test_suite)

BOOST_AUTO_TEST_CASE(compression_test)
{
    ELIB_STATIC_ASSERT(
        pair1::compression == compressed_pair_type::none
      );
    ELIB_STATIC_ASSERT(
        pair2::compression == compressed_pair_type::first
      );
    ELIB_STATIC_ASSERT(
        pair3::compression == compressed_pair_type::second
      );
    ELIB_STATIC_ASSERT(
        pair4::compression == compressed_pair_type::both
      );
    ELIB_STATIC_ASSERT(
        pair5::compression == compressed_pair_type::first
      );
    ELIB_STATIC_ASSERT(
        pair6::compression == compressed_pair_type::none
      );
    BOOST_CHECK(true);
}

BOOST_AUTO_TEST_CASE(default_ctor_test)
{
    pair1 p1;
    pair2 p2;
    pair3 p3;
    pair4 p4;
    pair5 p5;
    pair6 p6;
    BOOST_CHECK(true);
}

BOOST_AUTO_TEST_CASE(value_ctor_test)
{
    pair1 p1(t1{}, t2{});
    pair2 p2(empty1{}, t1{});
    pair3 p3(t1{}, empty1{});
    pair4 p4(empty1{}, empty2{});
    pair5 p5(empty1{}, empty1{});
    pair6 p6(t1{}, t1{});
    BOOST_CHECK(true);
}

BOOST_AUTO_TEST_CASE(copy_test)
{
    {
        pair1 const p1;
        pair1 const p2(p1);
        ((void)p2);
    }{
        pair2 const p1;
        pair2 const p2(p1);
        ((void)p2);
    }{
        pair3 const p1;
        pair3 const p2(p1);
        ((void)p2);
    }{
        pair4 const p1;
        pair4 const p2(p1);
        ((void)p2);
    }{
        pair5 const p1;
        pair5 const p2(p1);
        ((void)p2);
    }{
        pair6 const p1;
        pair6 const p2(p1);
        ((void)p2);
    }
    BOOST_CHECK(true);
}

BOOST_AUTO_TEST_CASE(move_test)
{
    {
        pair1 p1;
        pair1 p2(elib::move(p1));
        ((void)p2);
    }{
        pair2 p1;
        pair2 p2(elib::move(p1));
        ((void)p2);
    }{
        pair3 p1;
        pair3 p2(elib::move(p1));
        ((void)p2);
    }{
        pair4 p1;
        pair4 p2(elib::move(p1));
        ((void)p2);
    }{
        pair5 p1;
        pair5 p2(elib::move(p1));
        ((void)p2);
    }{
        pair6 p1;
        pair6 p2(elib::move(p1));
        ((void)p2);
    }
    BOOST_CHECK(true);
}

BOOST_AUTO_TEST_CASE(first_second_test)
{
    {
        pair1 p;
        p.first();
        p.second();
        
        pair1 const pc;
        pc.first();
        pc.second();
    }{
        pair2 p;
        p.first();
        p.second();
        
        pair2 const pc;
        pc.first();
        pc.second();
    }{
        pair3 p;
        p.first();
        p.second();
        
        pair3 const pc;
        pc.first();
        pc.second();
    }{
        pair4 p;
        p.first();
        p.second();
        
        pair4 const pc;
        pc.first();
        pc.second();
    }{
        pair5 p;
        p.first();
        p.second();
        
        pair5 const pc;
        pc.first();
        pc.second();
    }{
        pair6 p;
        p.first();
        p.second();
        
        pair6 const pc;
        pc.first();
        pc.second();
    }
    BOOST_CHECK(true);
}

BOOST_AUTO_TEST_CASE(swap_test)
{
    {
        pair1 p1;
        pair1 p2;
        p1.swap(p2);
        swap(p1, p2);
    }{
        pair2 p1;
        pair2 p2;
        p1.swap(p2);
        swap(p1, p2);
    }{
        pair3 p1;
        pair3 p2;
        p1.swap(p2);
        swap(p1, p2);
    }{
        pair4 p1;
        pair4 p2;
        p1.swap(p2);
        swap(p1, p2);
    }{
        pair5 p1;
        pair5 p2;
        p1.swap(p2);
        swap(p1, p2);
    }{
        pair6 p1;
        pair6 p2;
        p1.swap(p2);
        swap(p1, p2);
    }
    BOOST_CHECK(true);
}

BOOST_AUTO_TEST_CASE(equality_compare_test)
{
    bool ret{};
    {
        pair1 p1;
        pair1 p2;
        ret = (p1 == p2);
        ret = (p1 != p2);
        ret = (p1 < p2);
        ret = (p1 <= p2);
        ret = (p1 > p2);
        ret = (p1 >= p2);
    }{
        pair2 p1;
        pair2 p2;
        ret = (p1 == p2);
        ret = (p1 != p2);
        ret = (p1 < p2);
        ret = (p1 <= p2);
        ret = (p1 > p2);
        ret = (p1 >= p2);
    }{
        pair3 p1;
        pair3 p2;
        ret = (p1 == p2);
        ret = (p1 != p2);
        ret = (p1 < p2);
        ret = (p1 <= p2);
        ret = (p1 > p2);
        ret = (p1 >= p2);
    }{
        pair4 p1;
        pair4 p2;
        ret = (p1 == p2);
        ret = (p1 != p2);
        ret = (p1 < p2);
        ret = (p1 <= p2);
        ret = (p1 > p2);
        ret = (p1 >= p2);
    }{
        pair5 p1;
        pair5 p2;
        ret = (p1 == p2);
        ret = (p1 != p2);
        ret = (p1 < p2);
        ret = (p1 <= p2);
        ret = (p1 > p2);
        ret = (p1 >= p2);
    }{
        pair6 p1;
        pair6 p2;
        ret = (p1 == p2);
        ret = (p1 != p2);
        ret = (p1 < p2);
        ret = (p1 <= p2);
        ret = (p1 > p2);
        ret = (p1 >= p2);
    }
    BOOST_CHECK(true);
}

BOOST_AUTO_TEST_CASE(make_compressed_pair_test)
{
    make_compressed_pair(t1{}, t2{});
    make_compressed_pair(empty1{}, t1{});
    make_compressed_pair(t1{}, empty1{});
    make_compressed_pair(empty1{}, empty2{});
    make_compressed_pair(empty1{}, empty1{});
    make_compressed_pair(t1{}, t1{});
    BOOST_CHECK(true);
}

BOOST_AUTO_TEST_SUITE_END()