#ifndef ELIB_MP_ITERATOR_DEFAULT_RANDOM_ACCESS_ITERATOR_INTRINSICS_HPP
#define ELIB_MP_ITERATOR_DEFAULT_RANDOM_ACCESS_ITERATOR_INTRINSICS_HPP

# include <elib/mp/iterator/fwd.hpp>
# include <elib/mp/iterator/iterator.hpp>
# include <elib/mp/sequence.hpp>
# include <elib/mp/detail/integral_constant.hpp>
# include <cstddef>

namespace elib 
{
  namespace mp
  {
    
    template <>
    struct iterator_intrinsics< model::default_random_access_iterator >
    {
      
      template <class It> struct deref;
      template <class It> struct next;
      template <class It> struct prior;
      template <class It, class N> struct advance;
      template <class It, long N> struct advance_c;
      template <class First, class Last> struct distance;
      
      template <template <class, std::size_t> class It, class Seq, std::size_t N>
      struct deref< It<Seq, N> >
      {
        using type = at_c_t<Seq, N>;
      };
      
      
      template <template <class, std::size_t> class It, class Seq, std::size_t N>
      struct next< It<Seq, N> >
      {
        using type = It<Seq, N+1>;
      };
      
      
      template <template <class, std::size_t> class It, class Seq, std::size_t N>
      struct prior< It<Seq, N> >
      {
        using type = It<Seq, N-1>;
      };
      
      template <
          template <class, std::size_t> class It, class Seq, std::size_t N
        , class Delta 
        >
      struct advance< It<Seq, N>, Delta>
      {
        using type = It<Seq, N + Delta::type::value>;
      };
      
      
      template <
          template <class, std::size_t> class It, class Seq, std::size_t N
        , long Delta
        >
      struct advance_c< It<Seq, N>, Delta>
      {
        using type = It<Seq, N + Delta>;
      };
      
      
      template <
          template <class, std::size_t> class It1, class Seq1, std::size_t N1
        , template <class, std::size_t> class It2, class Seq2, std::size_t N2
        >
      struct distance< It1<Seq1, N1>, It2<Seq2, N2> >
      {
        using type = long_< static_cast<long>(N2 - N1) >;
      };
      
    };
    
  }                                                         // namespace mp
}                                                           // namespace elib
#endif /* ELIB_MP_ITERATOR_DEFAULT_RANDOM_ACCESS_ITERATOR_INTRINSICS_HPP */