#ifndef ELIB_AUX_TRAITS_COMMON_TYPE_HPP
#define ELIB_AUX_TRAITS_COMMON_TYPE_HPP

#include <type_traits>

namespace elib { namespace aux
{
    using std::common_type;
        
    template <class ...Args>
    using common_type_t = typename common_type<Args...>::type;
}}                                                           //namespace elib
#endif /* ELIB_AUX_TRAITS_COMMON_TYPE_HPP */
