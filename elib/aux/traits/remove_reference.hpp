#ifndef ELIB_AUX_TRAITS_REMOVE_REFERENCE_HPP
#define ELIB_AUX_TRAITS_REMOVE_REFERENCE_HPP

#include <type_traits>

namespace elib { namespace aux
{
    namespace traits
    {
        using std::remove_reference;
        
        template <class T>
        using remove_reference_t = typename remove_reference<T>::type;
        
        template <class T>
        using remove_ref = remove_reference<T>;
        
        template <class T>
        using remove_ref_t = remove_reference_t<T>;
    }                                                       //namespace traits
    
    using namespace traits;
}}                                                           //namespace elib
#endif /* ELIB_AUX_TRAITS_REMOVE_REFERENCE_HPP */
