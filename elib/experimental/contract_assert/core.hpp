#ifndef ELIB_CONTRACT_ASSERT_CORE_HPP
#define ELIB_CONTRACT_ASSERT_CORE_HPP

# include <elib/config.hpp>
# include <elib/assert.hpp>
# include <atomic>
# include <exception> /* for std::terminate */
# include <iostream>
# include <string>
# include <cstddef>
# include <cstdlib>

namespace elib { namespace contract_assert
{
    ////////////////////////////////////////////////////////////////////////////
    enum class contract_assert_mode
    {
        opt, dbg, safe
    };
    
# if defined(__clang__)
#   pragma clang diagnostic push
#   pragma clang diagnostic ignored "-Wcovered-switch-default"
#   pragma clang diagnostic ignored "-Wunreachable-code"
# endif
    ////////////////////////////////////////////////////////////////////////////
    inline std::string to_string(contract_assert_mode m) noexcept
    {
        switch (m)
        {
            case contract_assert_mode::opt:
                return "opt";
            case contract_assert_mode::dbg:
                return "dbg";
            case contract_assert_mode::safe:
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
        void(*)(contract_assert_mode, const char *msg, const char *file, const char* func, std::size_t line);
    
    namespace detail
    {
# if defined(__GNUC__) && !defined(__clang__)
#   pragma GCC diagnostic push
#   pragma GCC diagnostic ignored "-Wswitch-default"
#endif
        ELIB_NORETURN
        inline void default_violation_handler(
            contract_assert_mode m, const char *pred_str
          , const char *file, const char *func, std::size_t line
          )
        {
            const char *assert_name{nullptr};
            switch (m)
            {
                case contract_assert_mode::dbg:
                    assert_name = "ELIB_PRE_ASSERT";
                    break;
                case contract_assert_mode::safe:
                    assert_name = "ELIB_CONTRACT_ASSERT_SAFE";
                    break;
                case contract_assert_mode::opt:
                    assert_name = "ELIB_CONTRACT_ASSERT_OPT";
                    break;
            }; ELIB_ASSERT(assert_name);
            
            std::cerr <<  assert_name << "::" << file << "::" << line <<  std::endl;      
            std::cerr << " In " << func << ": ( " << pred_str << " ) FAILED" 
               << std::endl;                                          
                                                                      
            std::abort();                                                        
        }
# if defined(__GNUC__) && !defined(__clang__)
#   pragma GCC diagnostic pop
# endif

        
        inline std::atomic<violation_handler>* get_violation_handler_impl() noexcept
        {
            static std::atomic<violation_handler> m_handler{
                default_violation_handler
            };
            return &m_handler;
        }
    }                                                       // namespace detail
    
    ////////////////////////////////////////////////////////////////////////////
    inline violation_handler get_violation_handler(violation_handler handler) noexcept
    {
        violation_handler to_swap = handler ? handler : detail::default_violation_handler;
        return std::atomic_exchange(detail::get_violation_handler_impl(), to_swap);
    }
    
    ////////////////////////////////////////////////////////////////////////////
    inline violation_handler get_violation_handler() noexcept
    {
        return std::atomic_load(detail::get_violation_handler_impl());
    }
    
    ////////////////////////////////////////////////////////////////////////////
    ELIB_NORETURN 
    inline void assert_fail(
        contract_assert_mode which, const char *msg
      , const char *file, const char *func, std::size_t line
      )
    {
        violation_handler h = get_violation_handler();
        h(which, msg, file, func, line);
        // If h does return we have to enforce the noreturn attribute.
        std::terminate();
    }
    
}}                                                          // namespace elib
#endif /* ELIB_CONTRACT_ASSERT_CORE_HPP */