#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include "elib/timer.h"
#include "elib/elog.h"
#include "elib/lexical_cast.h"

#include <chrono>
#include <thread>

namespace chrono = std::chrono;


using namespace elib;


BOOST_AUTO_TEST_SUITE(timer_test_suite)


BOOST_AUTO_TEST_CASE(test_milliseconds)
{
    using timer_t = milliseconds_timer;
    auto dura = milliseconds(3);
    
    timer_t t;
    t.start();
    
    BOOST_CHECK(t.running());
    BOOST_CHECK(t.stopped() == false);
    
    std::this_thread::sleep_for(dura);
    
    t.stop();
    
    BOOST_CHECK(t.running() == false);
    BOOST_CHECK(t.stopped());
    
    elog::raw_out("%lu", t.count());
}


BOOST_AUTO_TEST_SUITE_END()