#ifndef ELIB_MP_VARIADIC_LIST_ITERATOR_HPP
#define ELIB_MP_VARIADIC_LIST_ITERATOR_HPP

# include <elib/mp/variadic/fwd.hpp>
# include <elib/mp/iterator.hpp>
# include <elib/mp/get_impl.hpp>

namespace elib 
{
  namespace mp
  {
    
    template <class ...Args> 
    struct variadic_list_iterator
    {
      using model_type = model::forward_iterator;
    };
    
    
    template <class ...Args>
    struct get_impl< variadic_list_iterator<Args...> >
    {
      using type = variadic_list_iterator_intrinsics;
    };
  }                                                         // namespace mp
}                                                           // namespace elib
#endif /* ELIB_MP_VARIADIC_LIST_ITERATOR_HPP */