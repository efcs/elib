#ifndef ELIB_TUPLE_INDEX_OF_IMPL_HPP
#define ELIB_TUPLE_INDEX_OF_IMPL_HPP

# include <elib/tuple/fwd.hpp>
# include <elib/tuple/elib_tuple.hpp>
# include <elib/tuple/item.hpp>
# include <elib/tuple/tuple_impl.hpp>
# include <elib/aux.hpp>
# include <utility>
# include <cstddef>

namespace elib { namespace tuples
{
    namespace detail
    {
        ////////////////////////////////////////////////////////////////////////////
        // detail::index_of_impl
        template <class Key, T>
        struct index_of_impl<Key, T const> : index_of_impl<Key, T>
        {};
        
        template <class Key, T>
        struct index_of_impl<Key, T volatile> : index_of_impl<Key, T>
        {};
        
        template <class Key, T>
        struct index_of_impl<Key, T const volatile> : index_of_impl<Key, T>
        {};
        
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
    }                                                       // namespace detail
}}                                                          // namespace elib
#endif /* ELIB_TUPLE_INDEX_OF_IMPL_HPP */