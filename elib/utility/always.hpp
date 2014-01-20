#ifndef ELIB_UTILITY_ALWAYS_HPP
#define ELIB_UTILITY_ALWAYS_HPP

# include <elib/utility/integral_constant.hpp>

namespace elib 
{
    namespace utility
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
    }                                                       // namespace utility
}                                                           // namespace elib
#endif /* ELIB_UTILITY_ALWAYS_HPP */