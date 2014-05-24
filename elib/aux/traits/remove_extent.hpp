#ifndef ELIB_AUX_TRAITS_REMOVE_EXTENT_HPP
#define ELIB_AUX_TRAITS_REMOVE_EXTENT_HPP

#include <type_traits>

namespace elib { namespace aux
{
    using std::remove_extent;
        
    template <class T>
    using remove_extent_t = typename remove_extent<T>::type;
}}                                                           //namespace elib
#endif /* ELIB_AUX_TRAITS_REMOVE_EXTENT_HPP */
