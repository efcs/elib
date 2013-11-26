#ifndef ELIB_MP_ALGORITHM_FOR_EACH_HPP
# define ELIB_MP_ALGORITHM_FOR_EACH_HPP

# include <elib/mp/algorithm/algorithm_fwd.hpp>

namespace elib
{
  namespace mp
  {

    //TODO
    template <class Seq, class F>
    void for_each(F f);
    
    //TODO
    template <class Seq, class TransformOp, class F>
    void for_each(F f);

  }                                                         // namespace mp
}                                                           // namespace elib
#endif /* ELIB_MP_ALGORITHM_FOR_EACH_HPP */