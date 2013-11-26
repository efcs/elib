#ifndef ELIB_MP_ALGORITHM_EQUAL_HPP
# define ELIB_MP_ALGORITHM_EQUAL_HPP

# include <elib/mp/algorithm/algorithm_fwd.hpp>

namespace elib
{
  namespace mp
  {

    //TODO
    template <class Seq1, class Sep2 
      , class Pred = std::is_same<_1, _2>
    >
    struct equal;

  }                                                         // namespace mp
}                                                           // namespace elib
#endif /* ELIB_MP_ALGORITHM_EQUAL_HPP */