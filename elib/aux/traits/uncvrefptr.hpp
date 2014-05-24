#ifndef ELIB_AUX_TRAITS_UNCVREFPTR_HPP
#define ELIB_AUX_TRAITS_UNCVREFPTR_HPP

# include <elib/aux/traits/remove_cv.hpp>

namespace elib { namespace aux
{
    namespace detail
    {
        template <class T>
        struct uncvrefptr_impl
        {
            using type = T;
        };
            
        template <class T>
        struct uncvrefptr_impl<T *>
        {
            using type = remove_cv_t<T>;
        };
            
        template <class T>
        struct uncvrefptr_impl<T &>
        {
            using type = remove_cv_t<T>;
        };
            
        template <class T>
        struct uncvrefptr_impl<T &&>
        {
            using type = remove_cv_t<T>;
        };
            
        template <class T>
        struct uncvrefptr_impl<T const> : uncvrefptr_impl<T>
        {
        };
            
        template <class T>
        struct uncvrefptr_impl<T volatile> : uncvrefptr_impl<T>
        {
        };
            
        template <class T>
        struct uncvrefptr_impl<T const volatile> : uncvrefptr_impl<T>
        {
        };
    }                                                       // namespace detail
        
    template <class T>
    using uncvrefptr = typename detail::uncvrefptr_impl<T>::type;
        
    namespace detail
    {
        template <class T>
        struct uncvrefptr_all_impl
        {
            using type = T;
        };
            
        template <class T>
        struct uncvrefptr_all_impl<T *> : uncvrefptr_all_impl<T>
        {
        };
            
        template <class T>
        struct uncvrefptr_all_impl<T &> : uncvrefptr_all_impl<T>
        {
        };
        
        template <class T>
        struct uncvrefptr_all_impl<T &&> : uncvrefptr_all_impl<T>
        {
        };
            
        template <class T>
        struct uncvrefptr_all_impl<T const> : uncvrefptr_all_impl<T>
        {
        };
            
        template <class T>
        struct uncvrefptr_all_impl<T volatile> : uncvrefptr_all_impl<T>
        {
        };
            
        template <class T>
        struct uncvrefptr_all_impl<T const volatile> : uncvrefptr_all_impl<T>
        {
        };
    }                                                       // namespace detail
        
    template <class T>
    using uncvrefptr_all = typename detail::uncvrefptr_all_impl<T>::type;

}}                                                          // namespace elib
namespace elib
{
    using aux::uncvrefptr;
    using aux::uncvrefptr_all;
}                                                           // namespace elib
#endif /* ELIB_AUX_TRAITS_UNCVREFPTR_HPP */