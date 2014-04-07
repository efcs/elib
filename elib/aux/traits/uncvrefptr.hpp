#ifndef ELIB_AUX_TRAITS_UNCVREFPTR_HPP
# define ELIB_AUX_TRAITS_UNCVREFPTR_HPP

namespace elib { namespace aux
{
    namespace traits
    {
        namespace traits_detail
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
        }                                            // namespace traits_detail
        
        template <class T>
        using uncvrefptr = typename traits_detail::uncvrefptr_impl<T>::type;
        
        namespace traits_detail
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
        }                                            // namespace traits_detail
        
        template <class T>
        using uncvrefptr_all = typename traits_detail::uncvrefptr_all_impl<T>::type;
    }                                                       // namespace traits
    
    using namespace traits;
}}                                                          // namespace elib
namespace elib
{
    using aux::uncvrefptr;
    using aux::uncvrefptr_all;
}                                                           // namespace elib
#endif /* ELIB_AUX_TRAITS_UNCVREFPTR_HPP */