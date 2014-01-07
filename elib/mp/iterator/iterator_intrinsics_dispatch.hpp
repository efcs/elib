#ifndef ELIB_MP_ITERATOR_ITERATOR_INTRINSICS_DISPATCH_HPP
#define ELIB_MP_ITERATOR_ITERATOR_INTRINSICS_DISPATCH_HPP

# include <elib/mp/iterator/fwd.hpp>
# include <elib/mp/iterator/forward_iterator_intrinsics.hpp>
# include <elib/mp/iterator/bidirectional_iterator_intrinsics.hpp>
# include <elib/mp/iterator/default_random_access_iterator_intrinsics.hpp>


namespace elib 
{
  namespace mp
  {
    
    template <class It> 
    struct iterator_intrinsics_dispatch
    {
      using type = iterator_intrinsics< typename It::model_of >;
    };
    
  }                                                         // namespace mp
}                                                           // namespace elib
#endif /* ELIB_MP_ITERATOR_ITERATOR_INTRINSICS_DISPATCH_HPP */