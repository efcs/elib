#ifndef ELIB_MP_SEQUENCE_ORDER_HPP
#define ELIB_MP_SEQUENCE_ORDER_HPP

# include <elib/mp/sequence/sequence_fwd.hpp>

namespace elib
{
  namespace mp
  {
    namespace detail
    {

      //TODO
      template <class Tag>
      struct order_impl
      {
        template <class Seq, class Key>
        struct apply;
      };

    }                                                       // namespace detail
  }                                                         // namespace mp
}                                                           // namespace elib
#endif /* ELIB_MP_SEQUENCE_ORDER_HPP */
