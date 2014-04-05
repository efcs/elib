#ifndef ELIB_AUX_ANY_POD_HPP
#define ELIB_AUX_ANY_POD_HPP

namespace elib { namespace aux
{
    template <class Ignored = decltype(nullptr)>
    struct any_pod
    {
        any_pod(...);
    };
}}                                                          // namespace elib
#endif /* ELIB_AUX_ANY_POD_HPP */