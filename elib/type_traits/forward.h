#ifndef ELIB_TYPE_TRAITS_FORWARD_H
#define ELIB_TYPE_TRAITS_FORWARD_H


#include <elib/type_traits/remove_reference.h>


namespace elib {
    

template <typename T>
constexpr T&&
forward(remove_reference_t<T>& v) noexcept
{
    return static_cast<T&&>(v);
}


template <typename T>
constexpr T&&
forward(remove_reference_t<T>&& v) noexcept
{
    return static_cast<T&&>(v);
}

    
} /* namespace elib */
#endif /* ELIB_TYPE_TRAITS_FORWARD_H */