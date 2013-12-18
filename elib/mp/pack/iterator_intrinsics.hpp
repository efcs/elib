#ifndef ELIB_MP_PACK_ITERATOR_INTRINSICS_HPP
#define ELIB_MP_PACK_ITERATOR_INTRINSICS_HPP

# include <elib/mp/pack/fwd.hpp>
# include <elib/mp/pack/iterator.hpp>
# include <elib/mp/pack/pack.hpp>
# include <elib/mp/pack/intrinsics.hpp>
# include <elib/mp/sequence.hpp>
# include <elib/mp/integral_constant.hpp>
# include <cstddef>

namespace elib 
{
  namespace mp
  {
    namespace detail
    {
      
      
      struct pack_iterator_intrinsics
      {
        
        template <class Iter> struct next;
        template <class Iter> struct prior;
        template <class Iter> struct deref;
        template <class Iter, class N> struct advance;
        template <class Iter, long N> struct advance_c;
        template <class First, class Last> struct distance;
        
        template <class Pack, std::size_t Pos>
        struct next< pack_iterator<Pack, Pos> >
        {
          using type = pack_iterator<Pack, Pos+1>;
        };
        
        template <class Pack, std::size_t Pos>
        struct prior< pack_iterator<Pack, Pos> >
        {
          using type = pack_iterator<Pack, Pos-1>;
        };
        
        template <class Pack, std::size_t Pos>
        struct deref< pack_iterator<Pack, Pos> >
        {
          using type = typename at_c<Pack, Pos>::type;
        };
        
        template <class Pack, std::size_t Pos, class N>
        struct advance< pack_iterator<Pack, Pos>, N>
        {
          using type = pack_iterator<Pack, Pos + N::type::value>;
        };
        
        template <class Pack, std::size_t Pos, long N>
        struct advance_c< pack_iterator<Pack, Pos>, N>
        {
          // TODO Wrong conversion ranking for long? 
          using type = pack_iterator<Pack, Pos + N>;
        };
        
        template <
            class LeftPack, std::size_t LeftPos
          , class RightPack, std::size_t RightPos
          >
        struct distance<
            pack_iterator<LeftPack, LeftPos>
          , pack_iterator<RightPack, RightPos>
          >
        {
          using type = long_<static_cast<long>(RightPos - LeftPos)>;
        };
        
      };                                     // struct path_iterator_intrinsics
      
      
    }                                                       // namespace detail
  }                                                         // namespace mp
}                                                           // namespace elib
#endif /* ELIB_MP_PACK_ITERATOR_INTRINSICS_HPP */