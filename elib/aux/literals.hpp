#ifndef ELIB_AUX_LITERALS_HPP
#define ELIB_AUX_LITERALS_HPP

# include <elib/aux/integral_constant.hpp>
# include <cstddef>


namespace elib 
{ 
    namespace aux { namespace detail
    {
        template <class To, unsigned long long Val, bool Done>
        struct generate_literal_impl
        {
            template <char ...>
            using apply = integral_constant<To, static_cast<To>(Val)>;
        };
            
        template <class To, unsigned long long Val>
        struct generate_literal_impl<To, Val, false>
        {
            template <char First, char ...Rest>
            using apply = typename 
                generate_literal_impl<
                    To
                  , (Val*10) + (First - '0')
                  , sizeof...(Rest) == 0
                >::template apply<Rest...>;
        };
        
        template <class To, char ...Ch>
        using generate_literal_apply = typename
            generate_literal_impl<To, 0, sizeof...(Ch) == 0>
                ::template apply<Ch...>;
    }}                                                 // namespace aux::detail
    
    template <char ...Ch>
    constexpr aux::detail::generate_literal_apply<int, Ch...>
    operator "" _int() noexcept
    { return {}; }
    
    template <char ...Ch>
    constexpr aux::detail::generate_literal_apply<bool, Ch...>
    operator "" _bool() noexcept
    { return {}; }
}                                                           // namespace elib
#endif /* ELIB_AUX_LITERALS_HPP */