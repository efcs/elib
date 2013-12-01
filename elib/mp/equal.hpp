#ifndef ELIB_MP_EQUAL_HPP
#define ELIB_MP_EQUAL_HPP

# include <elib/mp/algorithm_fwd.hpp>
# include <elib/mp/placeholders.hpp>
# include <elib/mp/integral_constant.hpp>

namespace elib
{
  namespace mp
  {
    
    //TODO
    template <class Seq1, class Sep2 
      , class Pred = std::is_same<_1, _2>
    >
    struct equal;
    
    template <class Seq1, class Seq2, class Pred>
    using equal_t = typename equal<Seq1, Seq2, Pred>::type;

  }                                                         // namespace mp
}                                                           // namespace elib
#endif /* ELIB_MP_EQUAL_HPP */