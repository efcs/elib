#ifndef ELIB_MP_LIST_INTRINSICS_HPP
#define ELIB_MP_LIST_INTRINSICS_HPP

# include <elib/mp/list/fwd.hpp>
# include <elib/mp/list/list.hpp>
# include <elib/mp/list/iterator.hpp>
# include <elib/mp/optimization.hpp>

namespace elib 
{
  namespace mp
  {
    namespace detail
    {
      
      struct list_intrinsics
      {
        
        // fwd
        template <class List> struct begin;
        template <class List> struct end;
        template <class List> struct size;
        template <class List> struct empty;
        template <class List> struct front;
        //TODO
        // template <...> struct insert;
        // template <...> struct insert_range;
        // template <...> struct erase;
        template <class List> struct clear;
        template <class List, class T> struct push_front;
        template <class List> struct pop_front;
        
        // optimizations
        using O1_SIZE_OPTIMIZATION = optimization_tag;
        
        // impl
        
        template <class List> 
        struct begin
        {
          using type = list_iterator<List>;
        };
        
        template <class List>
        struct end
        {
          using type = list_iterator< list<> >;
        };
        
        template <class ...Args>
        struct size< list<Args...> >
        {
          using type = size_type<sizeof...(Args)>;
        };
        
        template <class ...Args>
        struct empty< list<Args...> >
        {
          using type = bool_< (sizeof...(Args) == 0) >;
        };
        
        template <class List>
        struct front
        {
          using type = typename List::item;
        };
        
        template <class List>
        struct clear
        {
          using type = list<>;
        };
        
        template <class ...ListArgs, class T>
        struct push_front< list<ListArgs...>, T >
        {
          using type = list<T, ListArgs...>;
        };
        
        template <class List>
        struct pop_front
        {
          using type = typename List::next;
        };
        
        
      };                                              // struct list_intrinsics
      
    }                                                       // namespace detail
  }                                                         // namespace mp
}                                                           // namespace elib
#endif /* ELIB_MP_LIST_INTRINSICS_HPP */