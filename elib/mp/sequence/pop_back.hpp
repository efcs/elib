#ifndef ELIB_MP_SEQUENCE_POP_BACK_HPP
#define ELIB_MP_SEQUENCE_POP_BACK_HPP

# include <elib/mp/sequence/sequence_fwd.hpp>

namespace elib
{
  namespace mp
  {
    namespace detail
    {

      //TODO
      template <class Tag>
      struct pop_back_impl
      {
        template <class Seq>
        struct apply;
      };

    }                                                       // namespace detail
  }                                                         // namespace mp
}                                                           // namespace elib
#endif /* ELIB_MP_SEQUENCE_POP_BACK_HPP */
