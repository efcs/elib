#ifndef ELIB_MP_ITERATOR_DEREF_HPP
#define ELIB_MP_ITERATOR_DEREF_HPP

# include <elib/mp/iterator/iterator_fwd.hpp>

namespace elib
{
  namespace mp
  {
    
    template <class Iter>
    struct deref
    {
      using type = typename Iter::type;
    };
    
  }                                                         // namespace mp
}                                                           // namespace elib
#endif /* ELIB_MP_ITERATOR_DEREF_HPP */