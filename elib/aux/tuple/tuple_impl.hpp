#ifndef ELIB_AUX_TUPLE_TUPLE_IMPL_HPP
#define ELIB_AUX_TUPLE_TUPLE_IMPL_HPP

# include <elib/aux/tuple/fwd.hpp>
# include <elib/aux/tuple/element_impl.hpp>
# include <elib/aux/tuple/item.hpp>
# include <elib/aux/tuple/tuple_indexes.hpp>
# include <elib/aux/tuple/tuple_types.hpp>
# include <elib/aux/move.hpp>
# include <elib/aux/no_decay.hpp>
# include <elib/aux/none.hpp>
# include <elib/aux/swallow.hpp>
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
#endif /* ELIB_AUX_TUPLE_TUPLE_IMPL_HPP */