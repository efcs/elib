// REQUIRES: ELIB_CONTAINER_SOURCE, ELIB_BOOST_TEST
#define BOOST_TEST_MODULE Main
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include <elib/container/linear_flat_map.hpp>
#include <string>
#include <utility>

// instantiation test
namespace elib { namespace container 
{
    template class linear_flat_map<int, int>;
    template class linear_flat_map<std::string, std::string>;
}}  

using map_type = elib::linear_flat_map<int, int>;
using compare = map_type::key_compare;
using iterator = map_type::iterator;
using const_iterator = map_type::const_iterator;

BOOST_AUTO_TEST_SUITE(container_linear_flat_map_test_suite)

BOOST_AUTO_TEST_CASE(constructor_test)
{
    {
        const map_type m;
        BOOST_CHECK(m.empty());
    }
    {
        const map_type m;
        const map_type cp(m);
        BOOST_CHECK(cp == m);
    }
    {
        const map_type m((map_type()));
        BOOST_CHECK(m.empty());
    }
    {
        compare cmp;
        const map_type m(cmp);
    }
    {
        const map_type m1{{0, 0}, {1, 1}, {2, 2}};
        const map_type m2(m1.begin(), m1.end());
        BOOST_CHECK(m1.size() == 3);
        BOOST_CHECK(m2.size() == 3);
        BOOST_CHECK(m1 == m2);
    }
}

BOOST_AUTO_TEST_CASE(assignment_test)
{
    {
        map_type m1{{0, 0}, {1, 1}, {2, 2}};
        BOOST_CHECK(not m1.empty());
        const map_type m2;
        m1 = m2;
        BOOST_CHECK(m1.empty());
        BOOST_CHECK(m1 == m2);
    }
    {
        map_type m1{{0, 0}, {1, 1}, {2, 2}};
        BOOST_CHECK(not m1.empty());
        m1 = map_type();
        BOOST_CHECK(m1.empty());
    }
    {
        map_type m1;
        BOOST_CHECK(m1.empty());
        m1 = {{0, 0}, {1, 1}};
        BOOST_CHECK(m1.size() == 2);
    }
}

BOOST_AUTO_TEST_CASE(access_test)
{
    {
        const map_type m1{{0, 0}, {1, 1}, {2, 2}};
        BOOST_CHECK(m1.at(0) == 0);
        BOOST_CHECK(m1.at(1) == 1);
        BOOST_CHECK(m1.at(2) == 2);
        BOOST_CHECK_THROW(m1.at(3), std::out_of_range);
    }
    {
        map_type m1{{0, 0}, {1, 1}, {2, 2}};
        BOOST_CHECK(m1.at(0) == 0);
        BOOST_CHECK(m1.at(1) == 1);
        BOOST_CHECK(m1.at(2) == 2);
        BOOST_CHECK_THROW(m1.at(3), std::out_of_range);
    }
    {
        map_type m1{{0, 0}, {1, 1}, {2, 2}};
        
        int key = 0;
        BOOST_CHECK(m1[key] == 0);
        key = 1;
        BOOST_CHECK(m1[key] == 1);
        key = 2;
        BOOST_CHECK(m1[key] == 2);
        
        BOOST_CHECK(m1.size() == 3);
        key = 3;
        m1[key] = 3;
        BOOST_CHECK(m1.size() == 4);
        BOOST_CHECK(m1[key] == 3);
    }
    {
        map_type m1{{0, 0}, {1, 1}, {2, 2}};
        
        BOOST_CHECK(m1[0] == 0);
        BOOST_CHECK(m1[1] == 1);
        BOOST_CHECK(m1[2] == 2);
        
        BOOST_CHECK(m1.size() == 3);
        m1[3] = 3;
        BOOST_CHECK(m1.size() == 4);
        BOOST_CHECK(m1[3] == 3);
    }
}

