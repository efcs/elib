#ifndef ELIB_AUX_GET_SWAP_HPP
#define ELIB_AUX_GET_SWAP_HPP

# include <elib/aux/traits/is_swappable.hpp>
# include <utility>

namespace elib { namespace aux
{
    ////////////////////////////////////////////////////////////////////////////
    template <class T, class U = T>
    using get_swap_t = void(*)(T &, U &);
    
    namespace get_swap_detail
    {
        ////////////////////////////////////////////////////////////////////////
        template <
            class T, class U
          , ELIB_ENABLE_IF(is_swappable<T, U>::value)
          >
        get_swap_t<T, U> 
        get_swap_impl(int) noexcept
        {
            using std::swap;
            static auto get_fn = 
            [](T & lhs, U & rhs) { swap(lhs, rhs); };
            
            return get_fn;
        }
        
        template <class T, class U>
        get_swap_t<T, U> 
        get_swap_impl(long) noexcept
        {
            return nullptr;
        }
        
        ////////////////////////////////////////////////////////////////////////
        template <
            class T, class U
          , ELIB_ENABLE_IF( is_noexcept_swappable<T, U>::value )
          >
        get_swap_t<T, U>
        get_noexcept_swap_impl(int) noexcept
        {
            using std::swap;
            static auto get_fn = 
            [](T & lhs, U & rhs) { swap(lhs, rhs); };
            
            return get_fn;
        }
        
        template <class T, class U>
        get_swap_t<T, U>
        get_noexcept_swap_impl(long)
        {
            return nullptr;
        }
    }                                              // namespace get_swap_detail
    
    ////////////////////////////////////////////////////////////////////////////
    template <
        class T, class U = T
      , ELIB_ENABLE_IF(is_swappable<T, U>::value)
      >
    get_swap_t<T, U> 
    get_swap() noexcept
    {
        return get_swap_detail::get_swap_impl<T, U>(0);
    }
    
    ////////////////////////////////////////////////////////////////////////////
    template <
        class T, class U = T
      , ELIB_ENABLE_IF(is_noexcept_swappable<T, U>::value)
      >
    get_swap_t<T, U> 
    get_noexcept_swap() noexcept
    {
        return get_swap_detail::get_noexcept_swap_impl<T, U>(0);
    }
    
    ////////////////////////////////////////////////////////////////////////////
    template <class T, class U = T>
    get_swap_t<T, U> 
    get_swap_ptr() noexcept
    {
        return get_swap_detail::get_swap_impl<T, U>(0);
    }
    
    ////////////////////////////////////////////////////////////////////////////
    template <class T, class U = T>
    get_swap_t<T, U> 
    get_noexcept_swap_ptr() noexcept
    {
        return get_swap_detail::get_noexcept_swap_impl<T, U>(0);
    }
    
}}                                                          // namespace elib
namespace elib
{
    using aux::get_swap_t;
    using aux::get_swap;
    using aux::get_noexcept_swap;
    using aux::get_swap_ptr;
    using aux::get_noexcept_swap_ptr;
}                                                           // namespace elib
#endif /* ELIB_AUX_GET_SWAP_HPP */