#ifndef ELIB_MP_PAIR_HPP
#define ELIB_MP_PAIR_HPP

namespace elib 
{
  namespace mp
  {
    
    template <class T1, class T2>
    struct pair
    {
      using type = pair;
      using first = T1;
      using second = T2;
    };
    
  //-------------------------------- first ----------------------------------// 
    
    template <class Pair>
    struct first
    {
      using type = typename Pair::first;
    };
    
    template <class Pair>
    using first_t = typename Pair::first;
    
  //-------------------------------- second ---------------------------------//
  
    template <class Pair>
    struct second
    {
      using type = typename Pair::second;
    };
    
    template <class Pair>
    using second_t = typename Pair::second;
  
    
  }                                                         // namespace mp
}                                                           // namespace elib
#endif /* ELIB_MP_PAIR_HPP */