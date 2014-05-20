#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include <elib/aux/none.hpp>

using namespace elib;

BOOST_AUTO_TEST_SUITE(elib_aux_none_test_suite)

BOOST_AUTO_TEST_CASE(is_none_test)
{
    static_assert(
        aux::is_none<aux::none>::value
      , "must be none"
      );
    
    static_assert(
        not aux::is_none<int>::value
      , "must not be none"
      );
    BOOST_CHECK(true);
}

BOOST_AUTO_TEST_SUITE_END()