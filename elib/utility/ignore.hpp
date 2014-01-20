#ifndef ELIB_UTILITY_IGNORE_HPP
#define ELIB_UTILITY_IGNORE_HPP

namespace elib 
{
    namespace utility
    {
# if __cplusplus < 201300
        template <class ...T>
        inline void ignore(T &&...) noexcept
        {}
# else
        template <class ...T>
        constexpr void ignore(T &&...) noexcept
        {}
# endif
    }                                                       // namespace utility
}                                                           // namespace elib
#endif /* ELIB_UTILITY_IGNORE_HPP */