#ifndef ELIB_MP_SEQUENCE_INTRINSICS_HPP
#define ELIB_MP_SEQUENCE_INTRINSICS_HPP

# include <elib/mp/identity.hpp>
# include <elib/mp/iterator.hpp>
# include <elib/mp/sequence.hpp>
# include <elib/mp/algorithm/count.hpp>
# include <elib/mp/detail/integral_constant.hpp>


namespace elib 
{
  namespace mp
  {
    
    struct forward_sequence_intrinsics
    {
      template <class Seq>
      using sequence_size = count<Seq>;
      
      template <class Seq>
      using empty = bool_<mp::sequence_size_t<Seq>::value == 0>;
      
      template <class Seq>
      using begin = identity< typename Seq::begin >;
      
      template <class Seq>
      using end = identity< typename Seq::end >;
      
      template <class Seq>
      using front = mp::deref< mp::begin_t<Seq> >;
    };
    
    
    struct bidirectional_sequence_intrinsics
      : forward_sequence_intrinsics
    {
      template <class Seq>
      using back = mp::deref< mp::prior_t< mp::end_t<Seq> > >;
    };
    
  }                                                         // namespace mp
}                                                           // namespace elib
#endif /* ELIB_MP_SEQUENCE_INTRINSICS_HPP */