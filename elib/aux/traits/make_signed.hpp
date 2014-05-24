#ifndef ELIB_AUX_TRAITS_MAKE_SIGNED_HPP
#define ELIB_AUX_TRAITS_MAKE_SIGNED_HPP

#include <type_traits>

namespace elib { namespace aux
{
    using std::make_signed;
        
    template <class T>
    using make_signed_t = typename make_signed<T>::type;
}}                                                           //namespace elib
#endif /* ELIB_AUX_TRAITS_MAKE_SIGNED_HPP */
