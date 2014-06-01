#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include <elib/container/detail/flat_map_base.hpp>
#include <functional>
#include <string>
#include <map>

// instantiation test
namespace elib { namespace container 
{
    template class flat_map_base<int, int, std::less<int>>;
    template class flat_map_base<std::string, std::string, std::less<std::string>>;
}}  

using map_type = elib::container::flat_map_base<int, int, std::less<int>>;
using value_type = map_type::value_type;
using compare = map_type::key_compare;
using iterator = map_type::iterator;
using const_iterator = map_type::const_iterator;
using reverse_iterator = map_type::reverse_iterator;
using const_reverse_iterator = map_type::const_reverse_iterator;

BOOST_AUTO_TEST_SUITE(container_flat_map_base_test_suite)



BOOST_AUTO_TEST_CASE(reverse_iterator_test)
{
    // non-const reverse_iterator
    {
        map_type m{{0, 0}, {1, 1}};
        reverse_iterator first = m.rbegin();
        reverse_iterator last = m.rend();
        BOOST_CHECK(first->first == 1);
        BOOST_CHECK((--last)->first == 0);
        
        BOOST_CHECK(first->second == 1);
        first->second = 2;
        BOOST_CHECK(first->second == 2);
        BOOST_CHECK(m.linear_at(1) == 2);
        
    }
    // const reverse_iterator
    {
        const map_type m{{0, 0}, {1, 1}};
        const_reverse_iterator first = m.rbegin();
        const_reverse_iterator last = m.rend();
        BOOST_CHECK(first->first == 1);
        BOOST_CHECK((--last)->first == 0);
    }
    // const reverse_iterator
    {
        map_type m{{0, 0}, {1, 1}};
        const_reverse_iterator first = m.crbegin();
        const_reverse_iterator last = m.crend();
        BOOST_CHECK(first->first == 1);
        BOOST_CHECK((--last)->first == 0);
    }
}

BOOST_AUTO_TEST_CASE(max_size_coverage_test)
{
    map_type m;
    BOOST_CHECK(m.max_size() > 0);
}

BOOST_AUTO_TEST_CASE(capacity_test)
{
    map_type m{{0, 0}};
    
    auto const cap = m.capacity();
    BOOST_CHECK(cap >= 1);
    m.reserve(cap + 5);
    BOOST_CHECK(m.capacity() >= cap + 5);
    BOOST_CHECK(m.size() == 1);
}

BOOST_AUTO_TEST_CASE(shrink_to_fit_coverage_test)
{
    map_type m;
    m.shrink_to_fit();
    BOOST_CHECK(true);
}

BOOST_AUTO_TEST_CASE(key_comp_test)
{
    const map_type m;
    compare cmp = m.key_comp();
    BOOST_CHECK( cmp(0, 1) );
    BOOST_CHECK(not cmp(1, 1) );
    BOOST_CHECK(not cmp(2, 1) );
}

BOOST_AUTO_TEST_CASE(value_comp_test)
{
    const value_type v1(0, 0);
    const value_type v2(1, 1);
    const map_type m;
    map_type::value_compare cmp = m.value_comp();
    BOOST_CHECK( cmp(v1, v2) );
    BOOST_CHECK( not cmp(v1, v1) );
    BOOST_CHECK( not cmp(v2, v1) );
}

BOOST_AUTO_TEST_SUITE_END()