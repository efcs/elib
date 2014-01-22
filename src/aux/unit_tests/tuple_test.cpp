#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include "elib/aux.hpp"
#include <tuple>
#include <string>

using namespace elib;



BOOST_AUTO_TEST_SUITE(aux_tuple_test_suite)

BOOST_AUTO_TEST_CASE(aux_tuple_init)
{
    aux::tuple<std::string, long, char, long, long> t{aux::move(std::string{"Hello"}), 3, 1};
    std::string & s = aux::get<0>(t);
    BOOST_CHECK( s == "Hello" );
    //((void) aux::get<std::string>(t));
    //BOOST_CHECK( (void*)&s2 == (void*)&aux::get<3>(t) );

}

BOOST_AUTO_TEST_SUITE_END()