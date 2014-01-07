#ifndef ELIB_MP_ITERATOR_RANDOM_ACCESS_ITERATOR_INTRINSICS_HPP
#define ELIB_MP_ITERATOR_RANDOM_ACCESS_ITERATOR_INTRINSICS_HPP

# include <elib/mp/iterator/fwd.hpp>
# include <elib/mp/iterator/bidirectional_iterator_intrinsics.hpp>

namespace elib 
{
  namespace mp
  {
    
    template <>
    struct iterator_intrinsics< model::random_access_iterator >
    {
      template <class It>
      using deref = identity< typename It::item >;
      
      template <class It>
      using next = identity< typename It::next >;
      
      template <class It>
      using prior = identity< typename It::prior >;
    };
    
  }                                                         // namespace mp
}                                                           // namespace elib
#endif /* ELIB_MP_ITERATOR_RANDOM_ACCESS_ITERATOR_INTRINSICS_HPP */