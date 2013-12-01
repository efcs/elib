#ifndef ELIB_MP_ACCUMULATE_HPP
#define ELIB_MP_ACCUMULATE_HPP

# include <elib/mp/algorithm_fwd.hpp>
# include <elib/mp/fold.hpp>

namespace elib
{
  namespace mp
  {

    template <class Seq, class State, class ForwardOp>
    struct accumulate : fold<Seq, State, ForwardOp>
    {};
    
    
    template <class Seq, class State, class ForwardOp>
    using accumulate_t = typename accumulate<Seq, State, ForwardOp>::type;

  }                                                         // namespace mp
}                                                           // namespace elib
#endif /* ELIB_MP_ACCUMULATE_HPP */