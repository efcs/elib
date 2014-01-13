#ifndef ELIB_UTILITY_RETURN_MACRO_HPP
#define ELIB_UTILITY_RETURN_MACRO_HPP

# include <utility>
# include <elib/config.hpp>

/* Implementation taken from eric_niebler proto-0x
 * Workaround for GCC not excepting "this" in noexcept clauses 
 * added by me (just remove the noexcept clause until GCC gets there shit together)
 */
# if ! ELIB_WORKAROUND(ELIB_GNU, GCC_NOEXCEPT_THIS_BUG)
#  
#   
#   define ELIB_AUTO_RETURN(...)                                 \
  noexcept(noexcept(                                             \
    decltype(__VA_ARGS__)(std::declval<decltype(__VA_ARGS__)>()) \
  )) -> decltype(__VA_ARGS__)                                    \
  {                                                              \
    return (__VA_ARGS__);                                        \
  }
#   
#   
#   define ELIB_RETURN(...)                                        \
  noexcept(noexcept(                                               \
      decltype(__VA_ARGS__)(std::declval<decltype(__VA_ARGS__)>()) \
  ))                                                               \
  {                                                                \
    return (__VA_ARGS__);                                          \
  }
# 
#   
#   else /* GCC_NOEXCEPT_THIS_BUG */
#   
#   
#   define ELIB_AUTO_RETURN(...) \
  -> decltype(__VA_ARGS__)       \
  {                              \
    return (__VA_ARGS__);        \
  }                             
# 
#   
#   define ELIB_RETURN(...) \
  {                         \
    return (__VA_ARGS__);   \
  }
#   
#   
# endif /* GCC_NOEXCEPT_THIS_BUG */


#endif /* ELIB_UTILITY_RETURN_MACRO_HPP */