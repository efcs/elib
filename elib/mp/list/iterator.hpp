#ifndef ELIB_MP_LIST_ITERATOR_HPP
#define ELIB_MP_LIST_ITERATOR_HPP

# include <elib/mp/list/fwd.hpp>
# include <elib/mp/list/list.hpp>
# include <elib/mp/iterator.hpp>
# include <elib/mp/get_impl.hpp>

namespace elib 
{
  namespace mp
  {
    
    template <class List>
    struct list_iterator
    {
      using category = forward_iterator_tag;
      using type = list_iterator;
      using item = List;
    };
  
    
    template <class List>
    struct get_impl< list_iterator<List> >
    {
      using type = detail::list_iterator_intrinsics;
    };
  
  }                                                         // namespace mp
}                                                           // namespace elib
#endif /* ELIB_MP_LIST_ITERATOR_HPP */