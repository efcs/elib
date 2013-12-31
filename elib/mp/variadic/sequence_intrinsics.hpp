#ifndef ELIB_MP_VARIADIC_SEQUENCE_INTRINSICS_HPP
#define ELIB_MP_VARIADIC_SEQUENCE_INTRINSICS_HPP

# include <elib/mp/variadic/fwd.hpp>
# include <elib/mp/variadic/append.hpp>
# include <elib/mp/variadic/at.hpp>
# include <elib/mp/variadic/drop.hpp>
# include <elib/mp/variadic/prepend.hpp>
# include <elib/mp/variadic/slice.hpp>
# include <elib/mp/variadic/take.hpp>
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
      
      template <class S, class N>
      using at = variadic_at<S, N::type::value>;
      
      template <class S, std::size_t N>
      using at_c = variadic_at<S, N>;
      
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
      using push_back = variadic_append<S, T>;
      
      template <class S>
      using pop_back = 
          variadic_take<
            S
          , sequence_size<S>::type::value - 1
        >;
      
    //-------------------------------- push & pop front ---------------------//
    
      template <class S, class T>
      using push_front = variadic_prepend<S, T>;
      
      
      template <class S> struct pop_front;
      
      
      template <template <class...> class S, class First, class ...Rest>
      struct pop_front< S<First, Rest...> > : identity< S<Rest...> >
      {};
      
    //------------------------ take & drop & slice --------------------------// 
    
      template <class S, std::size_t N>
      using take = variadic_take<S, N>;
      
      template <class S, std::size_t N>
      using drop = variadic_drop<S, N>;
      
      template <class Seq, std::size_t First, std::size_t Last>
      using slice = variadic_slice<Seq, First, Last>;
      
    //------------------------ join & append & prepend ----------------------// 
    
      template <class Left, class Right>
      using join = variadic_join<Left, Right>;
    
      template <class S, class ...Args>
      using append = variadic_append<S, Args...>;
      
      template <class S, class ...Args>
      using prepend = variadic_prepend<S, Args...>;
      
    };                                                      // variadic_sequence_intrinsics
    
  }                                                         // namespace mp
}                                                           // namespace elib
#endif /* ELIB_MP_VARIADIC_SEQUENCE_INTRINSICS_HPP */