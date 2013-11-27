#ifndef ELIB_MP_ALGORITHM_ACCUMULATE_HPP
#define ELIB_MP_ALGORITHM_ACCUMULATE_HPP

# include <elib/mp/algorithm/algorithm_fwd.hpp>
# include <elib/mp/algorithm/fold.hpp>

namespace elib
{
  namespace mp
  {

    template <class Seq, class State, class ForwardOp>
    struct accumulate : fold<Seq, State, ForwardOp>
    {};

  }                                                         // namespace mp
}                                                           // namespace elib
#endif /* ELIB_MP_ALGORITHM_ACCUMULATE_HPP */