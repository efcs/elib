#ifndef ELIB_UTILITY_ANY_HPP
#define ELIB_UTILITY_ANY_HPP

namespace elib 
{
    namespace utility
    {
        namespace detail
        {
            ////////////////////////////////////////////////////////////////////
            // detail::any
            template <class Ignored = decltype(nullptr)>
            struct any
            {
                any() = default;
                
                template <typename T>
                constexpr any(T const &) noexcept
                {}
                
                template <class T>
                operator T &&() const noexcept;
            };
        }                                                   // namespace detail
        
        ////////////////////////////////////////////////////////////////////////
        // any
        using any = detail::any<>;
        
        ////////////////////////////////////////////////////////////////////////
        // any_pod
        template <class Ignored = decltype(nullptr)>
        struct any_pod
        {
            any_pod(...);
        };
    }                                                       // namespace utility
}                                                           // namespace elib
#endif /* ELIB_UTILITY_ANY_HPP */