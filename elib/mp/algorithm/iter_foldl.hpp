#ifndef ELIB_MP_ALGORITHM_ITER_FOLDL_HPP
#define ELIB_MP_ALGORITHM_ITER_FOLDL_HPP

# include <elib/mp/always.hpp>
# include <elib/mp/algorithm/iter_fold_if.hpp>

namespace elib 
{
  namespace mp
  {
    
    template <class Seq, class State, class F>
    using iter_foldl = iter_foldl_if<Seq, State, F>;
      
      
    template <class Seq, class State, class F>
    using iter_foldl_t = typename iter_foldl_if<Seq, State, F>::type;
    
  }                                                         // namespace mp
}                                                           // namespace elib
#endif /* ELIB_MP_ALGORITHM_ITER_FOLDL_HPP */
