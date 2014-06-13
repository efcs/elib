// REQUIRES: ELIB_MEMORY_SOURCE
#include <elib/memory/allocator_destructor.hpp>
#include <memory>
#include "test/helper.hpp"

TEST_CASE(memory_allocator_destructor_test)
{
    // for code coverage: memory_allocator_destructor_test
    {
        using Alloc = std::allocator<int>;
        using Dtor = elib::allocator_destructor<Alloc>;
        Alloc a;
        std::unique_ptr<int, Dtor> tmp(a.allocate(1), Dtor(a, 1));
    }
}