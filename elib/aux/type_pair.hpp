#ifndef ELIB_AUX_TYPE_PAIR_HPP
#define ELIB_AUX_TYPE_PAIR_HPP

namespace elib { namespace aux
{
    template <class First, class Second>
    struct type_pair
    {
        using type = type_pair;
        using first = First;
        using second = Second;
    };
    
    template <class T>
    using first_t = typename T::first;
    
    template <class T>
    using second_t = typename T::second;
}}                                                          // namespace elib
#endif /* ELIB_AUX_TYPE_PAIR_HPP */