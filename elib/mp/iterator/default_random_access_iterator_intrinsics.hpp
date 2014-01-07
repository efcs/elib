#ifndef ELIB_MP_ITERATOR_DEFAULT_RANDOM_ACCESS_ITERATOR_INTRINSICS_HPP
#define ELIB_MP_ITERATOR_DEFAULT_RANDOM_ACCESS_ITERATOR_INTRINSICS_HPP

# include <elib/mp/iterator/fwd.hpp>
# include <elib/mp/iterator/iterator.hpp>
# include <cstddef>

namespace elib 
{
  namespace mp
  {
    
    template <>
    struct iterator_intrinsics< model::default_random_access_iterator >
    {
      
    };
    
  }                                                         // namespace mp
}                                                           // namespace elib
#endif /* ELIB_MP_ITERATOR_DEFAULT_RANDOM_ACCESS_ITERATOR_INTRINSICS_HPP */