#ifndef ELIB_MP_ITERATOR_FORWARD_ITERATOR_INTRINSICS_HPP
#define ELIB_MP_ITERATOR_FORWARD_ITERATOR_INTRINSICS_HPP

# include <elib/mp/iterator/fwd.hpp>
# include <elib/mp/iterator/iterator_traits.hpp>

namespace elib 
{
  namespace mp
  {
    
    template <>
    struct iterator_intrinsics< model::forward_iterator >
    {
      
      template <class It>
      struct deref
      {
        using type = typename It::item;
      };
      
      template <class It>
      using next = identity< typename It::next >;
      
      
      template <class It, std::size_t N>
      struct advance_c
        : advance_c< mp::next_t<It>, N - 1>
      {};
      
      template <class It>
      struct advance_c< It, 0 >
      {
        using type = It;
      };
      
      
      template <class It, class N>
      using advance = advance_c<It, N::type::value>;
      
      
      template <class First, class Last, std::size_t N>
      struct distance_impl
        : distance_impl< mp::next_t<First>, Last, N+1>
      {};
      
      
      template <class Last, std::size_t N>
      struct distance_impl<Last, Last, N>
      {
        using type = size_type_<N>;
      };
      
      
      template <class First, class Last>
      using distance = distance_impl<First, Last, 0>;
      
    };
  }                                                         // namespace mp
}                                                           // namespace elib
#endif /* ELIB_MP_ITERATOR_FORWARD_ITERATOR_INTRINSICS_HPP */