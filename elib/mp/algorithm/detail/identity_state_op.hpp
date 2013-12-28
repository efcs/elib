#ifndef ELIB_MP_ALGORITHM_DETAIL_IDENTITY_STATE_OP_HPP
#define ELIB_MP_ALGORITHM_DETAIL_IDENTITY_STATE_OP_HPP

# include <elib/mp/identity.hpp>

namespace elib 
{
  namespace mp
  {
    namespace detail
    {
      
      struct identity_state_op
      {
        template <class State, class Iter>
        using apply = identity< State >;
      };
      
    }                                                       // namespace detail
  }                                                         // namespace mp
}                                                           // namespace elib
#endif /* ELIB_MP_ALGORITHM_DETAIL_IDENTITY_STATE_OP_HPP */