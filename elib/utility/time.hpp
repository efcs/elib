#ifndef ELIB_TIME_HPP
#define ELIB_TIME_HPP


#include <chrono>


namespace elib {
    
    
using std::chrono::system_clock;
using std::chrono::steady_clock;
using std::chrono::high_resolution_clock;

using std::chrono::nanoseconds;
using std::chrono::microseconds;
using std::chrono::milliseconds;
using std::chrono::seconds;
using std::chrono::minutes;
using std::chrono::hours;


typedef system_clock default_clock;

    
} /* namespace elib */
#endif /* ELIB_TIME_HPP */
