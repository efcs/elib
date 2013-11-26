#ifndef ELIB_MP_SEQUENCE_ERASE_KEY_HPP
#define ELIB_MP_SEQUENCE_ERASE_KEY_HPP

# include <elib/mp/sequence/sequence_fwd.hpp>

namespace elib
{
  namespace mp
  {
    namespace detail
    {
      
      //TODO
      template <class Tag>
      struct erase_key_impl
      {
        template <class AssocSeq, class Key>
        struct apply;
      };
      
    }                                                       // namespace detail
  }                                                         // namespace mp
}                                                           // namespace elib
#endif /* ELIB_MP_SEQUENCE_ERASE_KEY_HPP */