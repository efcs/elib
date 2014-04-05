#ifndef ELIB_AUX_TRAITS_REMOVE_VOLATILE_HPP
#define ELIB_AUX_TRAITS_REMOVE_VOLATILE_HPP

#include <type_traits>

namespace elib { namespace aux
{
    namespace traits
    {
        using std::remove_volatile;
        
        template <class T>
        using remove_volatile_t = typename remove_volatile<T>::type;
    }                                                       //namespace traits
    
    using namespace traits;
}}                                                           //namespace elib
#endif /* ELIB_AUX_TRAITS_REMOVE_VOLATILE_HPP */
