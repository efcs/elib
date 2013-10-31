#ifndef ELIB_CHRONO_TIMER_HPP
#define ELIB_CHRONO_TIMER_HPP

# include <elib/config.hpp>
# include <chrono>


# ifndef ELIB_CLANG

namespace elib
{
  namespace chrono
  {
    
    
    template <typename Clock=std::chrono::system_clock>
    class timer
    {
    public:
      
      static constexpr typename Clock::time_point npos_time_point =
        Clock::time_point::min();
      
      static constexpr typename Clock::duration npos_duration =
        Clock::duration::min();
      
      timer() noexcept = default;
      
      timer(const timer&) = default;
      timer(timer&&) = default;
      
      timer& operator=(const timer&) = default;
      timer& operator=(timer&&) = default;
      
      ~timer() noexcept = default;
      
      // query timer state
      bool started() const noexcept
      { return !m_is_npos(m_start_time); }
      
      bool stopped() const noexcept
      { return !m_is_npos(m_stop_time); }
      
      bool running() const noexcept
      { return started() && !stopped(); }
      
      
      void start()
      {
        m_start_time = Clock::now();
        m_stop_time = npos_time_point;
      }
      
      // stop the timer if running
      void stop()
      {
        if (running())
          m_stop_time = Clock::now();
      }
      
      // reset to default state
      void reset()
      {
        m_start_time = npos_time_point;
        m_stop_time = npos_time_point;
      }
      
      // alias for start
      void restart()
      { start(); }
      
      
      const typename Clock::time_point& start_time() const noexcept
      { return m_start_time; }
      
      const typename Clock::time_point& stop_time() const noexcept
      { return m_stop_time; }
      
      
      
      typename Clock::duration duration() const
      {
        if (! started())
          return Clock::duration::zero();
          
        if (stopped())
          return m_stop_time - m_start_time;
        else
          return Clock::now() - m_start_time;
      }
      
      template <typename Dura>
      Dura duration() const
      { return std::chrono::duration_cast<Dura>(duration()); }
      
      std::chrono::nanoseconds nanoseconds() const
      { return duration<std::chrono::nanoseconds>(); }
      
      std::chrono::microseconds microseconds() const
      { return duration<std::chrono::microseconds>(); }
        
      std::chrono::milliseconds milliseconds() const
      { return duration<std::chrono::milliseconds>(); }
        
      std::chrono::seconds seconds() const
      { return duration<std::chrono::seconds>(); }
        
      std::chrono::minutes minutes() const
      { return duration<std::chrono::minutes>(); }
        
      std::chrono::hours hours() const
      { return duration<std::chrono::hours>(); }
      
      
      //
    private:
      //
      
      static constexpr bool 
      m_is_npos(const typename Clock::time_point& tp) noexcept
      { return (tp == npos_time_point); }
      
      typename Clock::time_point m_start_time{npos_time_point}, 
                                 m_stop_time{npos_time_point};
      
      
    };                                                        // class timer


    template <typename Clock>
    constexpr typename Clock::time_point timer<Clock>::npos_time_point;
    
    template <typename Clock>
    constexpr typename Clock::duration timer<Clock>::npos_duration;
    
  }                                                         // namespace chrono
}                                                           // namespace elib


# endif                                                    // ELIB_CLANG
#endif /* ELIB_CHRONO_TIMER_HPP */