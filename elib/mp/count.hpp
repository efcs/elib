#ifndef ELIB_MP_COUNT_HPP
#define ELIB_MP_COUNT_HPP

# include <elib/mp/algorithm_fwd.hpp>

namespace elib
{
  namespace mp
  {
    
  //-------------------------------- count --------------------------------// 

    //TODO
    template <class Seq, class T>
    struct count;
    
    template <class Seq, class T>
    using count_t = typename count<Seq, T>::type;
    
  //-------------------------------- count_if --------------------------------// 
    
    template <class Seq, class Pred> 
    struct count_if;
    
    template <class Seq, class Pred>
    using count_if_t = typename count_if<Seq, Pred>::type;
  }                                                         // namespace mp
}                                                           // namespace elib
#endif /* ELIB_MP_COUNT_HPP */