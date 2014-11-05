#ifndef ELIB_AUX_STATIC_CONST_HPP
#define ELIB_AUX_STATIC_CONST_HPP

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

    namespace detail
    {
        // suppress unused enabler warning
        constexpr struct unused_enabler_t {
            constexpr unused_enabler_t(void *const &) {}
        } unused_enabler{enabler};
    }                                                       // namespace detail
    
}}                                                          // namespace elib
#endif /* ELIB_AUX_STATIC_CONST_HPP */