BOOST_AUTO_TEST_CASE(insert_test)
{
    // insert pair
    {
        map_type::value_type p(0, 0);
        map_type m;
        auto ret = m.insert(static_cast<map_type::value_type const &>(p));
        BOOST_CHECK(ret.second);
        BOOST_CHECK(ret.first->first == 0);
        BOOST_CHECK(ret.first->second == 0);
        BOOST_CHECK(m.size() == 1);
        BOOST_CHECK(m.at(0) == 0);
        
        p.second = 1;
        ret = m.insert(static_cast<map_type::value_type const &>(p));
        BOOST_CHECK(not ret.second);
        BOOST_CHECK(ret.first->first == 0);
        BOOST_CHECK(ret.first->second == 0);
        BOOST_CHECK(m.size() == 1);
        BOOST_CHECK(m.at(0) == 0);
    }
    // insert pair rvalue
    {
        map_type m;
        auto ret = m.insert(map_type::value_type(0, 0));
        BOOST_CHECK(ret.second);
        BOOST_CHECK(ret.first->first == 0);
        BOOST_CHECK(ret.first->second == 0);
        BOOST_CHECK(m.size() == 1);
        BOOST_CHECK(m.at(0) == 0);
        
        ret = m.insert(map_type::value_type(0, 1));
        BOOST_CHECK(not ret.second);
        BOOST_CHECK(ret.first->first == 0);
        BOOST_CHECK(ret.first->second == 0);
        BOOST_CHECK(m.size() == 1);
        BOOST_CHECK(m.at(0) == 0);
    }
    // insert pair position
    {
        map_type m;
        map_type::value_type p(0, 0);
        auto ret = m.insert(m.cbegin(), static_cast<map_type::value_type const &>(p));
        BOOST_CHECK(ret->first == 0);
        BOOST_CHECK(ret->second == 0);
        BOOST_CHECK(m.size() == 1);
        BOOST_CHECK(m.at(0) == 0);
        
        p.second = 1;
        ret = m.insert(m.cbegin(), static_cast<map_type::value_type const &>(p));
        ret = m.insert(m.cbegin(), p);
        BOOST_CHECK(ret->first == 0);
        BOOST_CHECK(ret->second == 0);
        BOOST_CHECK(m.size() == 1);
        BOOST_CHECK(m.at(0) == 0);
    }
    // insert rvalue pair position
    {
        map_type m;
        auto ret = m.insert(m.cbegin(), std::make_pair(0, 0));
        BOOST_CHECK(ret->first == 0);
        BOOST_CHECK(ret->second == 0);
        BOOST_CHECK(m.size() == 1);
        BOOST_CHECK(m.at(0) == 0);
        
        ret = m.insert(m.cbegin(), std::make_pair(0, 1));
        BOOST_CHECK(ret->first == 0);
        BOOST_CHECK(ret->second == 0);
        BOOST_CHECK(m.size() == 1);
        BOOST_CHECK(m.at(0) == 0);
    }
    // insert range
    {
        map_type m1{{0, 0}, {1, 1}, {2, 2}};
        map_type m2;
        BOOST_CHECK(m2.empty());
        m2.insert(m1.begin(), m1.end());
        BOOST_CHECK(m2.size() == 3);
        BOOST_CHECK(m2.at(0) == 0);
        BOOST_CHECK(m2.at(1) == 1);
        BOOST_CHECK(m2.at(2) == 2);
        BOOST_CHECK(m1 == m2);
    }
    // insert init_list
    {
        map_type m;
        BOOST_CHECK(m.empty());
        m.insert({{0, 0}, {1, 1}, {2, 2}});
        BOOST_CHECK(m.size() == 3);
        BOOST_CHECK(m.at(0) == 0);
        BOOST_CHECK(m.at(1) == 1);
        BOOST_CHECK(m.at(2) == 2);
    }
}


BOOST_AUTO_TEST_CASE(erase_key_test)
{
    map_type m;
    BOOST_CHECK(m.erase(0) == 0);
    m.insert(std::make_pair(0, 0));
    BOOST_CHECK(m.size() == 1);
    BOOST_CHECK(m.at(0) == 0);
    m.erase(1);
    BOOST_CHECK(m.size() == 1);
    m.erase(0);
    BOOST_CHECK(m.size() == 0);
}

