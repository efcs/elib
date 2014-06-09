#define BOOST_TEST_MODULE Main
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include <elib/memory/allocator_destructor.hpp>
#include <memory>

BOOST_AUTO_TEST_SUITE(memory_allocator_destructor_test_suite)

// for code coverage
BOOST_AUTO_TEST_CASE(memory_allocator_destructor_test)
{
    using Alloc = std::allocator<int>;
    using Dtor = elib::allocator_destructor<Alloc>;
    Alloc a;
    std::unique_ptr<int, Dtor> tmp(a.allocate(1), Dtor(a, 1));
    BOOST_CHECK(true);
}

BOOST_AUTO_TEST_SUITE_END()