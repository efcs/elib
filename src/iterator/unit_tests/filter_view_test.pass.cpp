// REQUIRES: ELIB_ITERATOR
#include <elib/iterator.hpp>
#include <elib/aux/static_assert.hpp>
#include <elib/aux/traits/is_same.hpp>
#include <iterator>
#include <vector>
#include "rapid-cxx-test.hpp"

using vector_t = std::vector<int>;
using const_iterator_t = vector_t::const_iterator;

struct pred_t
{
    bool operator()(int x) { return x % 2 == 0; }
};

using filter_t = elib::iter::filter_view<vector_t, pred_t>;
using const_filter_t = elib::iter::filter_view<const vector_t, pred_t>;

using rfilter_t = elib::iter::reverse_filter_view<vector_t, pred_t>;
using const_rfilter_t = elib::iter::reverse_filter_view<const vector_t, pred_t>;


TEST_SUITE(elib_iterator_filter_view_test_suite)


TEST_CASE(non_const_ctor_test)
{
    vector_t s;
    pred_t p;
    const vector_t cs;
    {
        filter_t v(s);
    }{
        filter_t v(s, p);
    }{
        const_filter_t v(s);
    }{
        const_filter_t v(s, p);
    }{
        const_filter_t v(cs);
    }{ 
        const_filter_t v(cs, p);
    }{
        rfilter_t v(s);
    }{
        rfilter_t v(s, p);
    }{
        const_rfilter_t v(s);
    }{
        const_rfilter_t v(s, p);
    }{
        const_rfilter_t v(cs);
    }{ 
        const_rfilter_t v(cs, p);
    }
}

TEST_CASE(assign_test)
{
    vector_t s;
    vector_t s2;
    const vector_t cs;
    {
        filter_t v(s);
        v = s2;
    }{
        const_filter_t v(s);
        v = cs;
    }{
        rfilter_t v(s);
        v = s2;
    }{
        const_rfilter_t v(s);
        v = cs;
    }
}

TEST_CASE(swap_test)
{
    vector_t s;
    vector_t s2;
    
    {
        filter_t v1(s);
        filter_t v2(s2);
        v1.swap(v2);
        swap(v1, v2);
    }{
        const_filter_t v1(s);
        const_filter_t v2(s2);
        v1.swap(v2);
        swap(v1, v2);
    }{
        rfilter_t v1(s);
        rfilter_t v2(s2);
        v1.swap(v2);
        swap(v1, v2);
    }{
        const_rfilter_t v1(s);
        const_rfilter_t v2(s2);
        v1.swap(v2);
        swap(v1, v2);
    }
}

TEST_CASE(begin_end_test)
{
    vector_t in = {0, 1, 2, 3, 4, 5};
    const vector_t expect = {0, 2, 4};
    
    filter_t f(in);
    const filter_t cf(in);
    
    TEST_CHECK_EQUAL_COLLECTIONS(
        f.begin(), f.end()
      , expect.begin(), expect.end()
      );
    
    TEST_CHECK_EQUAL_COLLECTIONS(
        begin(f), end(f)
      , expect.begin(), expect.end()
      );
    
    TEST_CHECK_EQUAL_COLLECTIONS(
        f.cbegin(), f.cend()
      , expect.begin(), expect.end()
      );
    
    TEST_CHECK_EQUAL_COLLECTIONS(
        cf.begin(), cf.end()
      , expect.begin(), expect.end()
      );
    
    TEST_CHECK_EQUAL_COLLECTIONS(
        begin(cf), end(cf)
      , expect.begin(), expect.end()
      );
    
    TEST_CHECK_EQUAL_COLLECTIONS(
        f.rbegin(), f.rend()
      , expect.rbegin(), expect.rend()
      );
    
    TEST_CHECK_EQUAL_COLLECTIONS(
        rbegin(f), rend(f)
      , expect.rbegin(), expect.rend()
      );
    
    TEST_CHECK_EQUAL_COLLECTIONS(
        f.crbegin(), f.crend()
      , expect.rbegin(), expect.rend()
      );
    
    TEST_CHECK_EQUAL_COLLECTIONS(
        cf.rbegin(), cf.rend()
      , expect.rbegin(), expect.rend()
      );
    
    TEST_CHECK_EQUAL_COLLECTIONS(
        rbegin(cf), rend(cf)
      , expect.rbegin(), expect.rend()
      );
}

TEST_CASE(rbegin_rend_test)
{
    vector_t in = {0, 1, 2, 3, 4, 5};
    const vector_t expect = {4, 2, 0};
    
    rfilter_t f(in);
    const rfilter_t cf(in);
    
    TEST_CHECK_EQUAL_COLLECTIONS(
        f.begin(), f.end()
      , expect.begin(), expect.end()
      );
    
    TEST_CHECK_EQUAL_COLLECTIONS(
        begin(f), end(f)
      , expect.begin(), expect.end()
      );
    
    TEST_CHECK_EQUAL_COLLECTIONS(
        f.cbegin(), f.cend()
      , expect.begin(), expect.end()
      );
    
    TEST_CHECK_EQUAL_COLLECTIONS(
        cf.begin(), cf.end()
      , expect.begin(), expect.end()
      );
    
    TEST_CHECK_EQUAL_COLLECTIONS(
        begin(cf), end(cf)
      , expect.begin(), expect.end()
      );
}

TEST_SUITE_END()