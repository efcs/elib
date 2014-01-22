#ifndef ELIB_TUPLE_APPLY_TUPLE_HPP
#define ELIB_TUPLE_APPLY_TUPLE_HPP

# include <elib/tuple/fwd.hpp>
# include <elib/tuple/pair.hpp>
# include <elib/tuple/tuple.hpp>
# include <elib/tuple/tuple_indexes.hpp>
# include <elib/aux.hpp>
# include <tuple>
# include <cstddef>

namespace elib 
{
    namespace tuples
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
            auto apply_tuple_impl(F&& f, Tuple&& t, tuple_indexes<I...>)
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
          , class IndexSeq = make_tuple_indexes_t<
                                tuple_size<aux::decay_t<Tuple>>::value
                             >
        >
        auto apply_tuple(F&& f, Tuple&& t, IndexSeq())
        ELIB_AUTO_RETURN_NOEXCEPT(
            detail::apply_tuple_impl(
                static_cast<F &&>(f), static_cast<Tuple &&>(t), IndexSeq{}
            )
        )
        
    }                                                       // namespace tuples
}                                                           // namespace elib
#endif /* ELIB_TUPLE_APPLY_TUPLE_HPP */