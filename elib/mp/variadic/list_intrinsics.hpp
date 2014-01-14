#ifndef ELIB_MP_VARIADIC_LIST_INTRINSICS_HPP
#define ELIB_MP_VARIADIC_LIST_INTRINSICS_HPP

# include <elib/mp/variadic/fwd.hpp>
# include <elib/mp/variadic/append.hpp>
# include <elib/mp/variadic/concat.hpp>
# include <elib/mp/variadic/drop.hpp>
# include <elib/mp/variadic/fill.hpp>
# include <elib/mp/variadic/list_iterator.hpp>
# include <elib/mp/variadic/prepend.hpp>
# include <elib/mp/sequence.hpp>
# include <elib/mp/identity.hpp>
# include <elib/mp/iterator.hpp>
# include <elib/mp/integral_constant.hpp>
# include <cstddef>

namespace elib 
{
  namespace mp
  {
    
    template <template <class...> class IteratorType>
    struct variadic_list_intrinsics
    {
      
      template <class List, class N> 
      using at = variadic_at<List, N::type::value>;
      
      template <class List, class N>
      using at_t = typename variadic_at<List, N::type::value>::type;
      
      template <class List, std::size_t N>
      using at_c = variadic_at<List, N>;
      
      template <class List, std::size_t N>
      using at_c_t = typename variadic_at<List, N>::type;
      
    //-------------------------------- size --------------------------------// 
      
      template <class List> struct sequence_size;
      
      template <template <class...> class List, class ...Args>
      struct sequence_size< List<Args...> > : size_type< sizeof...(Args) >
      {};
      
    //-------------------------------- empty --------------------------------// 
      
      template <class List>
      using empty = bool_< sequence_size<List>::type::value == 0 >;
      
    //----------------------------- begin end--------------------------------// 
    
      template <class List> struct begin;
      
      template <template <class...> class List, class ...Args>
      struct begin< List<Args...> > 
        : identity< IteratorType<Args...> >
      {};

      
      template <class List>
      using end = 
        identity< 
          IteratorType<>
        >;
      
    //-------------------------------- front --------------------------------// 
    
      template <class List> struct front;
      
      template <template <class...> class List, class First, class ...Rest>
      struct front< List<First, Rest...> > : identity<First>
      {};
      
    //-------------------------------- clear --------------------------------// 
    
      template <class List> struct clear;
      
      template <template <class...> class List, class ...Args>
      struct clear< List<Args...> > : identity< List<> >
      {};
      
    //-------------------------------- push pop front -----------------------// 
    
      template <class List, class T> struct push_front;
      template <class List> struct pop_front;
      
      template <template <class...> class List, class ...Args, class T>
      struct push_front< List<Args...>, T> : identity< List<T, Args...> >
      {};
      
      template <template <class...> class List, class First, class ...Rest>
      struct pop_front< List<First, Rest...> > : identity< List<Rest...> >
      {};
      
    //-------------------------------- push_back ----------------------------// 
      // no pop_back is given since it is O(n) and variadic list
      // operators should be O(1)
      template <class List, class T> struct push_back;
      
      template <template <class...> class List, class ...Args, class T>
      struct push_back< List<Args...>, T > : identity< List<Args..., T> >
      {};
      
    //-------------------------------- drop --------------------------------// 
    
      template <class List, std::size_t N>
      using drop = variadic_drop<List, N>;
      
    //---------------------- join append prepend ----------------------------// 
    
      template <class Left, class Right>
      using concat = variadic_concat<Left, Right>;
      
      template <class List, class ...Args>
      using append = variadic_append<List, Args...>;
      
      template <class List, class ...Args>
      using prepend = variadic_prepend<List, Args...>;
      
    };                                                      // variadic_list_intrinsics
    
  }                                                         // namespace mp
}                                                           // namespace elib
#endif /* ELIB_MP_VARIADIC_LIST_INTRINSICS_HPP */