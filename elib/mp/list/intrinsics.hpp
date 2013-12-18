#ifndef ELIB_MP_LIST_INTRINSICS_HPP
#define ELIB_MP_LIST_INTRINSICS_HPP

# include <elib/mp/list/fwd.hpp>
# include <elib/mp/list/list.hpp>
# include <elib/mp/list/iterator.hpp>
# include <elib/mp/sequence.hpp>
# include <elib/mp/integral_constant.hpp>

namespace elib 
{
  namespace mp
  {
    namespace detail
    {
      
      struct list_intrinsics
      {
        template <class S> struct front;
        template <class S> struct sequence_size;
        template <class S> struct empty;
        //template <class S> struct begin;
        //template <class S> struct end;
        //template <class S> struct clear;
        template <class S, class T> struct push_front;
        template <class S> struct pop_front;
        
        template <class First, class ...Rest>
        struct front< list<First, Rest...> >
        {
          using type = First;
        };
        
        template <class ...Args>
        struct sequence_size< list<Args...> > 
          : size_type<sizeof...(Args)>
        {};
        
        template <class List>
        using O1_size = sequence_size<List>;
        
        template <class ...Args>
        struct empty< list<Args...> >
          : bool_<sizeof...(Args) == 0>
        {};
        
        template <class List>
        using begin = list_iterator<List>;
        
        template <class List>
        using end = list_iterator<list<>>;
        
        template <class>
        using clear = list<>;
        
        template <class ...Args, class T>
        struct push_front< list<Args...>, T>
        {
          using type = list<T, Args...>;
        };
        
        template <class First, class ...Rest>
        struct pop_front< list<First, Rest...> >
        {
          using type = list<Rest...>;
        };
        
        
      };                                              // struct list_intrinsics
      
    }                                                       // namespace detail
  }                                                         // namespace mp
}                                                           // namespace elib
#endif /* ELIB_MP_LIST_INTRINSICS_HPP */