#ifndef ELIB_AUX_TRAITS_REMOVE_ALL_EXTENTS_HPP
#define ELIB_AUX_TRAITS_REMOVE_ALL_EXTENTS_HPP

#include <type_traits>

namespace elib { namespace aux
{
    using std::remove_all_extents;
        
    template <class T>
    using remove_all_extents_t = typename remove_all_extents<T>::type;
}}                                                           //namespace elib
#endif /* ELIB_AUX_TRAITS_REMOVE_ALL_EXTENTS_HPP */
