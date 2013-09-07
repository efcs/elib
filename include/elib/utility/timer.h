#ifndef ELIB_TIMER_H
#define ELIB_TIMER_H


#include <elib/utility/time.h>


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
    
    constexpr bool 
    running() const;
    
    constexpr bool
    stopped() const;
    
    template <typename Duration=duration_type>
    Duration
    duration() const;
    
    template <typename Duration=duration_type>
    typename Duration::rep
    count() const;
    
private:
    typedef typename clock_type::time_point time_point;
    
    static constexpr duration_type 
    ZERO_DURA = duration_type::zero();
    
    static constexpr time_point 
    ZERO_TIME = time_point(ZERO_DURA);
    
    template <typename Duration=duration_type>
    Duration
    _duration(const time_point & start, const time_point & stop) const;
    
    time_point m_start{}, m_stop{};
};



typedef timer<default_clock, nanoseconds> nanoseconds_timer;
typedef timer<default_clock, microseconds> microseconds_timer;
typedef timer<default_clock, milliseconds> milliseconds_timer;
typedef timer<default_clock, seconds> seconds_timer;
typedef timer<default_clock, minutes> minutes_timer;
typedef timer<default_clock, hours> hours_timer;


    
} /* namespace elib */


#include <elib/utility/detail/_timer.h>


#endif /* ELIB_TIMER_H */