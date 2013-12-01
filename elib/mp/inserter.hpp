#ifndef ELIB_MP_INSERTER_HPP
#define ELIB_MP_INSERTER_HPP

# include <elib/mp/algorithm_fwd.hpp>
# include <elib/mp/intrinsic/push_front.hpp>
# include <elib/mp/intrinsic/push_back.hpp>
# include <elib/mp/placeholders.hpp>

namespace elib
{
  namespace mp
  {

  //-------------------------------- inserter -------------------------------// 
    
    template <class State, class Op>
    struct inserter
    {
      using state = State;
      using operation = Op;
    };
  
  //-------------------------------- front_inserter -------------------------// 
    
    template <class Seq>
    struct front_inserter : inserter<Seq, push_front<_1, _2>>
    {};
    
  //-------------------------------- back_inserter --------------------------// 
    
    template <class Seq>
    struct back_inserter : inserter<Seq, push_back<_1, _2>>
    {};

  }                                                         // namespace mp
}                                                           // namespace elib
#endif /* ELIB_MP_INSERTER_HPP */