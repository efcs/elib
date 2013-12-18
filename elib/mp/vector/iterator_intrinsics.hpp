#ifndef ELIB_MP_VECTOR_ITERATOR_INTRINSICS_HPP
#define ELIB_MP_VECTOR_ITERATOR_INTRINSICS_HPP

# include <elib/mp/vector/fwd.hpp>
# include <elib/mp/vector/vector.hpp>
# include <elib/mp/vector/item.hpp>
# include <elib/mp/vector/iterator.hpp>
# include <elib/mp/vector/intrinsics.hpp>
# include <elib/mp/iterator.hpp>
# include <cstddef>

namespace elib 
{
  namespace mp
  {
    namespace detail
    {
      
      struct vector_iterator_intrinsics
      {
        
        template <class Iter> struct deref;
        template <class Iter> struct next;
        template <class Iter> struct prior;
        template <class Iter, class N> struct advance;
        template <class Iter, long N> struct advance_c;
        template <class First, class Last> struct distance;
        
        
        template <class Vector, std::size_t N>
        struct deref< vector_iterator<Vector, N> >
        {
          using type = typename at_c<Vector, N>::type;
        };
        
        
        template <class Vector, std::size_t N>
        struct next< vector_iterator<Vector, N> >
        {
          using type = vector_iterator<Vector, N + 1>;
        };
        
        
        template <class Vector, std::size_t N>
        struct prior< vector_iterator<Vector, N> >
        {
          using type = vector_iterator<Vector, N - 1>;
        };
        
        
        template <class Iter, class N> 
        struct advance : advance_c<Iter, N::type::value>
        {};
        
        
        template <class Vector, std::size_t N, long Delta>
        struct advance_c< vector_iterator<Vector, N>, Delta >
        {
          // TODO Wrong conversion ranking? 
          using type = vector_iterator<Vector, N + Delta>;
        };
        
        
        template <
            class Left, std::size_t LeftPos
          , class Right, std::size_t RightPos
          >
        struct distance< 
            vector_iterator<Left, LeftPos>
          , vector_iterator<Right, RightPos>
          > 
            : long_<static_cast<long>(RightPos - LeftPos)>
        {};
      
      };                                   // struct vector_iterator_intrinsics
      
      
    }                                                       // namespace detail
  }                                                         // namespace mp
}                                                           // namespace elib
#endif /* ELIB_MP_VECTOR_ITERATOR_INTRINSICS_HPP */