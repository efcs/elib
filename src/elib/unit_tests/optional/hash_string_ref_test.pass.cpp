// REQUIRES: ELIB_CORE
#include <elib/optional.hpp>
#include <string>
#include "rapid-cxx-test.hpp"
using opt = elib::optional<std::string &>;


TEST_SUITE(elib_optional_hash_string_ref_test_suite)

TEST_CASE(empty_hash_test)
{
    const opt o;
    std::hash<opt> h{};
    TEST_CHECK(h(o) == std::hash<opt>::result_type{});
}

TEST_CASE(non_empty_hash_test)
{
    std::string s = "hello World!\n";
    opt const o(s);
    std::hash<opt> oh{};
    std::hash<std::string> sh{};
    TEST_CHECK(oh(o) == sh(s));
}

TEST_SUITE_END()