#ifndef ELIB_MP_ITERATOR_RANGE_HPP
#define ELIB_MP_ITERATOR_RANGE_HPP

# include <elib/mp/intrinsic/sequence_tag.hpp>

namespace elib
{
  namespace mp
  {
    
    namespace detail
    {
      struct iterator_range_tag {};
    }
    
    template <class First, class Last>
    struct iterator_range
    {
      using type = iterator_range;
      using tag = detail::iterator_range_tag;
      using begin = First;
      using end = Last;
    };
    
  }                                                         //namespace mp
}                                                           //namespace elib
#endif /* ELIB_MP_ITERATOR_RANGE_HPP */