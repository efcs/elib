#ifndef ELIB_MP_ITERATOR_BIDIRECTIONAL_ITERATOR_INTRINSICS_HPP
#define ELIB_MP_ITERATOR_BIDIRECTIONAL_ITERATOR_INTRINSICS_HPP


# include <elib/mp/iterator/fwd.hpp>
# include <elib/mp/iterator/forward_iterator_intrinsics.hpp>
# include <elib/mp/identity.hpp>


namespace elib 
{
  namespace mp
  {
    
    template <>
    struct iterator_intrinsics< model::bidirectional_iterator >
      : iterator_intrinsics< model::forward_iterator >
    {
      template <class It>
      using prior = identity< typename It::prior >;
      
      
      template <class It, long N, bool = (N >= 0)>
      struct advance_c_impl;
      
      
      template <class It, long N>
      struct advance_c_impl<It, N, true>
        : advance_c_impl<mp::next_t<It>, N - 1, true>
      {};
      
      
      template <class It, long N>
      struct advance_c_impl<It, N, false>
        : advance_c_impl<mp::prior_t<It>, N + 1, false>
      {};
      
      
      template <class It, bool IsNeg>
      struct advance_c_impl<It, 0, IsNeg>
      {
        using type = It;
      };
      
      
      template <class It, long N>
      using advance_c = advance_c_impl<It, N>;
      
      
      template <class It, class N>
      using advance = advance_c_impl<It, N::type::value>;
      
    };
  }                                                         // namespace mp
}                                                           // namespace elib
#endif /* ELIB_MP_ITERATOR_BIDIRECTIONAL_ITERATOR_INTRINSICS_HPP */