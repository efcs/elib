#ifndef ELIB_MP_VECTOR_ITERATOR_HPP
#define ELIB_MP_VECTOR_ITERATOR_HPP

# include <elib/mp/vector/fwd.hpp>
# include <elib/mp/vector/vector.hpp>
# include <elib/mp/iterator.hpp>
# include <elib/mp/get_impl.hpp>
# include <cstddef>

namespace elib 
{
  namespace mp
  {
    
    template <class Vector, std::size_t Pos>
    struct vector_iterator
    {
      using type = vector_iterator;
      using category = random_access_iterator_tag;
    };
    
    
    template <class Vector, std::size_t Pos>
    struct get_impl< vector_iterator<Vector, Pos> >
    {
      using type = detail::vector_iterator_intrinsics;
    };
    
  }                                                         // namespace mp
}                                                           // namespace elib
#endif /* ELIB_MP_VECTOR_ITERATOR_HPP */