#ifndef ELIB_AUX_IGNORE_HPP
#define ELIB_AUX_IGNORE_HPP

namespace elib 
{
    namespace aux
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
    }                                                       // namespace aux
}                                                           // namespace elib
#endif /* ELIB_AUX_IGNORE_HPP */