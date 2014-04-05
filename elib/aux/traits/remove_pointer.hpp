#ifndef ELIB_AUX_TRAITS_REMOVE_POINTER_HPP
#define ELIB_AUX_TRAITS_REMOVE_POINTER_HPP

#include <type_traits>

namespace elib { namespace aux
{
    namespace traits
    {
        using std::remove_pointer;
        
        template <class T>
        using remove_pointer_t = typename remove_pointer<T>::type;
        
        template <class T>
        using remove_ptr = remove_pointer<T>;
        
        template <class T>
        using remove_ptr_t = remove_pointer_t<T>;
    }                                                       //namespace traits
    
    using namespace traits;
}}                                                           //namespace elib
#endif /* ELIB_AUX_TRAITS_REMOVE_POINTER_HPP */
