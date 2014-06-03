#ifndef ELIB_PREASSERT_CORE_HPP
#define ELIB_PREASSERT_CORE_HPP

# include <elib/config.hpp>
# include <atomic>
# include <iostream>
# include <string>
# include <cstddef>
# include <cstdlib>

namespace elib { namespace preassert
{
    ////////////////////////////////////////////////////////////////////////////
    enum class mode
    {
        opt, dbg, safe
    };
    
# if defined(__clang__)
#   pragma clang diagnostic push
#   pragma clang diagnostic ignored "-Wcovered-switch-default"
#   pragma clang diagnostic ignored "-Wunreachable-code"
# endif
    ////////////////////////////////////////////////////////////////////////////
    inline std::string to_string(mode m) noexcept
    {
        switch (m)
        {
            case mode::opt:
                return "opt";
            case mode::dbg:
                return "dbg";
            case mode::safe:
                return "safe";
            default:
                std::abort();
        };
    }
# if defined(__clang__)
#   pragma clang diagnostic pop
# endif

    ////////////////////////////////////////////////////////////////////////////
    using violation_handler = 
        void(*)(mode, const char *msg, const char *file, const char* func, std::size_t line);
    
    namespace detail
    {
        ELIB_NORETURN
        inline void default_violation_handler(
            mode m, const char *pred_str
          , const char *file, const char *func, std::size_t line
          )
        {
            std::cerr <<  to_string(m) << file << "::" << line <<  std::endl;      
            std::cerr << " In " << func << ": ( " << pred_str << " ) FAILED" 
               << std::endl;                                          
                                                                      
            std::abort();                                                        
        }
        
        inline std::atomic<violation_handler>* get_violation_handler_impl() noexcept
        {
            static std::atomic<violation_handler> m_handler{default_violation_handler};
            return &m_handler;
        }
    }                                                       // namespace detail
    
    ////////////////////////////////////////////////////////////////////////////
    inline violation_handler get_violation_handler(violation_handler handler) noexcept
    {
        return std::atomic_exchange(detail::get_violation_handler_impl(), handler);
    }
    
    ////////////////////////////////////////////////////////////////////////////
    inline violation_handler get_violation_handler() noexcept
    {
        return std::atomic_load(detail::get_violation_handler_impl());
    }
    
    ////////////////////////////////////////////////////////////////////////////
    ELIB_NORETURN 
    inline void assert_fail(
        mode which, const char *msg
      , const char *file, const char *func, std::size_t line
      )
    {
        violation_handler h = get_violation_handler();
        if (h) {
            try {
                h(which, msg, file, func, line);
            } catch (...) { }
        }
        std::abort();
    }
    
}}                                                          // namespace elib
#endif /* ELIB_PREASSERT_CORE_HPP */