BOOST_AUTO_TEST_CASE(erase_position_test)
{
    map_type m{{1, 1}, {2, 2}};
    BOOST_CHECK(m.size() == 2);
    
    iterator pos = m.erase(m.cbegin());
    BOOST_CHECK(pos == m.begin());
    BOOST_CHECK(pos->first == 2);
    BOOST_CHECK(m.size() == 1);
    
    pos = m.erase(m.cbegin());
    BOOST_CHECK(pos == m.end());
    BOOST_CHECK(m.size() == 0);
}

BOOST_AUTO_TEST_CASE(erase_range_test)
{
    map_type m{{0, 0}, {1, 1}, {2, 2}, {3, 3}, {4, 4}};
    BOOST_CHECK(m.size() == 5);
    
    iterator pos = m.erase(m.cend(), m.cend());
    BOOST_CHECK(pos == m.cend());
    BOOST_CHECK(m.size() == 5);
    
    pos = m.erase(m.cbegin(), m.cbegin());
    BOOST_CHECK(pos == m.begin());
    BOOST_CHECK(m.size() == 5);

    // erase first element
    pos = m.erase(m.cbegin(), ++m.cbegin());
    BOOST_CHECK(pos == m.begin());
    BOOST_CHECK(m.size() == 4);
    BOOST_CHECK(pos->first == 1);
    // range is not {1, 1}, {2, 2}, {3, 3}, {4, 4}
    
    // erase last two elements
    pos = m.erase(m.cbegin() + 2, m.cend());
    BOOST_CHECK(pos == m.end());
    BOOST_CHECK(m.size() == 2);
    // range is now {1, 1}, {2, 2}
    
    pos = m.erase(m.cbegin(), m.cend());
    BOOST_CHECK(pos == m.end());
    BOOST_CHECK(m.empty());
    
}

BOOST_AUTO_TEST_CASE(clear_test)
{
    map_type m1{{0, 0}, {1, 1}};
    BOOST_CHECK(not m1.empty());
    m1.clear();
    BOOST_CHECK(m1.empty());
}

BOOST_AUTO_TEST_CASE(swap_test)
{
    const map_type m1{{0, 0}, {1, 1}};
    map_type m1_cp(m1);
    
    const map_type m2{{2, 2}};
    map_type m2_cp(m2);
    
    BOOST_REQUIRE(m1 == m1_cp);
    BOOST_REQUIRE(m2 == m2_cp);
    m1_cp.swap(m2_cp);
    BOOST_CHECK(m1_cp == m2);
    BOOST_CHECK(m2_cp == m1);
    
    swap(m1_cp, m2_cp);
    BOOST_CHECK(m1_cp == m1);
    BOOST_CHECK(m2_cp == m2);
}

BOOST_AUTO_TEST_CASE(count_test)
{
    map_type m{{1, 1}};
    BOOST_CHECK(m.count(0) == 0);
    BOOST_CHECK(m.count(1) == 1);
}

BOOST_AUTO_TEST_CASE(equal_range_test)
{
    // const equal_range test
    {
        const map_type m{{1, 1}, {2, 2}};
        std::pair<const_iterator, const_iterator> ret = m.equal_range(0);
        BOOST_CHECK(ret.first->first == 1);
        BOOST_CHECK(ret.second->first == 1);
        
        ret = m.equal_range(1);
        BOOST_CHECK(ret.first->first == 1);
        BOOST_CHECK(ret.second->first == 2);
        
        ret = m.equal_range(2);
        BOOST_CHECK(ret.first->first == 2);
        BOOST_CHECK(ret.second == m.cend());
        
        ret = m.equal_range(3);
        BOOST_CHECK(ret.first == m.cend());
        BOOST_CHECK(ret.second == m.cend());
    }
    // non-const equal_range_test
    {
        map_type m{{1, 1}, {2, 2}};
        std::pair<iterator, iterator> ret = m.equal_range(0);
        BOOST_CHECK(ret.first->first == 1);
        BOOST_CHECK(ret.second->first == 1);
        
        // try modifying the value
        BOOST_CHECK(ret.first->second == 1);
        ret.first->second = 2;
        BOOST_CHECK(ret.first->second == 2);
        BOOST_CHECK(m.at(1) == 2);
        
        
        ret = m.equal_range(1);
        BOOST_CHECK(ret.first->first == 1);
        BOOST_CHECK(ret.second->first == 2);
        
        ret = m.equal_range(2);
        BOOST_CHECK(ret.first->first == 2);
        BOOST_CHECK(ret.second == m.end());
        
        ret = m.equal_range(3);
        BOOST_CHECK(ret.first == m.end());
        BOOST_CHECK(ret.second == m.end());
    }
}

