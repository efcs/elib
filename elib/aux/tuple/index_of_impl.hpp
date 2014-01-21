#ifndef ELIB_AUX_TUPLE_INDEX_OF_IMPL_HPP
#define ELIB_AUX_TUPLE_INDEX_OF_IMPL_HPP

# include <elib/aux/tuple/fwd.hpp>
# include <elib/aux/tuple/elib_tuple.hpp>
# include <elib/aux/tuple/item.hpp>
# include <elib/aux/tuple/tuple_impl.hpp>
# include <elib/aux/integral_constant.hpp>
# include <elib/aux/move.hpp>
# include <utility>
# include <cstddef>

namespace elib { namespace aux
{
    namespace tuple_detail
    {
        ////////////////////////////////////////////////////////////////////////////
        // detail::index_of_impl
        template <class Key, class ...Args>
        struct index_of_impl<Key, tuple<Args...>>
        {
            using Impl = typename tuple<Args...>::Impl;
            using AtKey = typename Impl::template item_at_key<Key>;
            
            using type = typename AtKey::index;
        };
        
        template <class Key, class Second>
        struct index_of_impl<Key, pair<Key, Second>>
        {
            using type = size_type_<0>;
        };
        
        template <class Key, class First>
        struct index_of_impl<Key, pair<First, Key>>
        {
            using type = size_type_<1>;
        };
        
        template <class Key, class Second>
        struct index_of_impl<Key, std::pair<Key, Second>>
        {
            using type = size_type_<0>;
        };
        
        template <class Key, class First>
        struct index_of_impl<Key, std::pair<First, Key>>
        {
            using type = size_type_<1>;
        };
    }                                                       // namespace tuple_detail
}}                                                          // namespace elib
#endif /* ELIB_AUX_TUPLE_INDEX_OF_IMPL_HPP */