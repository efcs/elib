#ifndef ELIB_UTILITY_APPLY_TUPLE_HPP
#define ELIB_UTILITY_APPLY_TUPLE_HPP

/* Unpack a tuple and apply it to a function
 * Implementation inspired (taken) from C++14 standard draft
 */
# include <elib/utility/integer_sequence.hpp>
# include <type_traits>
# include <tuple>

namespace elib 
{
  namespace detail
  {
      
    template <class F, class Tuple, std::size_t... I>
    auto apply_tuple_impl(F&& f, Tuple&& t, index_seq<I...>)
    -> decltype(std::forward<F>(f)(std::get<I>(std::forward<Tuple>(t))...))
    {
      return std::forward<F>(f)( std::get<I>( std::forward<Tuple>(t) )... );
    }
    
  }                                                         // namespace detail
  
//-------------------------- apply_unpacked_tuple -------------------------// 
  
  template <class F, class Tuple
      , class IndexSeq = make_index_seq<std::tuple_size<Tuple>::value>
  >
  auto apply_unpacked_tuple(F&& f, Tuple&& t, IndexSeq())
  -> decltype(
      detail::apply_tuple_impl(
        std::forward<F>(f), std::forward<Tuple>(t), IndexSeq()
      )
    )
  {
    return detail::apply_tuple_impl(
      std::forward<F>(f), std::forward<Tuple>(t), IndexSeq()
    );
  }

}                                                           // namespace elib
#endif /* ELIB_UTILITY_APPLY_TUPLE_HPP */