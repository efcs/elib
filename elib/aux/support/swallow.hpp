#ifndef ELIB_AUX_SUPPORT_SWALLOW_HPP
#define ELIB_AUX_SUPPORT_SWALLOW_HPP

namespace elib { namespace aux
{
# if __cplusplus <= 201303L
    template <class ...T>
    inline void swallow(T &&...) noexcept {}
# else
    template <class ...T>
    constexpr void swallow(T &&...) noexcept {}
# endif
}}                                                          // namespace elib
#endif /* ELIB_AUX_SUPPORT_SWALLOW_HPP */