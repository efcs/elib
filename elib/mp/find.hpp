#ifndef ELIB_MP_FIND_HPP
#define ELIB_MP_FIND_HPP

# include <elib/mp/algorithm_fwd.hpp>

namespace elib
{
  namespace mp
  {

  //-------------------------------- find --------------------------------// 
  
    //TODO
    template <class Seq, class T>
    struct find;
    
    template <class Seq, class T>
    using find_t = typename find<Seq, T>::type;
    
  //-------------------------------- find_if --------------------------------// 
  
    //TODO
    template <class Seq, class Pred>
    struct find_if;
    
    template <class Seq, class Pred>
    using find_if_t = typename find_if<Seq, Pred>::type;

  }                                                         // namespace mp
}                                                           // namespace elib
#endif /* ELIB_MP_FIND_HPP */