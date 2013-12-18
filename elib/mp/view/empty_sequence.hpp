#ifndef ELIB_MP_VIEW_EMPTY_SEQUENCE_HPP
#define ELIB_MP_VIEW_EMPTY_SEQUENCE_HPP

# include <elib/mp/get_impl.hpp>
# include <elib/mp/sequence.hpp>
# include <elib/mp/iterator.hpp>
# include <elib/mp/integral_constant.hpp>

namespace elib 
{
  namespace mp
  {
    
    struct empty_sequence
    {};
    
    
    struct empty_sequence_iterator
    {
      using category = random_access_iterator_tag;
    };
    
    
    namespace detail
    {
      
      struct empty_sequence_intrinsics
      {
        
        template <class Seq>
        using sequence_size = size_type<0>;
        
        template <class Seq>
        using begin = identity<empty_sequence_iterator>;
        
        template <class Seq>
        using end = identity<empty_sequence_iterator>;
        
      };                                           // empty_sequence_intrinsics
      
    }                                                       // namespace detail
    
    
    template <>
    struct get_impl< empty_sequence >
    {
      using type = detail::empty_sequence_intrinsics;
    };
    
  }                                                         // namespace mp
}                                                           // namespace elib
#endif /* ELIB_MP_VIEW_EMPTY_SEQUENCE_HPP */