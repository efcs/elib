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

BOOST_AUTO_TEST_CASE(flat_map_base_init)
{
    BOOST_CHECK(true);
}

BOOST_AUTO_TEST_SUITE_END()