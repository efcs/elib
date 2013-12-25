#ifndef ELIB_MP_ALGORITHM_INSERTER_HPP
#define ELIB_MP_ALGORITHM_INSERTER_HPP

# include <elib/mp/arg.hpp>
# include <elib/mp/sequence.hpp>

namespace elib 
{
  namespace mp
  {
    
    template <class State, class Op>
    struct inserter
    {
      using state = State;
      using operation = Op;
    };
    
    
    template <class Seq>
    struct back_inserter 
      : inserter<Seq, push_back<_1, _2>>
    {};
    
    
    template <class Seq>
    struct front_inserter
      : inserter<Seq, push_front<_1, _2>>
    {};
    
  }                                                         // namespace mp
}                                                           // namespace elib
#endif /* ELIB_MP_ALGORITHM_INSERTER_HPP */
