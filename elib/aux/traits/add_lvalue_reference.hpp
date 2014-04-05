#ifndef ELIB_AUX_TRAITS_ADD_LVALUE_REFERENCE_HPP
#define ELIB_AUX_TRAITS_ADD_LVALUE_REFERENCE_HPP

#include <type_traits>

namespace elib { namespace aux
{
    namespace traits
    {
        using std::add_lvalue_reference;
        
        template <class T>
        using add_lvalue_reference_t = typename add_lvalue_reference<T>::type;
        
        template <class T>
        using add_lvalue_ref = add_lvalue_reference<T>;
        
        template <class T>
        using add_lvalue_ref_t = typename add_lvalue_reference<T>::type;
    }                                                       //namespace traits
    
    using namespace traits;
}}                                                           //namespace elib
#endif /* ELIB_AUX_TRAITS_ADD_LVALUE_REFERENCE_HPP */
