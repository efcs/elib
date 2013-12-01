#ifndef ELIB_MP_MIN_MAX_ELEMENT_HPP
#define ELIB_MP_MIN_MAX_ELEMENT_HPP

# include <elib/mp/algorithm_fwd.hpp>

namespace elib
{
  namespace mp
  {

  //-------------------------------- min_element ----------------------------// 
    
    //TODO
    template <class Seq, class Pred=less<_1, _2>>
    struct min_element;
    
    template <class Seq, class Pred>
    using min_element_t = typename min_element<Seq, Pred>::type;
    
  //-------------------------------- max_element ----------------------------// 
  
    //TODO
    template <class Seq, class Pred=less<_1, _2>>
    struct max_element;
    
    template <class Seq, class Pred>
    using max_element_t = typename max_element<Seq, Pred>::type;

  }                                                         // namespace mp
}                                                           // namespace elib
#endif /* ELIB_MP_MIN_MAX_ELEMENT_HPP */