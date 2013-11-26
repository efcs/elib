#ifndef ELIB_MP_ALGORITHM_FOLD_HPP
#define ELIB_MP_ALGORITHM_FOLD_HPP

# include <elib/mp/algorithm/algorithm_fwd.hpp>

namespace elib
{
  namespace mp
  {

    //TODO
    template <class Seq, class State, class ForwardOp> 
    struct fold;
    
    template <class Seq, class State, class BackwardOp, class ForwardOp=_1>
    struct reverse_fold;
    
  }                                                         // namespace mp
}                                                           // namespace elib
#endif /* ELIB_MP_ALGORITHM_FOLD_HPP */