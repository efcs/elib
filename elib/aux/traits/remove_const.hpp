#ifndef ELIB_AUX_TRAITS_REMOVE_CONST_HPP
#define ELIB_AUX_TRAITS_REMOVE_CONST_HPP

#include <type_traits>

namespace elib { namespace aux
{
    namespace traits
    {
        using std::remove_const;
        
        template <class T>
        using remove_const_t = typename remove_const<T>::type;
    }                                                       //namespace traits
    
    using namespace traits;
}}                                                           //namespace elib
#endif /* ELIB_AUX_TRAITS_REMOVE_CONST_HPP */
