#ifndef ELIB_MP_VARIADIC_INTRINSICS_HPP
#define ELIB_MP_VARIADIC_INTRINSICS_HPP

# include <elib/mp/variadic/fwd.hpp>
# include <elib/mp/variadic/iterator.hpp>
# include <elib/mp/variadic/fill_variadic.hpp>
# include <elib/mp/variadic/at_impl.hpp>
# include <elib/mp/variadic/drop_impl.hpp>
# include <elib/mp/variadic/take_impl.hpp>
# include <elib/mp/variadic/join_impl.hpp>
# include <elib/mp/variadic/append_impl.hpp>
# include <elib/mp/variadic/prepend_impl.hpp>
# include <elib/mp/integral_constant.hpp>
# include <elib/mp/identity.hpp>
# include <elib/mp/sequence.hpp>
# include <cstddef>

namespace elib 
{
  namespace mp
  {
    
    struct variadic_intrinsics
    {
      
    //-------------------------- sequence_size -----------------------------// 
      
      template <class S> struct sequence_size;
      
      // type sequence
      template <template <class...> class S, class ...Args>
      struct sequence_size< S<Args...> > : size_type<sizeof...(Args)>
      {};
      
    //-------------------------------- empty --------------------------------// 
    
      template <class Seq>
      using empty = bool_< sequence_size<Seq>::type::value == 0 >;
      
    //------------------------------ begin & end ----------------------------// 
    
      template <class S>
      using begin = variadic_iterator<S, 0>;
      
      
      template <class S>
      using end = variadic_iterator<S, sequence_size<S>::type::value>;
      
    //-------------------------------- at -----------------------------------// 
      
      template <class S, std::size_t N> struct at_c;
      
      template <template <class...> class S, class ...Args, std::size_t N>
      struct at_c 
      {
        using type = decltype(
          detail::variadic_at_impl< 
            fill_variadic_t<S, decltype(nullptr), N>
          >::eval((identity<Args>*)nullptr...)
        );
      };
      
      template <class Seq, class N>
      using at = at_c<Seq, N::type::value>;
      
      
    //-------------------------------- front --------------------------------//
    
      template <class S> struct front;
    
      template <template <class...> class S, class First, class ...Rest>
      struct front< S<First, Rest...> > : identity<First>
      {};
      
    //-------------------------------- back ---------------------------------// 
      
      template <class S>
      using back = at_c<S, sequence_size<S>::type::value - 1>;
      
      
    //-------------------------------- clear --------------------------------// 
    
      template <class S> struct clear;
    
      template <template <class...> class S, class ...Args>
      struct clear : identity<S<>>
      {};
      
    //-------------------------------- push & pop back ----------------------// 
      
      template <class S, class T>
      using push_back = detail::variadic_append_impl<S, T>;
      
      template <class S>
      using pop_back = 
        detail::variadic_take_impl<S, sequence_size<S>::type::value - 1>;
      
    //-------------------------------- push & pop front ---------------------//
    
      template <class S, class T>
      using push_front = detail::variadic_prepend<S, T>;
      
      
      template <class S> struct pop_front;
      
      
      template <template <class...> class S, class First, class ...Rest>
      struct pop_front< S<First, Rest...> > : identity< S<Rest...> >
      {};
      
    //-------------------------------- take & drop --------------------------// 
    
      template <class S, std::size_t N>
      using take = detail::variadic_take_impl<typename clear<S>::type, S, N>;
      
      
      template <class S, std::size_t N> struct drop;
      
      
      template <template <class...> class S, class ...Args, std::size_t N>
      struct drop<S<Args...>, N>
      {
        using type = decltype(
          detail::variadic_drop_impl< fill_variadic_t<S, decltype(nullptr), N> >
            ::eval((identity<Args>*)nullptr...)
        );
      };
      
    //------------------------ join & append & prepend ----------------------// 
    
      template <class Left, class Right>
      using join = detail::variadic_join_impl<Left, Right>;
    
      template <class S, class ...Args>
      using append = detail::variadic_append_impl<S, Args...>;
      
      template <class S, class ...Args>
      using prepend = detail::variadic_prepend_impl<S, Args...>;
      
    };                                                      // variadic_intrinsics
    
  }                                                         // namespace mp
}                                                           // namespace elib
#endif /* ELIB_MP_VARIADIC_INTRINSICS_HPP */