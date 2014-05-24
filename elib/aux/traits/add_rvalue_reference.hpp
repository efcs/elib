#ifndef ELIB_AUX_TRAITS_ADD_RVALUE_REFERENCE_HPP
#define ELIB_AUX_TRAITS_ADD_RVALUE_REFERENCE_HPP

#include <type_traits>

namespace elib { namespace aux
{
    using std::add_rvalue_reference;
        
    template <class T>
    using add_rvalue_reference_t = typename add_rvalue_reference<T>::type;
        
    template <class T>
    using add_rvalue_ref = add_rvalue_reference<T>;
        
    template <class T>
    using add_rvalue_ref_t = typename add_rvalue_reference<T>::type;
}}                                                           //namespace elib
#endif /* ELIB_AUX_TRAITS_ADD_RVALUE_REFERENCE_HPP */
