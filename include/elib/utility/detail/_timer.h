#ifndef ELIB__TIMER_H
#define ELIB__TIMER_H


#ifndef ELIB_TIMER_H
#   error only include this file through timer.h
#endif


namespace elib {
    
    
template <typename Clock, typename Dura>
inline void
timer<Clock, Dura>::reset()
{
    m_start = time_point(ZERO_TIME);
    m_stop = time_point(ZERO_TIME);
}

template <typename Clock, typename Dura>
inline void
timer<Clock, Dura>::start()
{
    m_start = time_point(clock_type::now());
    m_stop = time_point(ZERO_TIME);
}

template <typename Clock, typename Dura>
inline void
timer<Clock, Dura>::stop()
{
    m_stop = time_point(clock_type::now());
}

template <typename Clock, typename Dura>
template <typename Duration>
inline Duration
timer<Clock, Dura>::mark() const
{
    return _duration<Duration>(m_start, clock_type::now());
}

template <typename Clock, typename Dura>
template <typename Duration>
inline typename Duration::rep
timer<Clock, Dura>::mark_count() const
{
    return _duration<Duration>(m_start, clock_type::now()).count();
}

template <typename Clock, typename Dura>
inline constexpr bool
timer<Clock, Dura>::running() const
{
    return (m_start != ZERO_TIME && m_stop == ZERO_TIME);
}

template <typename Clock, typename Dura>
inline constexpr bool
timer<Clock, Dura>::stopped() const
{
    return (m_stop != ZERO_TIME);
}

template <typename Clock, typename Dura>
template <typename Duration>
inline Duration
timer<Clock, Dura>::duration() const
{
    if (! stopped())
        return _duration<Duration>(m_start, clock_type::now());
    else
        return _duration<Duration>(m_start, m_stop);
}

template <typename Clock, typename Dura>
template <typename Duration>
inline typename Duration::rep
timer<Clock, Dura>::count() const
{
    if (! stopped())
        return _duration<Duration>(m_start, clock_type::now()).count();
    else
        return _duration<Duration>(m_start, m_stop).count();
}

template <typename Clock, typename Dura>
template <typename Duration>
inline Duration
timer<Clock, Dura>::_duration(const time_point & start, 
                              const time_point & stop) const
{
    using std::chrono::duration_cast;
    
    if (m_start == ZERO_TIME)
        return duration_cast<Duration>(ZERO_DURA);
    else
        return duration_cast<Duration>(stop - start);
}


} /* namespace elib */
#endif /* ELIB__TIMER_H */
