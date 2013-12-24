#ifndef ELIB_MP_VARIADIC_SEQUENCE_INTRINSICS_HPP
#define ELIB_MP_VARIADIC_SEQUENCE_INTRINSICS_HPP

# include <elib/mp/variadic/fwd.hpp>
# include <elib/mp/variadic/sequence_iterator.hpp>
# include <elib/mp/variadic/fill_variadic.hpp>
# include <elib/mp/variadic/detail/at_impl.hpp>
# include <elib/mp/variadic/detail/drop_impl.hpp>
# include <elib/mp/variadic/detail/take_impl.hpp>
# include <elib/mp/variadic/detail/join_impl.hpp>
# include <elib/mp/variadic/detail/append_impl.hpp>
# include <elib/mp/variadic/detail/prepend_impl.hpp>
# include <elib/mp/integral_constant.hpp>
# include <elib/mp/identity.hpp>
# include <elib/mp/sequence.hpp>
# include <cstddef>

namespace elib 
{
  namespace mp
  {
    
    template <template <class, std::size_t> class IteratorType>
    struct variadic_sequence_intrinsics
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
      using begin = IteratorType<S, 0>;
      
      
      template <class S>
      using end = IteratorType<S, sequence_size<S>::type::value>;
      
    //-------------------------------- at -----------------------------------// 
      
      template <class S, std::size_t N> struct at_c;
      
      template <template <class...> class S, class ...Args, std::size_t N>
      struct at_c< S<Args...>, N> 
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
      struct clear< S<Args...> > : identity<S<>>
      {};
      
    //-------------------------------- push & pop back ----------------------// 
      
      template <class S, class T>
      using push_back = detail::variadic_append_impl<S, T>;
      
      template <class S>
      using pop_back = 
        detail::variadic_take_impl<
            typename clear<S>::type
          , S
          , sequence_size<S>::type::value - 1
        >;
      
    //-------------------------------- push & pop front ---------------------//
    
      template <class S, class T>
      using push_front = detail::variadic_prepend_impl<S, T>;
      
      
      template <class S> struct pop_front;
      
      
      template <template <class...> class S, class First, class ...Rest>
      struct pop_front< S<First, Rest...> > : identity< S<Rest...> >
      {};
      
    //------------------------ take & drop & slice --------------------------// 
    
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
      
      
      template <class Seq, std::size_t First, std::size_t Last>
      using slice = 
        take<
            typename drop<Seq, First>::type
          , Last - First
        >;
      
      
    //------------------------ join & append & prepend ----------------------// 
    
      template <class Left, class Right>
      using join = detail::variadic_join_impl<Left, Right>;
    
      template <class S, class ...Args>
      using append = detail::variadic_append_impl<S, Args...>;
      
      template <class S, class ...Args>
      using prepend = detail::variadic_prepend_impl<S, Args...>;
      
    };                                                      // variadic_sequence_intrinsics
    
  }                                                         // namespace mp
}                                                           // namespace elib
#endif /* ELIB_MP_VARIADIC_SEQUENCE_INTRINSICS_HPP */