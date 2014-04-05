#ifndef ELIB_AUX_ADDRESSOF_HPP
#define ELIB_AUX_ADDRESSOF_HPP

# include <elib/aux/integral_constant.hpp>
# include <elib/aux/declval.hpp>
# include <cstddef>

namespace elib { namespace aux
{
    namespace detail
    {
        template <class T>
        struct has_overload_addressof
        {
            template <
                class U
              , std::size_t = sizeof(::elib::aux::declval<U &>().operator&())
              >
            static constexpr bool test(int) { return true; }
                
            template <class U>
            static constexpr bool test(long) { return false; }
                
            using type = integral_constant<bool, test<T>(0)>;
        };
            
        template <bool HasOverload>
        struct addressof_impl
        {
            template <class T>
            static constexpr T* addressof(T & t) noexcept
            {
                return &t;
            }
        };
            
        template <>
        struct addressof_impl<true>
        {
            template <class T>
            static T* addressof(T & t) noexcept
            {
                return reinterpret_cast<T*>(
                & const_cast<char &>(
                    reinterpret_cast<const volatile char &>(t)
                ));
            }
        };
    }                                                   // namespace detail
        
    ////////////////////////////////////////////////////////////////////////
    // aux::addressof
    template <class T>
    constexpr T* addressof(T & t) noexcept
    {
        using HasOverload = typename detail::has_overload_addressof<T>::type;
        return detail::addressof_impl<HasOverload::value>::addressof(t);
    }
}}                                                          // namespace elib
namespace elib
{
    using aux::addressof;
}                                                           // namespace elib
#endif /* ELIB_AUX_ADDRESSOF_HPP */