#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include "elib/aux.hpp"
#include <tuple>
#include <string>

using namespace elib;

BOOST_AUTO_TEST_SUITE(aux_tuple_test_suite)

BOOST_AUTO_TEST_CASE(aux_tuple_init)
{
    aux::tuple<std::string, int, char> t{aux::move(std::string{"Hello"}), 3, 1};
    std::string & s = aux::get<0>(t);
    BOOST_CHECK( s == "Hello" );
    std::string & s2 = aux::get<std::string>(t);
    
    std::tuple<int> t1;
    ((void)t1);
    ((void)t);
}

BOOST_AUTO_TEST_SUITE_END()