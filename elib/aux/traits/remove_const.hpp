#ifndef ELIB_AUX_TRAITS_REMOVE_CONST_HPP
#define ELIB_AUX_TRAITS_REMOVE_CONST_HPP

#include <type_traits>

namespace elib { namespace aux
{
    using std::remove_const;
        
    template <class T>
    using remove_const_t = typename remove_const<T>::type;
}}                                                            // namespace elib
#endif /* ELIB_AUX_TRAITS_REMOVE_CONST_HPP */
