#ifndef ELIB_MP_LIST_LIST_ITERATOR_HPP
#define ELIB_MP_LIST_LIST_ITERATOR_HPP

# include <elib/mp/iterator.hpp>
# include <elib/mp/get_impl.hpp>

namespace elib 
{
  namespace mp
  {
    
    struct list_iterator_intrinsics;
    
    template <class ...Args> 
    struct list_iterator
    {
      using model_type = model::forward_iterator;
    };
    
    
    template <class ...Args>
    struct get_impl< list_iterator<Args...> >
    {
      using type = list_iterator_intrinsics;
    };
  }                                                         // namespace mp
}                                                           // namespace elib
#endif /* ELIB_MP_LIST_LIST_ITERATOR_HPP */