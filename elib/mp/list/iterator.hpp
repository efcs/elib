#ifndef ELIB_MP_LIST_ITERATOR_HPP
#define ELIB_MP_LIST_ITERATOR_HPP

# include <elib/mp/list/fwd.hpp>
# include <elib/mp/list/list.hpp>
# include <elib/mp/get_impl.hpp>

namespace elib 
{
  namespace mp
  {
    
    
    template <class List>
    struct list_iterator {};
    
    
    template <class List>
    struct get_impl< list_iterator<List> >
    {
      using type = detail::list_iterator_intrinsics;
    };
    
    
    namespace detail
    {
      
      struct list_iterator_intrinsics
      {
        // fwd
        //template <class Iter, class N> struct advance;
        //template <class First, class Last> struct distance;
        template <class Iter> struct next;
        template <class Iter> struct deref;
        template <class Iter> struct iterator_category;
        
        template <class List>
        struct next< list_iterator<List> >
        {
          using type = list_iterator<typename List::next>;
        };
        
        template <class List>
        struct deref< list_iterator<List> >
        {
          using type = typename List::item;
        };
        
        template <class Iter>
        struct iterator_category
        {
          using type = forward_iterator_tag;
        };
        
      };                                     // struct list_iterator_intrinsics

    }                                                       // namespace detail
  }                                                         // namespace mp
}                                                           // namespace elib
#endif /* ELIB_MP_LIST_ITERATOR_HPP */