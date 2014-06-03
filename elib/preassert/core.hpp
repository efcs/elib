#ifndef ELIB_PREASSERT_CORE_HPP
#define ELIB_PREASSERT_CORE_HPP

# include <elib/config.hpp>
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
    
    
    ////////////////////////////////////////////////////////////////////////////
    violation_handler get_violation_handler(violation_handler handler) noexcept;
    violation_handler get_violation_handler() noexcept;
    
    ////////////////////////////////////////////////////////////////////////////
    ELIB_NORETURN void assert_fail(
        mode which, const char *msg
      , const char *file, const char *func, std::size_t line
      );
    
}}                                                          // namespace elib
#endif /* ELIB_PREASSERT_CORE_HPP */