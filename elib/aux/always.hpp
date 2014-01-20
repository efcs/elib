#ifndef ELIB_AUX_ALWAYS_HPP
#define ELIB_AUX_ALWAYS_HPP

# include <elib/aux/integral_constant.hpp>

namespace elib 
{
    namespace aux
    {
        namespace detail
        {
            template <class Always, class ...Ignored>
            struct _always
            {
                using type = Always;
            };
        }                                                   // namespace detail
        
        template <class ...T>
        using always = typename detail::_always<true_, T...>::type;
        
        template <class ...T>
        using never = typename detail::_always<false_, T...>::type;
        
        template <class ...T>
        using always_void = typename detail::_always<void, T...>::type;
    }                                                       // namespace aux
}                                                           // namespace elib
#endif /* ELIB_AUX_ALWAYS_HPP */