#ifndef ELIB_AUX_TRAITS_UNCVPTR_HPP
#define ELIB_AUX_TRAITS_UNCVPTR_HPP

# include <elib/aux/traits/remove_cv.hpp>
# include <elib/aux/traits/remove_pointer.hpp>

namespace elib { namespace aux
{

    ////////////////////////////////////////////////////////////////////////////
    template <class T>
    using uncvptr = remove_cv_t<remove_pointer_t<T>>;
        
    ////////////////////////////////////////////////////////////////////////////
    namespace detail
    {
        template <class T>
        struct uncvptr_all_impl
        {
            using type = T;
        };
            
        template <class T>
        struct uncvptr_all_impl<T *> : uncvptr_all_impl<T>
        {
        };
            
        template <class T>
        struct uncvptr_all_impl<T const> : uncvptr_all_impl<T>
        {
        };
            
        template <class T>
        struct uncvptr_all_impl<T volatile> : uncvptr_all_impl<T>
        {
        };
            
        template <class T>
        struct uncvptr_all_impl<T const volatile> : uncvptr_all_impl<T>
        {
        };
    }                                                       // namespace detail
        
    ////////////////////////////////////////////////////////////////////////////
    template <class T>
    using uncvptr_all = typename detail::uncvptr_all_impl<T>::type;
        
}}                                                          // namespace elib
namespace elib
{
    using aux::uncvptr;
    using aux::uncvptr_all;
}                                                           // namespace elib
#endif /* ELIB_AUX_TRAITS_UNCVPTR_HPP */