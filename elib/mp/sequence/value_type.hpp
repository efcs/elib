#ifndef ELIB_MP_SEQUENCE_VALUE_TYPE_HPP
#define ELIB_MP_SEQUENCE_VALUE_TYPE_HPP

# include <elib/mp/sequence/sequence_fwd.hpp>

namespace elib
{
  namespace mp
  {
    namespace detail
    {

      //TODO
      template <class Tag>
      struct value_type_impl
      {
        template <class Seq, class T>
        struct apply;
      };

    }                                                       // namespace detail
  }                                                         // namespace mp
}                                                           // namespace elib
#endif /* ELIB_MP_SEQUENCE_VALUE_TYPE_HPP */