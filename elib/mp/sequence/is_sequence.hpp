#ifndef ELIB_MP_SEQUENCE_IS_SEQUENCE_HPP
#define ELIB_MP_SEQUENCE_IS_SEQUENCE_HPP

# include <elib/mp/sequence/sequence_fwd.hpp>

namespace elib
{
  namespace mp
  {
    namespace detail
    {

      //TODO
      template <class Tag>
      struct is_sequence_impl
      {
        template <class T>
        struct apply;
      };

    }                                                       // namespace detail
  }                                                         // namespace mp
}                                                           // namespace elib
#endif /* ELIB_MP_SEQUENCE_IS_SEQUENCE_HPP */