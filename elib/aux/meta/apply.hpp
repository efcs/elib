#ifndef ELIB_AUX_META_APPLY_HPP
#define ELIB_AUX_META_APPLY_HPP

namespace elib { namespace aux
{
    template <class T, class ...Args>
        using apply_ = typename T::template apply<Args...>;

        template <class T, class ...Args>
        using apply_t = typename T::template apply<Args...>::type;
}}                                                          // namespace elib
#endif /* ELIB_AUX_META_APPLY_HPP */