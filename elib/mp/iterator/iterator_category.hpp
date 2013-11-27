#ifndef ELIB_MP_ITERATOR_ITERATOR_CATEGORY_HPP
#define ELIB_MP_ITERATOR_ITERATOR_CATEGORY_HPP

# include <elib/mp/iterator/iterator_fwd.hpp>

namespace elib
{
  namespace mp
  {
  //-------------------------------- iterator_category ----------------------// 
    
    template <class Iter>
    struct iterator_category
    { using type = typename Iter::category; };
    
    
    template <class Iter>
    using iterator_category_t = typename iterator_category<Iter>::type;
    
  }                                                         // namespace mp
}                                                           // namespace elib
#endif /* ELIB_MP_ITERATOR_ITERATOR_CATEGORY_HPP */