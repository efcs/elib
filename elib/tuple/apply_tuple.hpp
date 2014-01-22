#ifndef ELIB_TUPLE_APPLY_TUPLE_HPP
#define ELIB_TUPLE_APPLY_TUPLE_HPP

# include <elib/aux/tuple/fwd.hpp>
# include <elib/aux/tuple/pair.hpp>
# include <elib/aux/tuple/tuple.hpp>
# include <elib/aux/integer_sequence.hpp>
# include <elib/aux/move.hpp>
# include <elib/aux/type_traits.hpp>
# include <tuple>
# include <cstddef>

namespace elib 
{
    namespace aux
    {
        namespace tuple_detail
        {
            ////////////////////////////////////////////////////////////////////
            // tuple_detail::apply_tuple_impl
            template <
                class F
              , class Tuple
              , std::size_t... I
              >
            auto apply_tuple_impl(F&& f, Tuple&& t, index_sequence<I...>)
            ELIB_AUTO_RETURN_NOEXCEPT(
                static_cast<F &&>(f)(
                  get<I>(static_cast<Tuple &&>(t))... 
                )
            )
        }                                                   // namespace tuple_detail

        ////////////////////////////////////////////////////////////////////////
        // apply_unpacked_tuple
        template <
            class F
          , class Tuple
          , class IndexSeq = make_index_sequence<tuple_size< decay_t<Tuple> >::value>
        >
        auto apply_tuple(F&& f, Tuple&& t, IndexSeq())
        ELIB_AUTO_RETURN_NOEXCEPT(
            tuple_detail::apply_tuple_impl(
                static_cast<F &&>(f), static_cast<Tuple &&>(t), IndexSeq{}
            )
        )
        
    }                                                       // namespace aux
}                                                           // namespace elib
#endif /* ELIB_TUPLE_APPLY_TUPLE_HPP */