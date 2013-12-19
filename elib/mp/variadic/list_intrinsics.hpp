#ifndef ELIB_MP_VARIADIC_LIST_INTRINSICS_HPP
#define ELIB_MP_VARIADIC_LIST_INTRINSICS_HPP

# include <elib/mp/variadic/fwd.hpp>
# include <elib/mp/variadic/list_iterator.hpp>
# include <elib/mp/variadic/fill_variadic.hpp>
# include <elib/mp/variadic/detail/drop_impl.hpp>
# include <elib/mp/variadic/detail/join_impl.hpp>
# include <elib/mp/variadic/detail/append_impl.hpp>
# include <elib/mp/variadic/detail/prepend_impl.hpp>
# include <elib/mp/sequence.hpp>
# include <elib/mp/identity.hpp>
# include <elib/mp/integral_constant.hpp>
# include <cstddef>

namespace elib 
{
  namespace mp
  {
    
    template <template <class...> class IteratorType>
    struct variadic_list_intrinsics
    {
      
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
      using end = IteratorType<>;
      
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
    
      template <class List, std::size_t N> struct drop;
      
      template <template <class...> class List, class ...Args, std::size_t N>
      struct drop< List<Args...>, N> 
      {
        using type = decltype(
          detail::variadic_drop_impl< fill_variadic_t<List, decltype(nullptr), N> >
            ::eval((identity<Args>*)nullptr...)
        );
      };
      
    //---------------------- join append prepend ----------------------------// 
    
      template <class Left, class Right>
      using join = detail::variadic_join_impl<Left, Right>;
      
      template <class List, class ...Args>
      using append = detail::variadic_append_impl<List, Args...>;
      
      template <class List, class ...Args>
      using prepend = detail::variadic_prepend_impl<List, Args...>;
      
    };                                                      // variadic_list_intrinsics
    
  }                                                         // namespace mp
}                                                           // namespace elib
#endif /* ELIB_MP_VARIADIC_LIST_INTRINSICS_HPP */