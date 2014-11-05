// REQUIRES: ELIB_AUX
#include <elib/aux/literals.hpp>
#include <string>
#include "rapid-cxx-test.hpp"

using namespace elib;
using namespace elib::aux;

TEST_SUITE(elib_aux_literals_test_suite)

#if !defined(ELIB_CONFIG_COVERITY_SCAN)

TEST_CASE(binary_literal_test)
{
    TEST_STATIC_ASSERT(0_bin == 0);
    TEST_STATIC_ASSERT(00_bin == 0);
    TEST_STATIC_ASSERT(000_bin == 0);
    
    TEST_STATIC_ASSERT(1_bin == 1);
    TEST_STATIC_ASSERT(01_bin == 1);
    TEST_STATIC_ASSERT(001_bin == 1);
    
    TEST_STATIC_ASSERT(10_bin == 2);
    TEST_STATIC_ASSERT(010_bin == 2);
    
    TEST_STATIC_ASSERT(11_bin == 3);
    TEST_STATIC_ASSERT(011_bin == 3);
    
    TEST_STATIC_ASSERT(100_bin == 4);
    TEST_STATIC_ASSERT(101_bin == 5);
    TEST_STATIC_ASSERT(111_bin == 7);
    
    TEST_CHECK(true);
}

TEST_CASE(string_to_string_literal_test)
{
    TEST_CHECK(""_str == "");
    TEST_CHECK(" "_str == " ");
    TEST_CHECK("Hello World!\n"_str == "Hello World!\n");
}

TEST_CASE(number_to_string_literal_test)
{
    TEST_CHECK(0_str == "0");
    TEST_CHECK(123467890_str == "123467890");
    
    TEST_CHECK(0.0_str == "0.0");
    TEST_CHECK(123.456_str == "123.456");
}

# else /* ELIB_CONFIG_COVERITY_SCAN */
TEST_CASE(literals_test)
{
    TEST_UNSUPPORTED();
}
#endif /* ELIB_CONFIG_COVERITY_SCAN */
TEST_SUITE_END()

