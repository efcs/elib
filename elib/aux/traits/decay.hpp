#ifndef ELIB_AUX_TRAITS_DECAY_HPP
#define ELIB_AUX_TRAITS_DECAY_HPP

#include <type_traits>

namespace elib { namespace aux
{
    using std::decay;
        
    template <class T>
    using decay_t = typename decay<T>::type;
}}                                                           //namespace elib
#endif /* ELIB_AUX_TRAITS_DECAY_HPP */
