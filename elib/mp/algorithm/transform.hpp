#ifndef ELIB_MP_ALGORITHM_TRANSFORM_HPP
#define ELIB_MP_ALGORITHM_TRANSFORM_HPP

# include <elib/mp/algorithm/algorithm_fwd.hpp>

namespace elib
{
  namespace mp
  {

    //TODO
    // Overload:
    //       <class Seq, class Op, class In = na>
    //       <class Seq1, class Seq2, class BinaryOp, class In = na>
    template <class Seq1, class Seq2, class BinaryOp=na, class In = na>
    struct transform;
  
    //TODO
    template <class Seq1, class Seq2, class BinaryOp=na, class In = na>
    struct reverse_transform;
    
    
  }                                                         // namespace mp
}                                                           // namespace elib
#endif /* ELIB_MP_ALGORITHM_TRANSFORM_HPP */