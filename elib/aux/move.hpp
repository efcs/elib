#ifndef ELIB_AUX_MOVE_HPP
#define ELIB_AUX_MOVE_HPP

# include <elib/config.hpp>
# include <elib/aux/type_traits.hpp>
# include <type_traits>
# include <utility>

// noexcept copy clause
# define ELIB_NOEXCEPT(...)                                            \
    noexcept(noexcept(                                                 \
        decltype(__VA_ARGS__)(::std::declval<decltype(__VA_ARGS__)>()) \
    ))
# 
# 
# // Implementation taken from eric_niebler proto-0x
# // Workaround for GCC not excepting "this" in noexcept clauses 
# // (just remove the noexcept clause until GCC gets their shit together)
# define ELIB_AUTO_RETURN_NOEXCEPT(...)                            \
  noexcept(noexcept(                                               \
    decltype(__VA_ARGS__)(::std::declval<decltype(__VA_ARGS__)>()) \
  )) -> decltype(__VA_ARGS__)                                      \
  {                                                                \
    return (__VA_ARGS__);                                          \
  }
#   
#   
# define ELIB_RETURN_NOEXCEPT(...)                                   \
  noexcept(noexcept(                                                 \
      decltype(__VA_ARGS__)(::std::declval<decltype(__VA_ARGS__)>()) \
  ))                                                                 \
  {                                                                  \
    return (__VA_ARGS__);                                            \
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
# if ELIB_WORKAROUND(ELIB_CONFIG_GNU, GCC_NOEXCEPT_THIS_BUG)
#   
#   define ELIB_AUTO_RETURN_WORKAROUND ELIB_AUTO_RETURN
#   define ELIB_RETURN_WORKAROUND(...) { return (__VA_ARGS__); }
#   
# else /* non-workaround support (same as AUTO_RETURN and RETURN) */
#   
#   define ELIB_AUTO_RETURN_WORKAROUND ELIB_AUTO_RETURN
#   define ELIB_RETURN_WORKAROUND ELIB_RETURN
#   
# endif

namespace elib 
{
    namespace aux
    {
        ////////////////////////////////////////////////////////////////////////
        // forward
        template <class T>
        constexpr T&& forward(remove_ref<T>& t) noexcept
        { 
            return static_cast<T&&>(t);
        }

        template <class T>
        constexpr T&& forward(remove_ref<T>&& t) noexcept
        {
            return static_cast<T &&>(t);
        }
        
        ////////////////////////////////////////////////////////////////////////
        // move
        template <class T>
        constexpr remove_ref<T> && move(T&& t) noexcept
        {
            return static_cast<remove_ref<T> &&>(t);
        }
        
        ////////////////////////////////////////////////////////////////////////
        // move_if_noexcept
        template <class T> constexpr 
        conditional<
            !std::is_nothrow_move_constructible<T>::value 
            && std::is_copy_constructible<T>::value
          , const T&
          , T&&
        >
        move_if_noexcept(T& x) noexcept
        {
            return aux::move(x);
        }
        
        ////////////////////////////////////////////////////////////////////////
        // declval
        template <class T>
        add_rvalue_ref<T> declval();
    }                                                       // namespace aux
}                                                           // namespace elib
#endif /* ELIB_AUX_MOVE_HPP */