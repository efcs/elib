#ifndef ELIB_AUX_ADDRESSOF_HPP
#define ELIB_AUX_ADDRESSOF_HPP

# include <elib/aux/declval.hpp>
# include <elib/aux/enable_if.hpp>
# include <elib/aux/integral_constant.hpp>

/// std::addressof isn't marked as constexpr because it uses reinterpret_cast.
/// elib::addressof is constexpr whenever T doesn't overload operator&
namespace elib { namespace aux
{
    namespace detail
    {
        ////////////////////////////////////////////////////////////////////////
        template <class T>
        struct has_overload_addressof_impl
        {
            template <
                class U
              , ELIB_ENABLE_IF_VALID_EXPR(::elib::aux::declval<U &>().operator&())
              >
            static elib::true_ test(int);
                
            template <class>
            static elib::false_ test(long);
                
            using type = decltype(test<T>(0));
        };
        
        template <class T>
        using has_overload_addressof = typename has_overload_addressof_impl<T>::type;
          
        ////////////////////////////////////////////////////////////////////////
        template <bool HasOverload>
        struct addressof_impl
        {
            template <class T>
            static constexpr T* addressof(T & t) noexcept
            {
                return &t;
            }
        };
            
        ////////////////////////////////////////////////////////////////////////
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
        using HasOverload = typename detail::has_overload_addressof<T>;
        return detail::addressof_impl<HasOverload::value>::addressof(t);
    }
}}                                                          // namespace elib
namespace elib
{
    using aux::addressof;
}                                                           // namespace elib
#endif /* ELIB_AUX_ADDRESSOF_HPP */