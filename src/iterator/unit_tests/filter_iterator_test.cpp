#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include <elib/iterator.hpp>
#include <elib/aux/static_assert.hpp>
#include <elib/aux/traits/is_same.hpp>
#include <iterator>
#include <vector>


using vector_t = std::vector<int>;
using const_iterator_t = vector_t::const_iterator;

auto is_even = [](int x) { return x % 2 == 0; };
using pred_t = decltype(is_even);

using filter_t = elib::iter::filter_iterator<const_iterator_t, pred_t>;

BOOST_AUTO_TEST_SUITE(elib_iterator_filter_iterator_test_suite)

#define ASSERT_SAME(...) ELIB_STATIC_ASSERT(::elib::aux::is_same<__VA_ARGS__>::value)
BOOST_AUTO_TEST_CASE(traits_test)
{
    using Traits = std::iterator_traits<const_iterator_t>;
    
    ASSERT_SAME(filter_t::value_type, Traits::value_type);
    ASSERT_SAME(filter_t::reference, filter_t::reference);
    ASSERT_SAME(filter_t::pointer, Traits::pointer);
    ASSERT_SAME(filter_t::difference_type, Traits::difference_type);
    ASSERT_SAME(filter_t::iterator_category, std::forward_iterator_tag);
    BOOST_CHECK(true);
}
#undef ASSERT_SAME

BOOST_AUTO_TEST_CASE(construct_test)
{
    {
        const vector_t in = { 1 };
        filter_t const end(is_even, in.end(), in.end());
        filter_t filt(is_even, in.begin(), in.end());
        BOOST_CHECK(filt == end);
    }{
        const vector_t in = { 2 };
        filter_t const end(is_even, in.end(), in.end());
        filter_t filt(is_even, in.begin(), in.end());
        BOOST_CHECK(filt != end);
    }{
        const vector_t in = { 1, 2 };
        filter_t const end(is_even, in.end(), in.end());
        filter_t filt(is_even, in.begin(), in.end());
        BOOST_CHECK(filt != end);
    }
}


BOOST_AUTO_TEST_CASE(empty_test)
{
    const vector_t in = {};
    const vector_t expect = {};
    
    filter_t const end(is_even, in.end(), in.end());
    filter_t begin(is_even, in.begin(), in.end());
    
    BOOST_CHECK_EQUAL_COLLECTIONS(
        begin, end
      , expect.begin(), expect.end()
      );
}

BOOST_AUTO_TEST_CASE(good_and_bad_test)
{
    const vector_t in = {0, 1, 2, 3, 4, 5};
    const vector_t expect = {0, 2, 4};
    
    filter_t const end(is_even, in.end(), in.end());
    filter_t begin(is_even, in.begin(), in.end());
    
    BOOST_CHECK_EQUAL_COLLECTIONS(
        begin, end
      , expect.begin(), expect.end()
      );
}

BOOST_AUTO_TEST_CASE(all_bad_test)
{
    const vector_t in = {1, 3, 5, 7};
    const vector_t expect = {};
    
    filter_t const end(is_even, in.end(), in.end());
    filter_t begin(is_even, in.begin(), in.end());
    
    BOOST_CHECK_EQUAL_COLLECTIONS(
        begin, end
      , expect.begin(), expect.end()
      );
}

BOOST_AUTO_TEST_CASE(all_good_test)
{
    const vector_t in = {0, 2, 4, 6};
    const vector_t expect = {0, 2, 4, 6};
    
    filter_t const end(is_even, in.end(), in.end());
    filter_t begin(is_even, in.begin(), in.end());
    
    BOOST_CHECK_EQUAL_COLLECTIONS(
        begin, end
      , expect.begin(), expect.end()
      );
}

BOOST_AUTO_TEST_CASE(equality_test)
{
    const vector_t in = {0, 1, 2};
    
    filter_t const end(is_even, in.end(), in.end());
    
    filter_t it(is_even, in.begin(), in.end());
    filter_t it2(is_even, in.begin(), in.end());
    
    BOOST_REQUIRE(it != end);
    BOOST_CHECK(it == it2);
    
    ++it;
    BOOST_REQUIRE(it != end);
    BOOST_CHECK(it != it2);
    
    ++it;
    ++it2;
    BOOST_CHECK(it == end);
    BOOST_CHECK(it2 != end);
    BOOST_CHECK(it != it2);
}

BOOST_AUTO_TEST_CASE(postfix_increment_test)
{
    const vector_t in = {0, 1, 2};
    
    filter_t const end(is_even, in.end(), in.end());
    
    filter_t it(is_even, in.begin(), in.end());
    filter_t it2(is_even, in.begin(), in.end());
    
    BOOST_REQUIRE(it != end);
    BOOST_CHECK(it == it2);
    
    filter_t it3 = it++;
    BOOST_CHECK(it3 != it);
    BOOST_CHECK(it3 == it2);
}

BOOST_AUTO_TEST_CASE(deref_test)
{
    const vector_t in = {0, 1};
    
    filter_t const end(is_even, in.end(), in.end());
    
    filter_t it(is_even, in.begin(), in.end());
    
    BOOST_REQUIRE(it != end);
    BOOST_CHECK(*it == 0);
    BOOST_CHECK(*(it.operator->()) == 0);
}

BOOST_AUTO_TEST_CASE(position_test)
{
    const vector_t in = {0, 1};
    
    filter_t const end(is_even, in.end(), in.end());
    
    filter_t it(is_even, in.begin(), in.end());
    BOOST_CHECK(it.position() == in.begin());
    ++it;
    BOOST_REQUIRE(it == end);
    BOOST_CHECK(it.position() == in.end());
}

BOOST_AUTO_TEST_SUITE_END()
