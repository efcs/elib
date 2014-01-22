#ifndef ELIB_FUSE_CONTAINER_TUPLE_TUPLE_FWD_HPP
#define ELIB_FUSE_CONTAINER_TUPLE_TUPLE_FWD_HPP

# include <elib/aux.hpp>

namespace elib { namespace fuse
{
    struct tuple_tag;
    struct tuple_model;
    
    template <class ...Types>
    struct tuple;
    
    namespace detail
    {
        template <int N, class T, bool Empty = aux::is_empty<T>::value>
        struct tuple_item;
        
    }                                                       // namespace detail
}}                                                          // namespace elib
#endif /* ELIB_FUSE_CONTAINER_TUPLE_TUPLE_FWD_HPP */