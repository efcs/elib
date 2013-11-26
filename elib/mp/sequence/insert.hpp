#ifndef ELIB_MP_SEQUENCE_INSERT_HPP
#define ELIB_MP_SEQUENCE_INSERT_HPP

# include <elib/mp/sequence/sequence_fwd.hpp>

namespace elib
{
  namespace mp
  {
    namespace detail
    {

      //TODO
      template <class Tag>
      struct insert_impl
      {
        template <class Seq, class Pos, class T>
        struct apply;
      };

    }                                                       // namespace detail
  }                                                         // namespace mp
}                                                           // namespace elib
#endif /* ELIB_MP_SEQUENCE_INSERT_HPP */
