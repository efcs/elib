#ifndef ELIB_MP_ALGORITHM_ITER_FOLD_HPP
#define ELIB_MP_ALGORITHM_ITER_FOLD_HPP

# include <elib/mp/algorithm/iter_fold_if.hpp>

namespace elib 
{
  namespace mp
  {
    
    template <class Seq, class State, class F>
    using iter_foldl = iter_foldl_if<Seq, State, F>;
      
    template <class Seq, class State, class F>
    using iter_foldl_t = iter_foldl_if_t<Seq, State, F>;
    
    
    template <class Seq, class State, class StateOp>
    using iter_foldr = iter_foldr_if<Seq, State, StateOp>;
    
    template <class Seq, class State, class StateOp>
    using iter_foldr_t = iter_foldr_if_t<Seq, State, StateOp>;
    
  }                                                         // namespace mp
}                                                           // namespace elib
#endif /* ELIB_MP_ALGORITHM_ITER_FOLDL_HPP */
