#ifndef ELIB_MP_ALGORITHM_UPPER_BOUND_HPP
#define ELIB_MP_ALGORITHM_UPPER_BOUND_HPP

# include <elib/mp/algorithm/algorithm_fwd.hpp>
# include <elib/mp/metafunction/comparison.hpp>
# include <elib/mp/metafunction/placeholders.hpp>

namespace elib
{
  namespace mp
  {

    //TODO
    template <class Seq, class T, class Pred=less<_1, _2>>
    struct upper_bound;

  }                                                         // namespace mp
}                                                           // namespace elib
#endif /* ELIB_MP_ALGORITHM_UPPER_BOUND_HPP */