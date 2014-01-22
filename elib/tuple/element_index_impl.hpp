#ifndef ELIB_TUPLE_ELEMENT_INDEX_IMPL_HPP
#define ELIB_TUPLE_ELEMENT_INDEX_IMPL_HPP

# include <elib/aux/tuple/fwd.hpp>
# include <elib/aux/tuple/elib_tuple.hpp>
# include <elib/aux/tuple/item.hpp>
# include <elib/aux/tuple/tuple_impl.hpp>
# include <elib/aux/always.hpp>
# include <utility>
# include <cstddef>

namespace elib { namespace aux
{
    namespace tuple_detail
    {
        template <class Value, class T>
        struct tuple_element_index_impl;
        
        template <class Value, class ...Ts>
        struct tuple_element_index_impl<Value, tuple<Ts...>>
        {
            using Tuple = tuple<Ts...>;
            using Impl = typename Tuple::Impl;
            using Detect = typename Impl::template item_at_value<Value>;
            
            using type = typename Detect::index;
        };
        
        template <class Value, class T>
        struct tuple_element_index_impl<Value, pair<Value, T>>
        {
            using type = size_type_<0>;
        };
        
        template <class Value, class T>
        struct tuple_element_index_impl<Value, pair<T, Value>>
        {
            using type = size_type_<1>;
        };
        
        template <class Value>
        struct tuple_element_index_impl<Value, pair<Value, Value>>
        {
            static_assert(
                never<Value>::value
              , "tuple_element_index: pair has same types"
            );
        };
        
        template <class Value, class T>
        struct tuple_element_index_impl<Value, std::pair<Value, T>>
        {
            using type = size_type_<0>;
        };
        
        template <class Value, class T>
        struct tuple_element_index_impl<Value, std::pair<T, Value>>
        {
            using type = size_type_<1>;
        };
        
        template <class Value>
        struct tuple_element_index_impl<Value, std::pair<Value, Value>>
        {
            static_assert(
                never<Value>::value
              , "tuple_element_index: pair has same types"
            );
        };
        
        
    }                                                       // namespace tuple_detail
}}                                                          // namespace elib
#endif /* ELIB_TUPLE_ELEMENT_INDEX_IMPL_HPP */