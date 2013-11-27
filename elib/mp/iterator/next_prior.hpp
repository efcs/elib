#ifndef ELIB_MP_ITERATOR_NEXT_PRIOR_HPP
#define ELIB_MP_ITERATOR_NEXT_PRIOR_HPP

# include <elib/mp/iterator/iterator_fwd.hpp>

namespace elib
{
  namespace mp
  {
  //-------------------------------- next -----------------------------------// 
    
    template <class Iter>
    struct next
    { using type = typename Iter::next; };
    
    
    template <class Iter>
    using next_t = typename next<Iter>::type;
      
  //-------------------------------- prior ----------------------------------// 
    
    template <class Iter>
    struct prior
    { using type = typename Iter::prior; };
    
    
    template <class Iter>
    using prior_t = typename prior<Iter>::type;

  }                                                         // namespace mp
}                                                           // namespace elib
#endif /* ELIB_MP_ITERATOR_NEXT_PRIOR_HPP */