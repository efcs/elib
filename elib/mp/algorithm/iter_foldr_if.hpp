#ifndef ELIB_MP_ALGORITHM_ITER_FOLDR_IF_HPP
#define ELIB_MP_ALGORITHM_ITER_FOLDR_IF_HPP

# include <elib/mp/apply_wrap.hpp>
# include <elib/mp/always.hpp>
# include <elib/mp/sequence.hpp>
# include <elib/mp/iterator.hpp>
# include <elib/mp/logical.hpp>
# include <elib/mp/same_type.hpp>
# include <elib/mp/lambda.hpp>
# include <elib/aux.hpp>

namespace elib 
{
  namespace mp
  {
    
    
    template <class Seq, class State, class F, class Pred = always_true>
    struct iter_foldr_if_impl<>
    
  }                                                         // namespace mp
}                                                           // namespace elib
#endif /* ELIB_MP_ALGORITHM_ITER_FOLDR_IF_HPP */