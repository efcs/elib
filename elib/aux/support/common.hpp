#ifndef ELIB_AUX_SUPPORT_COMMON_HPP
#define ELIB_AUX_SUPPORT_COMMON_HPP
# 
# include <elib/config.hpp>
# include <elib/aux/support/declval.hpp>
# 
# 
# define ELIB_DEFAULT_CLASS(Class)          \
  Class() = default;                        \
                                            \
  Class(const Class&) = default;            \
  Class(Class&&) = default;                 \
                                            \
  Class& operator=(const Class&) = default; \
  Class& operator=(Class&&) = default
# 

# define ELIB_DEFAULT_COPY(Class)   \
    Class(Class const &) = default; \
    Class & operator=(Class const &) = default
# 

# define ELIB_DEFAULT_MOVE(Class) \
    Class(Class &&) = default;    \
    Class & operator=(Class &&) = default
# 
    
# define ELIB_DEFAULT_COPY_MOVE(Class) \
    ELIB_DEFAULT_COPY(Class);          \
    ELIB_DEFAULT_MOVE(Class)
# 
    
# define ELIB_DELETE_COPY(Class)   \
    Class(Class const &) = delete; \
    Class & operator=(Class const &) = delete
# 
    
# define ELIB_DELETE_MOVE(Class) \
    Class(Class &&) = delete;    \
    Class & operator=(Class &&) = delete
# 
    
# define ELIB_DELETE_COPY_MOVE(Class) \
    ELIB_DELETE_COPY(Class);          \
    ELIB_DELETE_MOVE(Class)
# 
# 
# // Implementation taken from eric_niebler proto-0x
# // Workaround for GCC not excepting "this" in noexcept clauses 
# // (just remove the noexcept clause until GCC gets their shit together)
# define ELIB_AUTO_RETURN_NOEXCEPT(...)                             \
  noexcept(noexcept(                                                \
    decltype(__VA_ARGS__)(::elib::declval<decltype(__VA_ARGS__)>()) \
  )) -> decltype(__VA_ARGS__)                                       \
  {                                                                 \
    return (__VA_ARGS__);                                           \
  }
#   
#   
# define ELIB_RETURN_NOEXCEPT(...)                                    \
  noexcept(noexcept(                                                  \
      decltype(__VA_ARGS__)(::elib::declval<decltype(__VA_ARGS__)>()) \
  ))                                                                  \
  {                                                                   \
    return (__VA_ARGS__);                                             \
  }
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
# 
# define ELIB_UNUSED(x) ((void)x)
# 
# //////////////////////////////////////////////////////////////////////////////
# /* used to clearly have exposition for code we don't want to compile */
# define ELIB_EXPO(...) 
# 
# 
# // noexcept copy clause 
# define ELIB_NOEXCEPT(...)                                             \
    noexcept((                                                          \
        decltype(__VA_ARGS__)(::elib::declval<decltype(__VA_ARGS__)>()) \
    ))
# 
# 
# if __cplusplus <= 201303L
#   define ELIB_CXX14_CONSTEXPR inline
# else
#   define ELIB_CXX14_CONSTEXPR constexpr
# endif
# 
#endif /* ELIB_AUX_SUPPORT_COMMON_HPP */