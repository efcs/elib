#ifndef ELIB_AUX_SUPPORT_STATIC_CONST_HPP
#define ELIB_AUX_SUPPORT_STATIC_CONST_HPP

// for use with ELIB_ENABLE_IF and ELIB_ENABLE_IF_VALID_EXPR 
# define ELIB_ENABLER_TYPE void* const&
# define ELIB_ENABLER ::elib::aux::enabler

namespace elib { namespace aux
{
    template <class T>
    struct static_const
    { 
        static constexpr T value{}; 
    };

    template <class T>
    constexpr T static_const<T>::value;

    static constexpr void *const & enabler = static_const<void*>::value;
}}                                                          // namespace elib
#endif /* ELIB_AUX_SUPPORT_STATIC_CONST_HPP */