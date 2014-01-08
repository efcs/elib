#ifndef ELIB_LOG_LOG_HPP
#define ELIB_LOG_LOG_HPP

#include <elib/log/basic_log.hpp>
#include <elib/log/log_level.hpp>

#include <iostream>


namespace elib 
{
  namespace log 
  {
    

    namespace detail { class log_impl; }
        
        
    /* Actual logging class, implements the basic_log iterface */
    class log : public basic_log {
    public:
        log();
        explicit log(level_e level);
        
    protected:
        std::ostream & 
        _get_stream(level_e level);
        
    private:
        std::ostream &m_out, &m_err;
    };
 

  }                                                         // namespace log
}                                                           // namespace elib
#endif /* ELIB_LOG_LOG_HPP */