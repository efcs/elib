#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include <elib/container/flat_map.hpp>
#include <string>
#include <map>

// instantiation test
namespace elib { namespace container 
{
    template class flat_map<int, int>;
    template class flat_map<std::string, std::string>;
}}  

BOOST_AUTO_TEST_SUITE(flat_map_test_suite)

BOOST_AUTO_TEST_CASE(flat_map_init)
{
    BOOST_CHECK(true);
}

BOOST_AUTO_TEST_SUITE_END()