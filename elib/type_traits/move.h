#ifndef ELIB_TYPE_TRAITS_MOVE_H
#define ELIB_TYPE_TRAITS_MOVE_H


#include <elib/type_traits/remove_reference.h>


namespace elib {
    

template <typename T>
constexpr remove_reference_t<T>&&
move(T&& v) noexcept
{
    return static_cast<remove_reference_t<T>&&>(v);
}
    
    
} /* namespace elib */
#endif /* ELIB_TYPE_TRAITS_MOVE_H */