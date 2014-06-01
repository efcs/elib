#ifndef ELIB_AUX_AUTO_RETURN_HPP
#define ELIB_AUX_AUTO_RETURN_HPP
#
# /// A set of macros used to clean up the syntax for functions that use trailing 
# /// return syntax. They are intended for functions that are a single return 
# /// statement. There are versions that also deduce the exception specification
# /// Implementation taken from eric_niebler proto-0x
# /// Workaround for GCC not excepting "this" in noexcept clauses 
# /// (just remove the noexcept clause until GCC gets their shit together)
# include <elib/config.hpp>
# include <elib/aux/declval.hpp>
# 
# if !defined(ELIB_CONFIG_COVERITY_SCAN)
# 
#   define ELIB_AUTO_RETURN_NOEXCEPT(...)                               \
    noexcept(noexcept(                                                  \
        decltype(__VA_ARGS__)(::elib::declval<decltype(__VA_ARGS__)>()) \
    )) -> decltype(__VA_ARGS__)                                         \
    {                                                                   \
        return (__VA_ARGS__);                                           \
    }
#   
#   
#   define ELIB_RETURN_NOEXCEPT(...)                                    \
    noexcept(noexcept(                                                  \
        decltype(__VA_ARGS__)(::elib::declval<decltype(__VA_ARGS__)>()) \
    ))                                                                  \
    {                                                                   \
        return (__VA_ARGS__);                                           \
    }
# 
# 
# else /* ELIB_CONFIG_COVERITY_SCAN */
# 
#   define ELIB_AUTO_RETURN_NOEXCEPT(...) \
    -> decltype(__VA_ARGS__)              \
    {                                     \
        return (__VA_ARGS__);             \
    }
#   
#   
#   define ELIB_RETURN_NOEXCEPT(...) \
    {                                \
        return (__VA_ARGS__);        \
    }
#
# endif /* ELIB_CONFIG_COVERITY_SCAN */
#
# 
# define ELIB_AUTO_RETURN(...) \
    -> decltype(__VA_ARGS__)   \
    {                          \
        return (__VA_ARGS__);  \
    }                          
# 
# /* noexcept workaround for when "this" is used with GCC */
# if ELIB_WORKAROUND(ELIB_CONFIG_GCC, GCC_NOEXCEPT_THIS_BUG)
#
#   define ELIB_AUTO_RETURN_WORKAROUND ELIB_AUTO_RETURN
#   define ELIB_RETURN_WORKAROUND(...) { return (__VA_ARGS__); }
#   
# else /* non-workaround support (same as AUTO_RETURN and RETURN) */
#   
#   define ELIB_AUTO_RETURN_WORKAROUND ELIB_AUTO_RETURN
#   define ELIB_RETURN_WORKAROUND ELIB_RETURN
# endif
# 
#endif /* ELIB_AUX_AUTO_RETURN_HPP */