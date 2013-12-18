#ifndef ELIB_MP_VARIADIC_SEQUENCE_ITERATOR_HPP
#define ELIB_MP_VARIADIC_SEQUENCE_ITERATOR_HPP

# include <elib/mp/variadic/fwd.hpp>
# include <elib/mp/iterator.hpp>
# include <elib/mp/get_impl.hpp>
# include <cstddef>

namespace elib 
{
  namespace mp
  {
    
    template <class Seq, std::size_t N>
    struct variadic_sequence_iterator
    {
      using type = variadic_sequence_iterator;
      using category = random_access_iterator_tag;
    };
    
    template <class Seq, std::size_t N>
    struct get_impl< variadic_sequence_iterator<Seq, N> >
    {
      using type = variadic_sequence_iterator_intrinsics;
    };
    
  }                                                         // namespace mp
}                                                           // namespace elib
#endif /* ELIB_MP_VARIADIC_SEQUENCE_ITERATOR_HPP */