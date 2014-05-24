#ifndef ELIB_AUX_TRAITS_STRIP_REF_WRAPPER_HPP
#define ELIB_AUX_TRAITS_STRIP_REF_WRAPPER_HPP

# include <functional>

namespace elib { namespace aux
{
    template <class T>
    struct strip_ref_wrapper 
    { 
        using type = T; 
    };
        
    template <class T>
    struct strip_ref_wrapper< std::reference_wrapper<T> >
    {
        using type = T&;
    };

    template <class T>
    using strip_ref_wrapper_t = typename strip_ref_wrapper<T>::type;
}}                                                           //namespace elib
#endif /* ELIB_AUX_TRAITS_STRIP_REF_WRAPPER_HPP */
