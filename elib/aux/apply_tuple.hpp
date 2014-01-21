#ifndef ELIB_AUX_APPLY_TUPLE_HPP
#define ELIB_AUX_APPLY_TUPLE_HPP

# include <elib/aux/integer_sequence.hpp>
# include <elib/aux/move.hpp>
# include <elib/aux/type_traits.hpp>
# include <elib/aux/tuple_fwd.hpp>
# include <tuple>
# include <cstddef>

namespace elib 
{
    namespace aux
    {
        namespace detail
        {
            ////////////////////////////////////////////////////////////////////
            // detail::apply_tuple_impl
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
        }                                                   // namespace detail

        ////////////////////////////////////////////////////////////////////////
        // apply_unpacked_tuple
        template <
            class F
          , class Tuple
          , class IndexSeq = make_index_sequence<tuple_size< decay_t<Tuple> >::value>
        >
        auto apply_tuple(F&& f, Tuple&& t, IndexSeq())
        ELIB_AUTO_RETURN_NOEXCEPT(
            detail::apply_tuple_impl(
                static_cast<F &&>(f), static_cast<Tuple &&>(t), IndexSeq{}
            )
        )
        
    }                                                       // namespace aux
}                                                           // namespace elib
#endif /* ELIB_AUX_APPLY_TUPLE_HPP */