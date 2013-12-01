#ifndef ELIB_MP_EMPTY_SEQUENCE_HPP
#define ELIB_MP_EMPTY_SEQUENCE_HPP

# include <elib/mp/intrinsic/intrinsic_fwd.hpp>
# include <elib/mp/iterator_tags.hpp>
# include <elib/mp/long.hpp>

namespace elib
{
  namespace mp
  {
    namespace detail
    {
      struct empty_sequence_tag {};
    }                                                       // namespace detail
    
  //-------------------------------- empty_sequence-------------------------// 
    struct empty_sequence
    {
      using tag = detail::empty_sequence_tag;
      using type = empty_sequence;
      using begin = struct { using category = random_access_iterator_tag; };
      using end = begin;
    };
    
    
    namespace detail
    {
    //-------------------------------- size_impl ---------------------------// 
    
      template <>
      struct size_impl<empty_sequence_tag>
      {
        template <class Seq>
        struct apply : long_<0>
        {};
      };
    
    }                                                       // namespace detail
  }                                                         //namespace mp
}                                                           //namespace elib
#endif /* ELIB_MP_EMPTY_SEQUENCE_HPP */