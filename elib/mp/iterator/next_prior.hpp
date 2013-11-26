#ifndef ELIB_MP_ITERATOR_NEXT_PRIOR_HPP
#define ELIB_MP_ITERATOR_NEXT_PRIOR_HPP

# include <elib/mp/iterator/iterator_fwd.hpp>

namespace elib
{
  namespace mp
  {
  
    template <class Iter>
    struct next
    {
      using type = typename Iter::next;
    };
      
      
    template <class Iter>
    struct prior
    {
      using type = typename Iter::prior;
    };

  }                                                         // namespace mp
}                                                           // namespace elib
#endif /* ELIB_MP_ITERATOR_NEXT_PRIOR_HPP */