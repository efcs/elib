#ifndef ELIB_AUX_TYPE_PAIR_HPP
#define ELIB_AUX_TYPE_PAIR_HPP

namespace elib { namespace aux
{
    template <class First, class Second>
    struct type_pair
    {
        using type = type_pair;
        using first_type = First;
        using second_type = Second;
    };
    
    template <class T>
    using first_t = typename T::first_type;
    
    template <class T>
    using second_t = typename T::second_type;
}}                                                          // namespace elib
#endif /* ELIB_AUX_TYPE_PAIR_HPP */