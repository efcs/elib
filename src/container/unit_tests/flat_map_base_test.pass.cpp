// REQUIRES: ELIB_CONTAINER
#include <elib/container/detail/flat_map_base.hpp>
#include <functional>
#include <string>
#include <map>
#include "rapid-cxx-test.hpp"

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

TEST_SUITE(container_flat_map_base_test_suite)



TEST_CASE(reverse_iterator_test)
{
    // non-const reverse_iterator
    {
        map_type m{{0, 0}, {1, 1}};
        reverse_iterator first = m.rbegin();
        reverse_iterator last = m.rend();
        TEST_CHECK(first->first == 1);
        TEST_CHECK((--last)->first == 0);
        
        TEST_CHECK(first->second == 1);
        first->second = 2;
        TEST_CHECK(first->second == 2);
        TEST_CHECK(m.linear_at(1) == 2);
        
    }
    // const reverse_iterator
    {
        const map_type m{{0, 0}, {1, 1}};
        const_reverse_iterator first = m.rbegin();
        const_reverse_iterator last = m.rend();
        TEST_CHECK(first->first == 1);
        TEST_CHECK((--last)->first == 0);
    }
    // const reverse_iterator
    {
        map_type m{{0, 0}, {1, 1}};
        const_reverse_iterator first = m.crbegin();
        const_reverse_iterator last = m.crend();
        TEST_CHECK(first->first == 1);
        TEST_CHECK((--last)->first == 0);
    }
}

TEST_CASE(max_size_coverage_test)
{
    map_type m;
    TEST_CHECK(m.max_size() > 0);
}

TEST_CASE(capacity_test)
{
    map_type m{{0, 0}};
    
    auto const cap = m.capacity();
    TEST_CHECK(cap >= 1);
    m.reserve(cap + 5);
    TEST_CHECK(m.capacity() >= cap + 5);
    TEST_CHECK(m.size() == 1);
}

TEST_CASE(shrink_to_fit_coverage_test)
{
    map_type m;
    m.shrink_to_fit();
    TEST_CHECK(true);
}

TEST_CASE(key_comp_test)
{
    const map_type m;
    compare cmp = m.key_comp();
    TEST_CHECK( cmp(0, 1) );
    TEST_CHECK(not cmp(1, 1) );
    TEST_CHECK(not cmp(2, 1) );
}

TEST_CASE(value_comp_test)
{
    const value_type v1(0, 0);
    const value_type v2(1, 1);
    const map_type m;
    map_type::value_compare cmp = m.value_comp();
    TEST_CHECK( cmp(v1, v2) );
    TEST_CHECK( not cmp(v1, v1) );
    TEST_CHECK( not cmp(v2, v1) );
}

TEST_SUITE_END()