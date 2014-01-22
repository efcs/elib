#ifndef ELIB_MP_SAME_TYPE_HPP
#define ELIB_MP_SAME_TYPE_HPP

# include <elib/aux.hpp>

namespace elib { namespace mp
{
    template <class T, class U>
    struct same_type : false_ {};
    
    template <class T>
    struct same_type<T, T> : true_ {};
    
    template <class T, class U>
    using same_type_t = typename same_type<T, U>::type;

}}                                                           // namespace elib
#endif /* ELIB_MP_SAME_TYPE_HPP */