#ifndef ELIB_LOGGING_LOG_HPP
#define ELIB_LOGGING_LOG_HPP

# include <elib/logging/basic_log.hpp>
# include <elib/logging/log_level.hpp>
# include <iostream>

namespace elib { namespace logging { inline namespace v1
{
# if defined(__clang__)
#   pragma clang diagnostic push
#   pragma clang diagnostic ignored "-Wweak-vtables"
# endif
    ////////////////////////////////////////////////////////////////////////////
    class log : public basic_log {
    public:
        log() = default;
        
        explicit log(level_e lv)
          : basic_log(lv)
        {}
        
    protected:
        std::ostream & m_get_stream(level_e lv)
        {
            return ((lv <= level_e::step || lv == level_e::raw_out) 
              ? std::cout 
              : std::cerr);
        }
    };
# if defined(__clang__)
#   pragma clang diagnostic pop
# endif
 
}}}                                                         // namespace elib
#endif /* ELIB_LOGGING_LOG_HPP */