BOOST_AUTO_TEST_CASE(find_test)
{
    // const find test
    {
        const map_type m{{1, 1}};
        BOOST_CHECK(m.find(0) == m.end());
        
        const_iterator ret = m.find(1);
        BOOST_CHECK(ret != m.end());
        BOOST_CHECK(ret == m.begin());
        BOOST_CHECK(ret->first == 1);
        BOOST_CHECK(ret->second == 1);
        
        BOOST_CHECK(m.find(2) == m.end());
    }
    // non-const find test
    {
        map_type m{{1, 1}};
        BOOST_CHECK(m.find(0) == m.end());
        
        iterator ret = m.find(1);
        BOOST_CHECK(ret != m.end());
        BOOST_CHECK(ret == m.begin());
        BOOST_CHECK(ret->first == 1);
        BOOST_CHECK(ret->second == 1);
        // modify it
        ret->second = 2;
        BOOST_CHECK(ret->second == 2);
        BOOST_CHECK(m.at(1) == 2);
        
        BOOST_CHECK(m.find(2) == m.end());
    }
}

BOOST_AUTO_TEST_CASE(lower_bound_test)
{
    // const test
    {
        const map_type m{{1, 1}};
        const_iterator ret = m.lower_bound(0);
        BOOST_CHECK(ret == m.begin());
        BOOST_CHECK(ret->first == 1);
        
        ret = m.lower_bound(1);
        BOOST_CHECK(ret == m.begin());
        BOOST_CHECK(ret->first == 1);
        
        ret = m.lower_bound(2);
        BOOST_CHECK(ret == m.end());
    }
    // non-const test
    {
        map_type m{{1, 1}};
        iterator ret = m.lower_bound(0);
        BOOST_CHECK(ret == m.begin());
        BOOST_CHECK(ret->first == 1);
        
        ret = m.lower_bound(1);
        BOOST_CHECK(ret == m.begin());
        BOOST_CHECK(ret->first == 1);
        // modify it
        BOOST_CHECK(ret->second == 1);
        ret->second = 2;
        BOOST_CHECK(ret->second == 2);
        BOOST_CHECK(m.at(1) == 2);
        
        ret = m.lower_bound(2);
        BOOST_CHECK(ret == m.end());
    }
}

BOOST_AUTO_TEST_CASE(upper_bound_test)
{
    // const test
    {
        const map_type m{{1, 1}};
        const_iterator ret = m.upper_bound(0);
        BOOST_CHECK(ret == m.begin());
        BOOST_CHECK(ret->first == 1);
        
        ret = m.upper_bound(1);
        BOOST_CHECK(ret == m.end());
        
        ret = m.upper_bound(2);
        BOOST_CHECK(ret == m.end());
    }
    // non-const test
    {
        map_type m{{1, 1}};
        iterator ret = m.upper_bound(0);
        BOOST_CHECK(ret == m.begin());
        BOOST_CHECK(ret->first == 1);
        // modify it
        BOOST_CHECK(ret->second == 1);
        ret->second = 2;
        BOOST_CHECK(ret->second == 2);
        BOOST_CHECK(m.at(1) == 2);
        
        
        ret = m.upper_bound(1);
        BOOST_CHECK(ret == m.end());
        
        ret = m.upper_bound(2);
        BOOST_CHECK(ret == m.end());
    }
} 

BOOST_AUTO_TEST_SUITE_END()