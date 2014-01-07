#ifndef ELIB_MP_VARIADIC_PACK_ITERATOR_HPP
#define ELIB_MP_VARIADIC_PACK_ITERATOR_HPP

# include <elib/mp/variadic/fwd.hpp>
# include <elib/mp/iterator.hpp>
# include <elib/mp/get_impl.hpp>
# include <cstddef>

namespace elib 
{
  namespace mp
  {
    
    template <class Seq, std::size_t N>
    struct variadic_pack_iterator
    {
      using model_type = model::default_random_access_iterator;
    };
    
    template <class Seq, std::size_t N>
    struct get_impl< variadic_pack_iterator<Seq, N> >
    {
      using type = variadic_pack_iterator_intrinsics;
    };
    
  }                                                         // namespace mp
}                                                           // namespace elib
#endif /* ELIB_MP_VARIADIC_PACK_ITERATOR_HPP */