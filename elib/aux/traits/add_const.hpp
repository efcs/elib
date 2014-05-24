#ifndef ELIB_AUX_TRAITS_ADD_CONST_HPP
#define ELIB_AUX_TRAITS_ADD_CONST_HPP

#include <type_traits>

namespace elib { namespace aux
{
    using std::add_const;
        
    template <class T>
    using add_const_t = typename add_const<T>::type;
}}                                                           //namespace elib
#endif /* ELIB_AUX_TRAITS_ADD_CONST_HPP */
