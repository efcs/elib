// REQUIRES: ELIB_MEMORY_SOURCE
#include <elib/memory/make_unique.hpp>
#include <memory>
#include <string>

#include "test/helper.hpp"

TEST_CASE(elib_memory_make_unique_test_suite)
{
    {
        // make_unique_single_object
        std::unique_ptr<std::string> u = elib::make_unique<std::string>("Hello");
        TEST_ASSERT(bool(u));
        TEST_ASSERT(*u == "Hello");
    }{
        // make_unique_default_init_single_object
        std::unique_ptr<std::string> u = elib::make_unique_default_init<std::string>();
        TEST_ASSERT(bool(u));
        TEST_ASSERT(*u == "");
    }{
        // make_unique_array
        std::unique_ptr<int[]> u = elib::make_unique<int[]>(3);
        TEST_ASSERT(bool(u));
        TEST_ASSERT(u[0] == 0);
        TEST_ASSERT(u[1] == 0);
        TEST_ASSERT(u[2] == 0);
    }{
        // make_unique_default_init_array
        std::unique_ptr<std::string[]> u = 
            elib::make_unique_default_init<std::string[]>(3);
            
        TEST_ASSERT(bool(u));
        TEST_ASSERT(u[0] == "");
        TEST_ASSERT(u[1] == "");
        TEST_ASSERT(u[2] == "");
    }{
        // make_unique_value_init_array
        std::unique_ptr<int[]> u =
            elib::make_unique_value_init<int[]>(3, 0, 1, 2);
            
        TEST_ASSERT(bool(u));
        TEST_ASSERT(u[0] == 0);
        TEST_ASSERT(u[1] == 1);
        TEST_ASSERT(u[2] == 2);
    }{
        // make_unique_auto_size_array
        std::unique_ptr<int[]> u = 
            elib::make_unique_auto_size<int[]>(0, 1, 2);
            
        TEST_ASSERT(bool(u));
        TEST_ASSERT(u[0] == 0);
        TEST_ASSERT(u[1] == 1);
        TEST_ASSERT(u[2] == 2);
    }
}