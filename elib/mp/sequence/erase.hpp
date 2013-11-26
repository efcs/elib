#ifndef ELIB_MP_SEQUENCE_ERASE_HPP
#define ELIB_MP_SEQUENCE_ERASE_HPP

# include <elib/mp/sequence/sequence_fwd.hpp>

namespace elib
{
  namespace mp
  {
    namespace detail
    {
      
      //TODO
      template <class Tag>
      struct erase_impl
      {
        template <class Seq, class First, class Last>
        struct apply;
      };
      
    }                                                       // namespace detail
  }                                                         // namespace mp
}                                                           // namespace elib
#endif /* ELIB_MP_SEQUENCE_ERASE_HPP */