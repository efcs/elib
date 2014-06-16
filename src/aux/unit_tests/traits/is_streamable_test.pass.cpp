// REQUIRES: ELIB_AUX_SOURCE
#include <elib/aux/traits/is_input_streamable.hpp>
#include <elib/aux/traits/is_output_streamable.hpp>
#include <elib/aux/traits/is_streamable.hpp>
#include <ios>
#include "rapid-cxx-test.hpp"

using namespace elib::aux;

struct in_type {};
struct out_type {};
struct in_out_type {};
struct no_stream_type {};

std::istream & operator>>(std::istream & s, in_type &) { return s; }
std::ostream & operator<<(std::ostream & s, out_type &) { return s; }
std::istream & operator>>(std::istream & s, in_out_type &) { return s; }
std::ostream & operator<<(std::ostream & s, in_out_type &) { return s; }


TEST_SUITE(elib_aux_traits_is_streamable_test_suite)

TEST_CASE(is_input_streamable_test)
{
    TEST_STATIC_ASSERT(is_input_streamable<in_type>::value);
    TEST_STATIC_ASSERT(not is_input_streamable<out_type>::value);
    TEST_STATIC_ASSERT(is_input_streamable<in_out_type>::value);
    TEST_STATIC_ASSERT(not is_input_streamable<no_stream_type>::value);
    TEST_STATIC_ASSERT(not is_input_streamable<void>::value);
}

TEST_CASE(is_output_streamable_test)
{
    TEST_STATIC_ASSERT(not is_output_streamable<in_type>::value);
    TEST_STATIC_ASSERT(is_output_streamable<out_type>::value);
    TEST_STATIC_ASSERT(is_output_streamable<in_out_type>::value);
    TEST_STATIC_ASSERT(not is_output_streamable<no_stream_type>::value);
    TEST_STATIC_ASSERT(not is_output_streamable<void>::value);
}

TEST_CASE(is_streamable_test)
{
    TEST_STATIC_ASSERT(not is_streamable<in_type>::value);
    TEST_STATIC_ASSERT(not is_streamable<out_type>::value);
    TEST_STATIC_ASSERT(is_streamable<in_out_type>::value);
    TEST_STATIC_ASSERT(not is_streamable<no_stream_type>::value);
    TEST_STATIC_ASSERT(not is_streamable<void>::value);
}

TEST_SUITE_END()