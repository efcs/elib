#ifndef ELIB_MP_ITERATOR_RANGE_HPP
#define ELIB_MP_ITERATOR_RANGE_HPP

# include <elib/mp/get_impl.hpp>
# include <elib/mp/identity.hpp>
# include <elib/mp/iterator.hpp>
# include <elib/mp/integral_constant.hpp>
# include <elib/mp/sequence.hpp>

namespace elib 
{
  namespace mp
  {
   
    struct iterator_range_tag {};
    
    template <class Begin, class End>
    struct iterator_range
    {
      using type = iterator_range;
      
      using class_type = iterator_range_tag;
      using model_type = iterator_range_tag;
      
      using begin = Begin;
      using end = End;
    };
    
    
    namespace detail
    {
      
      
      template <class IterCategory>
      struct iterator_range_intrinsics;
      
      
      template <>
      struct iterator_range_intrinsics<model::forward_iterator>
      {
        template <class S>
        using begin = identity< typename S::begin >;
        
        template <class S>
        using end = identity< typename S::end >;
        
        
        template <class S>
        using sequence_size = distance<typename S::begin, typename S::end>;
        
        template <class S>
        using empty = bool_< sequence_size<S>::type::value == 0 >;

        template <class S>
        using front = deref< typename S::begin >;
      };
      
      
      template <>
      struct iterator_range_intrinsics<model::bidirectional_iterator>
        : iterator_range_intrinsics<model::forward_iterator>
      {
        template <class S>
        using back = deref< prior_t<typename S::end> >;
      };
      
      
      template <>
      struct iterator_range_intrinsics<model::random_access_iterator>
        : iterator_range_intrinsics<model::bidirectional_iterator>
      {
        template <class S, class N>
        using at = deref< advance_t<typename S::begin, N> >;
        
        template <class S, long N>
        using at_c = at<S, long_<N>>;
      };
      
      
    }                                                       // namespace detail
    
    
    template <class Begin, class End>
    struct get_impl< iterator_range<Begin, End> >
    {
      using type = detail::iterator_range_intrinsics<typename Begin::model_type>;
    };
    
    
    
  }                                                         // namespace mp
}                                                           // namespace elib
#endif /* ELIB_MP_ITERATOR_RANGE_HPP */