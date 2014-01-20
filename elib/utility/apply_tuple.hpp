#ifndef ELIB_UTILITY_APPLY_TUPLE_HPP
#define ELIB_UTILITY_APPLY_TUPLE_HPP

# include <elib/utility/integer_sequence.hpp>
# include <elib/utility/move.hpp>
# include <elib/utility/type_traits.hpp>
# include <tuple>

namespace elib 
{
    namespace utility
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
                    std::get<I>(static_cast<Tuple &&>(t))... 
                )
            )
        }                                                   // namespace detail

        ////////////////////////////////////////////////////////////////////////
        // apply_unpacked_tuple
        template <
            class F
          , class Tuple
          , class IndexSeq = make_index_sequence<std::tuple_size< decay<Tuple> >::value>
        >
        auto apply_unpacked_tuple(F&& f, Tuple&& t, IndexSeq())
        ELIB_AUTO_RETURN_NOEXCEPT(
            detail::apply_tuple_impl(
                static_cast<F &&>(f), static_cast<Tuple &&>(t), IndexSeq{}
            )
        )
        
    }                                                       // namespace utility
}                                                           // namespace elib
#endif /* ELIB_UTILITY_APPLY_TUPLE_HPP */