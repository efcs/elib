#ifndef ELIB_AUTO_RETURN_HPP
#define ELIB_AUTO_RETURN_HPP

# include <utility>
# include <elib/config.hpp>

/* Implementation taken from eric_niebler proto-0x
 * Workaround for GCC not excepting "this" in noexcept clauses 
 * added by me (just remove the noexcept clause until GCC gets there shit together)
 */
   
# define ELIB_AUTO_RETURN(...)                                     \
  noexcept(noexcept(                                               \
    decltype(__VA_ARGS__)(::std::declval<decltype(__VA_ARGS__)>()) \
  )) -> decltype(__VA_ARGS__)                                      \
  {                                                                \
    return (__VA_ARGS__);                                          \
  }
#   
#   
# define ELIB_RETURN(...)                                            \
  noexcept(noexcept(                                                 \
      decltype(__VA_ARGS__)(::std::declval<decltype(__VA_ARGS__)>()) \
  ))                                                                 \
  {                                                                  \
    return (__VA_ARGS__);                                            \
  }
# 
# /* noexcept workaround for when "this" is used with GCC */
# if ELIB_WORKAROUND(ELIB_GNU, GCC_NOEXCEPT_THIS_BUG)
#   
#   define ELIB_AUTO_RETURN_WORKAROUND(...) \
  -> decltype(__VA_ARGS__)                  \
  {                                         \
    return (__VA_ARGS__);                   \
  }
#   
#   define ELIB_RETURN_WORKAROUND(...) \
  {                                    \
    return (__VA_ARGS__);              \
  }
#   
# else /* non-workaround support (same as AUTO_RETURN and RETURN) */
#   
#   define ELIB_AUTO_RETURN_WORKAROUND ELIB_AUTO_RETURN
#   define ELIB_RETURN_WORKAROUND ELIB_RETURN
#   
# endif
# 
#endif /* ELIB_AUTO_RETURN_HPP */
