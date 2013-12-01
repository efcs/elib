#ifndef ELIB_MP_LOWER_BOUND_HPP
#define ELIB_MP_LOWER_BOUND_HPP

# include <elib/mp/algorithm_fwd.hpp>
# include <elib/mp/comparison.hpp>
# include <elib/mp/placeholders.hpp>

namespace elib
{
  namespace mp
  {

    //TODO
    template <class Seq, class T, class Pred = less<_1, _2>>
    struct lower_bound;
    
    
    template <class Seq, class T, class Pred>
    using lower_bound_t = typename lower_bound<Seq, T, Pred>::type;
  

  }                                                         // namespace mp
}                                                           // namespace elib
#endif /* ELIB_MP_LOWER_BOUND_HPP */