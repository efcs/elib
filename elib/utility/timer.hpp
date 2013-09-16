#ifndef ELIB_TIMER_HPP
#define ELIB_TIMER_HPP


#include <elib/utility/time.hpp>


namespace elib {
    
    
template <typename Clock=default_clock, typename Dura=seconds>
class timer {
public:
    typedef Clock clock_type;
    typedef Dura duration_type;
    
    timer() = default;
    ~timer() = default;
    
    void
    reset();
    
    void 
    start();
    
    void 
    stop();
    
    template <typename Duration=duration_type>
    Duration
    mark() const;
    
    template <typename Duration=duration_type>
    typename Duration::rep
    mark_count() const;
    
    bool 
    running() const;
    
    bool
    stopped() const;
    
    template <typename Duration=duration_type>
    Duration
    duration() const;
    
    template <typename Duration=duration_type>
    typename Duration::rep
    count() const;
    
private:
    typedef typename clock_type::time_point time_point;
    
    static duration_type 
    ZERO_DURA;
    
    static time_point 
    ZERO_TIME;
    
    template <typename Duration=duration_type>
    Duration
    _duration(const time_point & start, const time_point & stop) const;
    
    time_point m_start{}, m_stop{};
};


template <typename Clock, typename Dura>
typename timer<Clock, Dura>::duration_type
timer<Clock, Dura>::ZERO_DURA = duration_type::zero();


template <typename Clock, typename Dura>
typename timer<Clock, Dura>::time_point
timer<Clock, Dura>::ZERO_TIME  = time_point(ZERO_DURA);


typedef timer<default_clock, nanoseconds> nanoseconds_timer;
typedef timer<default_clock, microseconds> microseconds_timer;
typedef timer<default_clock, milliseconds> milliseconds_timer;
typedef timer<default_clock, seconds> seconds_timer;
typedef timer<default_clock, minutes> minutes_timer;
typedef timer<default_clock, hours> hours_timer;


    
} /* namespace elib */


#include <elib/utility/detail/_timer.hpp>


#endif /* ELIB_TIMER_HPP */