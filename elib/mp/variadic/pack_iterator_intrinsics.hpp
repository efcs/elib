#ifndef ELIB_MP_VARIADIC_PACK_ITERATOR_INTRINSICS_HPP
#define ELIB_MP_VARIADIC_PACK_ITERATOR_INTRINSICS_HPP

# include <elib/mp/variadic/fwd.hpp>
# include <elib/mp/variadic/pack_iterator.hpp>
# include <elib/mp/variadic/pack_intrinsics.hpp>
# include <elib/mp/pack.hpp>
# include <elib/mp/identity.hpp>
# include <cstddef>

namespace elib 
{
  namespace mp
  {
    
    struct variadic_pack_iterator_intrinsics
    {
      
    //-------------------------------- deref --------------------------------//
    
      template <class Iter> struct deref;
      
      template <template <class, std::size_t> class It, class S, std::size_t N>
      struct deref< It<S, N> > : at_c<S, N>
      {};
      
    //----------------------------- next & prior ----------------------------// 
    
      template <class Iter> struct next;
      template <class Iter> struct prior;
      
      template <template <class, std::size_t> class It, class S, std::size_t N>
      struct next< It<S, N> > : identity< It<S, N + 1> >
      {};
      
      template <template <class, std::size_t> class It, class S, std::size_t N>
      struct prior< It<S, N> > : identity< It<S, N - 1> >
      {};
      
    //-------------------------------- advance ------------------------------// 
      
      template <class It, long long Delta> struct advance_c;
      
      template <template <class, std::size_t> class It
        , class S, std::size_t N
        , long long Delta
        >
      struct advance_c< It<S, N>, Delta > : identity< It<S, N + Delta> >
      {};
      
      
      template <class It, class N>
      using advance = advance_c<It, N::type::value>;
      
    //----------------------------- distance --------------------------------// 
    
      template <class First, class Second> struct distance;
      
      template <
          template <class, std::size_t> class It
        , class SL, std::size_t NL
        , class SR, std::size_t NR
        >
      struct distance< It<SL, NL>, It<SR, NR> >
        : llong_< static_cast<long long>(NR - NL) >
      {};
      
    };                                // variadic_pack_iterator_intrinsics
    
  }                                                         // namespace mp
}                                                           // namespace elib
#endif /* ELIB_MP_VARIADIC_PACK_ITERATOR_INTRINSICS_HPP */