#ifndef ELIB_MP_SEQUENCE_AT_HPP
#define ELIB_MP_SEQUENCE_AT_HPP

# include <elib/mp/sequence/sequence_fwd.hpp>

namespace elib
{
  namespace mp
  {
    namespace detail
    {
      
      //TODO
      template <class Tag>
      struct at_impl
      {
        template <class Seq, class N>
        struct apply;
      };
      
    }                                                       // namespace detail
  }                                                         // namespace mp
}                                                           // namespace elib
#endif /* ELIB_MP_SEQUENCE_AT_HPP */