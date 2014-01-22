#ifndef ELIB_TUPLE_TUPLE_IMPL_HPP
#define ELIB_TUPLE_TUPLE_IMPL_HPP

# include <elib/aux/tuple/fwd.hpp>
# include <elib/aux/tuple/element_impl.hpp>
# include <elib/aux/tuple/item.hpp>
# include <elib/aux/tuple/tuple_indexes.hpp>
# include <elib/aux/tuple/tuple_types.hpp>
# include <elib/aux/tuple/unique_value_helper.hpp>
# include <elib/aux/integral_constant.hpp>
# include <elib/aux/move.hpp>
# include <elib/aux/no_decay.hpp>
# include <elib/aux/none.hpp>
# include <elib/aux/swallow.hpp>
# include <utility>
# include <cstddef>

namespace elib { namespace aux
{
    namespace tuple_detail
    {
        
        ////////////////////////////////////////////////////////////////////////
        // tuple_detail::tuple_impl
        template <class Indexes, class ...Types>
        struct tuple_impl;
        
        template <std::size_t ...Indexes, class ...Types>
        struct tuple_impl< tuple_indexes<Indexes...>, Types...>
          : tuple_item_c<Indexes, Types>...
        {
            ////////////////////////////////////////////////////////////////////
            // item_at_index_lookup
            template <class Index, class Value>
            static tuple_item<Index, Value>
            item_at_index_lookup(tuple_item<Index, Value> const&);
            
            template <class Index>
            static none item_at_index_lookup(...);
            
            ////////////////////////////////////////////////////////////////////
            //
            template <std::size_t Index>
            struct item_at_index
            {
                using result = decltype(
                    item_at_index_lookup<size_type_<Index>>(std::declval<tuple_impl>())
                );
                
                static_assert(
                    !is_same<result, none>::value
                  , "Index lookup failed"
                  );
                
                using type = typename result::value_type;
                using index = typename result::index;
                
                static constexpr type& call(tuple_impl& im) noexcept
                {
                    return static_cast<type &>(
                        static_cast<result &>(im).get()
                      );
                }
                
                static constexpr type const & call(tuple_impl const& im) noexcept
                {
                    return static_cast<type const &>(
                            static_cast<result const&>(im).get()
                        );
                }
                
                static constexpr type && call(tuple_impl && im) noexcept
                {
                    return static_cast<type &&>(
                            static_cast<result &&>(im).get()
                          );
                }
            };
            
            ////////////////////////////////////////////////////////////////////
            //
            template <class Value, class Index>
            static tuple_item<Index, Value>
            item_at_value_lookup(tuple_item<Index, Value> const&);
            
            template<class Value>
            static none item_at_value_lookup(...);
            
            ////////////////////////////////////////////////////////////////////
            //
            template <class Value>
            struct item_at_value
            {
                using result = decltype(
                    item_at_value_lookup<Value>(std::declval<tuple_impl>())
                  );
                
                static_assert( 
                    !is_same<result, none>::value
                  , "item at value lookup failed"
                  );
                
                using type = typename result::value_type;
                using index = typename result::index;
                
                static_assert(
                    is_unique_value<
                        index::value, Value
                      , tuple_indexes<Indexes...>
                      , tuple_types<Types...>
                    >::value
                  , "item_at_value: duplicates in tuple"
                );
                
                static constexpr type& call(tuple_impl & im) noexcept
                {
                    return static_cast<type &>(
                            static_cast<result &>(im).get()
                      );
                }
                
                static constexpr type const& call(tuple_impl const& im) noexcept
                {
                    return static_cast<type const &>(
                        static_cast<result const &>(im).get()
                      );
                }
                
                static constexpr type && call(tuple_impl && im) noexcept
                {
                    return static_cast<type &&>(
                        static_cast<result &&>( std::move(im) ).get()
                      );
                }
            };
            
            ////////////////////////////////////////////////////////////////////
            //
            template <class Key, class Index, class Value>
            static tuple_item<Index, pair<Key, Value>>
            item_at_key_lookup(tuple_item<Index, pair<Key, Value>> const&);
            
            template <class Key>
            static none item_at_key_lookup(...);
            
            ////////////////////////////////////////////////////////////////////
            //
            template <class Key>
            struct item_at_key
            {
                using result = decltype(
                    item_at_key_lookup<Key>(std::declval<tuple_impl>())
                  );
                
                static_assert( 
                    !is_same<result, none>::value
                  , "item at key lookup failed"
                  );
                
                using type = typename result::value_type;
                using index = typename result::index;
                
                static_assert(
                    is_unique_key<
                          index::value, Key
                        , tuple_indexes<Indexes...>
                        , tuple_types<Types...>
                    >::value
                    , "item_at_key:: duplicates in tuple"
                 );
                
                static constexpr type& call(tuple_impl & im) noexcept
                {
                    return static_cast<type &>(
                            static_cast<result &>(im).get()
                      );
                }
                
                static constexpr type const& call(tuple_impl const& im) noexcept
                {
                    return static_cast<type const &>(
                        static_cast<result const &>(im).get()
                      );
                }
                
                static constexpr type && call(tuple_impl && im) noexcept
                {
                    return static_cast<type &&>(
                        static_cast<result &&>( std::move(im) ).get()
                      );
                }
            };
            
            template <
                std::size_t ...I0, class ...Ts0
              , std::size_t ...I1, class ...Ts1
              , class ...ValueTypes
            >
            explicit tuple_impl(
                    tuple_indexes<I0...>, tuple_types<Ts0...>
                  , tuple_indexes<I1...>, tuple_types<Ts1...>
                  , ValueTypes &&... values)
                : tuple_item_c<I0, Ts0>(static_cast<ValueTypes &&>(values))...
                , tuple_item_c<I1, Ts1>()...
            {}
            
            template <class OtherT>
            tuple_impl(OtherT && t)
              : tuple_item_c<Indexes, Types>(
                    aux::forward<
                        tuple_element_impl_t<Indexes,  make_tuple_types_t<OtherT>>
                >(get<Indexes>(t)))...
            {}
            
            template <class OtherT>
            tuple_impl& operator=(OtherT && t)
            {
                swallow(
                    tuple_item_c<Indexes, Types>::operator=(
                        aux::forward<
                            tuple_element_impl_t<Indexes, make_tuple_types_t<OtherT>>
                        >(get<Indexes>(t))
                    )...
                  );
                return *this;
            }
            
            tuple_impl& operator=(tuple_impl const& t)
            {
                swallow(tuple_item_c<Indexes, Types>::operator=(
                    static_cast<tuple_item_c<Indexes, Types>& >(t).get()
                    )...
                );
                
                return *this;
            }
            
            void swap(tuple_impl & t)
            {
                swallow(tuple_item_c<Indexes, Types>::swap(
                    static_cast<tuple_item_c<Indexes, Types> &>(t)
                  )...
                );
            }
        };
    }                                                       // namespace tuple_detail
}}                                                          // namespace elib
#endif /* ELIB_TUPLE_TUPLE_IMPL_HPP */