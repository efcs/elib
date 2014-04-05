#ifndef ELIB_AUX_TRAITS_DECAY_HPP
#define ELIB_AUX_TRAITS_DECAY_HPP

#include <type_traits>

namespace elib { namespace aux
{
    namespace traits
    {
        using std::decay;
        
        template <class T>
        using decay_t = typename decay<T>::type;
    }                                                       //namespace traits
    
    using namespace traits;
}}                                                           //namespace elib
#endif /* ELIB_AUX_TRAITS_DECAY_HPP */
