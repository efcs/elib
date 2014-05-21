// ELIB_AUX_ASSERT_HPP
// header guard placed later in file

#if defined(ELIB_ASSERT)
#   undef ELIB_ASSERT
#   undef ELIB_WARN
#   undef ELIB_DEBUG
#endif
    
////////////////////////////////////////////////////////////////////////////////
// ELIB_ASSERT
# if !defined(NDEBUG) && !defined(ELIB_ASSERT_OFF)
#   define ELIB_ASSERT(...) ELIB_AUX_ASSERT_MACRO("ELIB_ASSERT: ", __VA_ARGS__)
# else
#   define ELIB_ASSERT(...) ((void)0)
# endif


////////////////////////////////////////////////////////////////////////////////
// ELIB_WARN
# if defined(ELIB_WARN_ON)
#   define ELIB_WARN(...) ELIB_AUX_ASSERT_MACRO_NOEXIT("ELIB_WARN: ", __VA_ARGS__)
# else
#   define ELIB_WARN(...) ((void)0)
# endif


////////////////////////////////////////////////////////////////////////////////
// ELIB_DEBUG
# if defined(ELIB_DEBUG_ON)
#   define ELIB_DEBUG(...) ELIB_AUX_ASSERT_MACRO_NOEXIT("ELIB_DEBUG: ", __VA_ARGS__)
# else
#   define ELIB_DEBUG(...) ((void)0)
# endif

////////////////////////////////////////////////////////////////////////////////
//                          ELIB_AUX_ASSERT_HPP                               //
////////////////////////////////////////////////////////////////////////////////
#ifndef ELIB_AUX_ASSERT_HPP
#define ELIB_AUX_ASSERT_HPP

# include <elib/config.hpp>
# include <elib/preprocessor/overload.hpp>
# include <iostream>
# include <cstdlib>

////////////////////////////////////////////////////////////////////////////////
#define ELIB_ASSERT_ALWAYS(...) \
    ELIB_AUX_ASSERT_MACRO("ELIB_ASSERT_ALWAYS: ", __VA_ARGS__)
#

////////////////////////////////////////////////////////////////////////////////
#define ELIB_WARN_ALWAYS(...) \
    ELIB_AUX_ASSERT_MACRO_NOEXIT("ELIB_WARN_ALWAYS: ", __VA_ARGS__)
#

////////////////////////////////////////////////////////////////////////////////
// ELIB_AUX_ASSERT_MACRO
# define ELIB_AUX_ASSERT_MACRO_IMPL(Fn, Str, ...)              \
    ELIB_PP_OVERLOAD(ELIB_AUX_ASSERT_MACRO_IMPL_, __VA_ARGS__)(Fn, Str, __VA_ARGS__)
    
# define ELIB_AUX_ASSERT_MACRO_IMPL_1(Fn, Str, Pred) \
    ( (Pred) ? ((void)0) : Fn(Str, #Pred, __FILE__, __func__, __LINE__) )
# 
# define ELIB_AUX_ASSERT_MACRO_IMPL_2(Fn, Str, Pred, Msg) \
    ( (Pred) ? ((void)0) : Fn(Str, #Pred, __FILE__, __func__, __LINE__, Msg) )
# 

# define ELIB_AUX_ASSERT_MACRO(Str, ...)                          \
    ELIB_AUX_ASSERT_MACRO_IMPL(::elib::aux::detail::assert_failed \
                             , Str, __VA_ARGS__)
# 

# define ELIB_AUX_ASSERT_MACRO_NOEXIT(Str, ...)                          \
    ELIB_AUX_ASSERT_MACRO_IMPL(::elib::aux::detail::assert_failed_noexit \
                             , Str, __VA_ARGS__)

////////////////////////////////////////////////////////////////////////////////
// ELIB_AUX_ASSERT_FUNCTION
# define ELIB_AUX_ASSERT_FUNCTION(Name, Stream, Abort)                \
    inline void                                                       \
    Name( const char* prompt, const char* pred_str                    \
        , const char* file, const char* func, int line                \
        , const char* opt_str = nullptr)                              \
    {                                                                 \
        Stream <<  prompt << file << "::" << line <<  std::endl;      \
        Stream << " In " << func << ": ( " << pred_str << " ) FAILED" \
               << std::endl;                                          \
                                                                      \
        if (opt_str) Stream << "  " << opt_str << std::endl;          \
        Abort;                                                        \
    }      
# 
  
namespace elib { namespace aux { namespace detail
{   
    ELIB_NORETURN 
    ELIB_AUX_ASSERT_FUNCTION(assert_failed, std::cerr, std::abort()) /* LCOV_EXCL_LINE */ 
    
    ELIB_AUX_ASSERT_FUNCTION(assert_failed_noexit, std::cerr, ((void)0))
    
}}}                                                           // namespace elib

# undef ELIB_AUX_ASSERT_FUNCTION

#endif /* ELIB_AUX_ASSERT_HPP */