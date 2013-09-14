#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include "elib/lock/semaphore.hpp"
#include "elib/lock/detail/semaphore_impl.hpp"

#include <thread>
#include <functional>
#include <vector>
#include <array>
#include <chrono>
#include <iostream>
#include <atomic>

#undef NDEBUG
#include <cassert>

using namespace elib::lock;
    
std::atomic_uint taken{ATOMIC_VAR_INIT(0)};

void take_thread(semaphore & sem)
{
    while (sem.try_lock()) {
        taken.fetch_add(1);
        std::this_thread::yield();
    }
}

template <unsigned N>
void take_thread_test(unsigned sem_size)
{
    taken.store(0);
    std::array<std::thread, N> threads;
    
    semaphore sem(sem_size);
    auto sem_ref = std::ref(sem);
    
   for (auto & t : threads)
       t = std::thread(take_thread, sem_ref);
    
    for (auto & t : threads)
        t.join();
    
    BOOST_CHECK(taken == sem_size);
    BOOST_CHECK(sem.count() == 0);
    BOOST_CHECK(sem.try_lock() == false);
}

BOOST_AUTO_TEST_SUITE(semaphore_test)

BOOST_AUTO_TEST_CASE(basic_semaphore_tests)
{
    semaphore sem(10);
    BOOST_CHECK(sem.count() == 10);
    BOOST_CHECK(sem.max() == 10);
    
    sem.lock();
    BOOST_CHECK(sem.count() == 9);
    BOOST_CHECK(sem.max() == 10);
    
    BOOST_CHECK(sem.try_lock());
    BOOST_CHECK(sem.count() == 8);
    
    sem.unlock();
    BOOST_CHECK(sem.count() == 9);
    
    sem.unlock();
    
    for (int i=0; i < 10; ++i) {
        BOOST_CHECK(sem.try_lock());
    }
    BOOST_CHECK(sem.count() == 0);
    BOOST_CHECK(sem.try_lock() == false);
    BOOST_CHECK(sem.count() == 0);
    
    for (int i=0; i < 10; ++i) {
        sem.unlock();
    }
    
    BOOST_CHECK(sem.count() == 10);
}

BOOST_AUTO_TEST_CASE(basic_thread_test)
{
    take_thread_test<10>(5000);
    take_thread_test<100>(50);
}


BOOST_AUTO_TEST_SUITE_END()
