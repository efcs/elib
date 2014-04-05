#ifndef ELIB_AUX_TRAITS_ADD_VOLATILE_HPP
#define ELIB_AUX_TRAITS_ADD_VOLATILE_HPP

#include <type_traits>

namespace elib { namespace aux
{
    namespace traits
    {
        using std::add_volatile;
        
        template <class T>
        using add_volatile_t = typename add_volatile<T>::type;
    }                                                       //namespace traits
    
    using namespace traits;
}}                                                           //namespace elib
#endif /* ELIB_AUX_TRAITS_ADD_VOLATILE_HPP */
