#ifndef ELIB_AUX_UNDEFINED_HPP
#define ELIB_AUX_UNDEFINED_HPP

# include <elib/aux/integral_constant.hpp>

namespace elib { namespace aux
{
    ////////////////////////////////////////////////////////////////////////////
    template <class ...>
    struct undefined;
    
    namespace detail
    {
        template <class T>
        struct is_undefined_impl
        {
            using type = elib::false_;
        };
        
        template <class ...Args>
        struct is_undefined_impl<undefined<Args...>>
        {
            using type = elib::true_;
        };
    }                                                       // namespace detail
    
    ////////////////////////////////////////////////////////////////////////////
    template <class T>
    using is_undefined = typename detail::is_undefined_impl<T>::type;
    
    ////////////////////////////////////////////////////////////////////////////
    template <class T>
    using is_not_undefined = 
        elib::bool_<
            not detail::is_undefined_impl<T>::type::value
        >;
}}                                                          // namespace elib
#endif /* ELIB_AUX_UNDEFINED_HPP */