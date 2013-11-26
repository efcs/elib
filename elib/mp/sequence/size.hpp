#ifndef ELIB_MP_SEQUENCE_SIZE_HPP
#define ELIB_MP_SEQUENCE_SIZE_HPP

# include <elib/mp/sequence/sequence_fwd.hpp>

namespace elib 
{
  namespace mp
  {
    namespace detail
    {
     
      //TODO
      template <class Tag>
      struct size_impl
      {
        template <class Seq>
        struct apply;
      };
     
    }                                                       // namespace detail
  }                                                         // namespace mp
}                                                           // namespace elib
#endif /* ELIB_MP_SEQUENCE_SIZE_HPP */