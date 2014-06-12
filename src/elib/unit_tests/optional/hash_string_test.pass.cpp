// REQUIRES: ELIB_SOURCE, ELIB_BOOST_TEST
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE Main
#include <boost/test/unit_test.hpp>

#include <elib/optional.hpp>
#include <string>
using opt = elib::optional<std::string>;


BOOST_AUTO_TEST_SUITE(elib_optional_hash_string_test_suite)

BOOST_AUTO_TEST_CASE(empty_hash_test)
{
    const opt o;
    std::hash<opt> h{};
    BOOST_CHECK(h(o) == std::hash<opt>::result_type{});
}

BOOST_AUTO_TEST_CASE(non_empty_hash_test)
{
    std::string const s = "hello World!\n";
    opt const o(s);
    std::hash<opt> oh{};
    std::hash<std::string> sh{};
    BOOST_CHECK(oh(o) == sh(s));
}

BOOST_AUTO_TEST_SUITE_END()