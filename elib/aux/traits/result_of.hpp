#ifndef ELIB_AUX_TRAITS_RESULT_OF_HPP
#define ELIB_AUX_TRAITS_RESULT_OF_HPP

#include <type_traits>

namespace elib { namespace aux
{
    namespace traits
    {
        using std::result_of;
        
        template <class T>
        using result_of_t = typename result_of<T>::type;
    }                                                       //namespace traits
    
    using namespace traits;
}}                                                           //namespace elib
#endif /* ELIB_AUX_TRAITS_RESULT_OF_HPP */
