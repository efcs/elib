// REQUIRES: ELIB_CORE
#include <elib/optional.hpp>
#include <string>
#include "rapid-cxx-test.hpp"

// instantiation tests
namespace elib
{
    template class optional<int>;
    template class optional<std::string>;
    template class optional<int &>;
    template class optional<std::string &>;
}


TEST_SUITE(elib_optional_instantiate_test_test_suite)

TEST_CASE(dummy)
{
    TEST_CHECK(true);
}

TEST_SUITE_END()