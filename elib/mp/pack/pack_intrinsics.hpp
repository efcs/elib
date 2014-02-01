#ifndef ELIB_MP_PACK_INTRINSICS_HPP
#define ELIB_MP_PACK_INTRINSICS_HPP

# include <elib/mp/identity.hpp>
# include <elib/mp/sequence.hpp>
# include <elib/mp/iterator/default_random_access_iterator.hpp>
# include <elib/aux.hpp>
# include <elib/params.hpp>
# include <cstddef>

namespace elib 
{
  namespace mp
  {
    
    struct pack_intrinsics
    {
      
    //-------------------------- sequence_size -----------------------------// 
      
      template <class S> struct sequence_size;
      
      // type sequence
      template <template <class...> class S, class ...Args>
      struct sequence_size< S<Args...> > : size_type_<sizeof...(Args)>
      {};
      
    //-------------------------------- empty --------------------------------// 
    
      template <class Seq>
      using empty = bool_< sequence_size<Seq>::type::value == 0 >;
      
    //------------------------------ begin & end ----------------------------// 
    
      template <class S>
      using begin = 
        identity<
          default_random_access_iterator<S, 0>
        >;
      
      
      template <class S>
      using end =
        identity<
          default_random_access_iterator<S, sequence_size<S>::type::value>
        >;
      
    //-------------------------------- at -----------------------------------// 
      
      template <class S, class N>
      using at = params::at<S, N::type::value>;
      
      template <class S, std::size_t N>
      using at_c = params::at<S, N>;
      
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
      using push_back = params::append<S, T>;
      
      template <class S>
      using pop_back = 
          params::take<
            S
          , sequence_size<S>::type::value - 1
        >;
      
    //-------------------------------- push & pop front ---------------------//
    
      template <class S, class T>
      using push_front = params::prepend<S, T>;
      
      
      template <class S> struct pop_front;
      
      
      template <template <class...> class S, class First, class ...Rest>
      struct pop_front< S<First, Rest...> > : identity< S<Rest...> >
      {};
      
    //------------------------ take & drop & slice --------------------------// 
    
      template <class S, std::size_t N>
      using take = params::take<S, N>;
      
      template <class S, std::size_t N>
      using drop = params::drop<S, N>;
      
      template <class Seq, std::size_t First, std::size_t Last>
      using slice = params::slice<Seq, First, Last>;
      
    //------------------------ join & append & prepend ----------------------// 
    
      template <class Left, class Right>
      using concat = params::concat<Left, Right>;
    
      template <class S, class ...Args>
      using append = params::append<S, Args...>;
      
      template <class S, class ...Args>
      using prepend = params::prepend<S, Args...>;
      
    };                                                      // pack_intrinsics
    
  }                                                         // namespace mp
}                                                           // namespace elib
#endif /* ELIB_MP_PACK_INTRINSICS_HPP */