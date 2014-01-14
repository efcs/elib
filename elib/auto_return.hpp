#ifndef ELIB_AUTO_RETURN_HPP
#define ELIB_AUTO_RETURN_HPP

# include <utility>
# include <elib/config.hpp>

/* Implementation taken from eric_niebler proto-0x
 * Workaround for GCC not excepting "this" in noexcept clauses 
 * added by me (just remove the noexcept clause until GCC gets there shit together)
 */
#   define ELIB_AUTO_RETURN_NOEXCEPT(...)                        \
  noexcept(noexcept(                                             \
    decltype(__VA_ARGS__)(::std::declval<decltype(__VA_ARGS__)>()) \
  )) -> decltype(__VA_ARGS__)                                    \
  {                                                              \
    return (__VA_ARGS__);                                        \
  }
#   
#   
#   define ELIB_RETURN_NOEXCEPT(...)                               \
  noexcept(noexcept(                                               \
      decltype(__VA_ARGS__)(::std::declval<decltype(__VA_ARGS__)>()) \
  ))                                                               \
  {                                                                \
    return (__VA_ARGS__);                                          \
  }
#   
# /* workaround for GCC */
# if ! ELIB_WORKAROUND(ELIB_GNU, GCC_NOEXCEPT_THIS_BUG)
#   
#   define ELIB_AUTO_RETURN(...)                                 \
  noexcept(noexcept(                                             \
    decltype(__VA_ARGS__)(::std::declval<decltype(__VA_ARGS__)>()) \
  )) -> decltype(__VA_ARGS__)                                    \
  {                                                              \
    return (__VA_ARGS__);                                        \
  }
#   
#   
#   define ELIB_RETURN(...)                                        \
  noexcept(noexcept(                                               \
      decltype(__VA_ARGS__)(::std::declval<decltype(__VA_ARGS__)>()) \
  ))                                                               \
  {                                                                \
    return (__VA_ARGS__);                                          \
  }
#   
# else /* gcc bug */
#   
#   define ELIB_AUTO_RETURN(...) \
      -> decltype(__VA_ARGS__)   \
      {                          \
        return (__VA_ARGS__);    \
      }
#   
#   /* this version makes no sense with the workaround */
#   define ELIB_RETURN(...) \
    {                       \
      return (__VA_ARGS__); \
    }
#   
# endif /* workaround for gcc */
# 
#endif /* ELIB_AUTO_RETURN_HPP */
