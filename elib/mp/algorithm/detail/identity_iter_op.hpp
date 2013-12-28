#ifndef ELIB_MP_ALGORITHM_DETAIL_IDENTITY_ITER_OP_HPP
#define ELIB_MP_ALGORITHM_DETAIL_IDENTITY_ITER_OP_HPP

# include <elib/mp/identity.hpp>

namespace elib 
{
  namespace mp
  {
    namespace detail
    {
      
      struct identity_iter_op
      {
        template <class Iter>
        using apply = identity< Iter >;
      };
      
    }                                                       // namespace detail
  }                                                         // namespace mp
}                                                           // namespace elib
#endif /* ELIB_MP_ALGORITHM_DETAIL_IDENTITY_ITER_OP_HPP */