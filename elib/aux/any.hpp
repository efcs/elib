#ifndef ELIB_AUX_ANY_HPP
#define ELIB_AUX_ANY_HPP

namespace elib 
{
    namespace aux
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
    }                                                       // namespace aux
}                                                           // namespace elib
#endif /* ELIB_AUX_ANY_HPP */