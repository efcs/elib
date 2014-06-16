// REQUIRES: ELIB_MEMORY_SOURCE
#include <elib/memory/allocator_destructor.hpp>
#include <memory>

#include "rapid-cxx-test.hpp"

TEST_SUITE(memory_allocator_destructor_test_suite)

// for code coverage
TEST_CASE(memory_allocator_destructor_test)
{
    using Alloc = std::allocator<int>;
    using Dtor = elib::allocator_destructor<Alloc>;
    Alloc a;
    std::unique_ptr<int, Dtor> tmp(a.allocate(1), Dtor(a, 1));
}

TEST_SUITE_END()