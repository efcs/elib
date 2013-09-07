#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include "elib/log/log.h"
#include "elib/enumeration/enum_traits.h"

using namespace elib;
using namespace elib::enumeration;

BOOST_AUTO_TEST_SUITE(log_test_suite)

BOOST_AUTO_TEST_CASE(log_level_enum_test)
{
    BOOST_CHECK(enum_traits<log::level_e>::verify_enum_traits());
}

BOOST_AUTO_TEST_SUITE_END()