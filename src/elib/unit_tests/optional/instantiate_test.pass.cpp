#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE Main
#include <boost/test/unit_test.hpp>

#include <elib/optional.hpp>
#include <string>

// instantiation tests
namespace elib
{
    template class optional<int>;
    template class optional<std::string>;
    template class optional<int &>;
    template class optional<std::string &>;
}


BOOST_AUTO_TEST_SUITE(elib_optional_instantiate_test_test_suite)

BOOST_AUTO_TEST_CASE(dummy)
{
    BOOST_CHECK(true);
}

BOOST_AUTO_TEST_SUITE_END()