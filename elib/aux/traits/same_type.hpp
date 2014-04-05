#ifndef ELIB_AUX_TRAITS_SAME_TYPE_HPP
#define ELIB_AUX_TRAITS_SAME_TYPE_HPP

# include <elib/aux/traits/is_same.hpp>

namespace elib { namespace aux
{
    namespace traits
    {
        template <class T, class U>
        using same_type = is_same<T, U>;
    }                                                       // namespace traits
    
    using namespace traits;
    
}}                                                          // namespace elib
#endif /* ELIB_AUX_TRAITS_SAME_TYPE_HPP */