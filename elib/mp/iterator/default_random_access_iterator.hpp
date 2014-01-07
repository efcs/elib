#ifndef ELIB_MP_ITERATOR_DEFAULT_RANDOM_ACCESS_ITERATOR_HPP
#define ELIB_MP_ITERATOR_DEFAULT_RANDOM_ACCESS_ITERATOR_HPP

# include <elib/mp/iterator/fwd.hpp>
# include <elib/mp/iterator/default_random_access_iterator_intrinsics.hpp>
# include <elib/mp/get_impl.hpp>
# include <cstddef>

namespace elib 
{
  namespace mp
  {
    
    template <class Seq, std::size_t N>
    struct default_random_access_iterator
    {
      using model_type = model::default_random_access_iterator;
    };
    
    
    template <class Seq, std::size_t N>
    struct get_impl< default_random_access_iterator<Seq, N> >
    {
      using type = default_random_access_iterator_intrinsics;
    };
    
  }                                                         // namespace mp
}                                                           // namespace elib
#endif /* ELIB_MP_ITERATOR_DEFAULT_RANDOM_ACCESS_ITERATOR_HPP */