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

BOOST_AUTO_TEST_SUITE(flat_map_base_test_suite)

BOOST_AUTO_TEST_CASE(flat_map_base_init)
{
    BOOST_CHECK(true);
}

BOOST_AUTO_TEST_SUITE_END()