#ifndef ELIB_AUX_SWALLOW_HPP
#define ELIB_AUX_SWALLOW_HPP

namespace elib 
{
    namespace aux
    {
# if __cplusplus < 201300
        template <class ...T>
        inline void swallow(T &&...) noexcept
        {}
# else
        template <class ...T>
        constexpr void swallow(T &&...) noexcept
        {}
# endif
    }                                                       // namespace aux
}                                                           // namespace elib
#endif /* ELIB_AUX_SWALLOW_HPP */