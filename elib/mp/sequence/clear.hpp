#ifndef ELIB_MP_SEQUENCE_CLEAR_HPP
#define ELIB_MP_SEQUENCE_CLEAR_HPP

# include <elib/mp/sequence/sequence_fwd.hpp>

namespace elib
{
  namespace mp
  {
    namespace detail
    {
      
      //TODO
      template <class Tag>
      struct clear
      {
        template <class Seq>
        struct apply;
      };
      
    }                                                       // namespace detail
  }                                                         // namespace mp
}                                                           // namespace elib
#endif /* ELIB_MP_SEQUENCE_CLEAR_HPP */