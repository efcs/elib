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
    
  }                                                         // namespace mp
}                                                           // namespace elib
#endif /* ELIB_MP_PAIR_HPP */