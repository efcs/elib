#ifndef ELIB_AUX_TRAITS_ADD_POINTER_HPP
#define ELIB_AUX_TRAITS_ADD_POINTER_HPP

#include <type_traits>

namespace elib { namespace aux
{
    using std::add_pointer;
        
    template <class T>
    using add_pointer_t = typename add_pointer<T>::type;
}}                                                           //namespace elib
#endif /* ELIB_AUX_TRAITS_ADD_POINTER_HPP */
