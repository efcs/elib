#ifndef ELIB_MP_SEQUENCE_ERASE_KEY_HPP
#define ELIB_MP_SEQUENCE_ERASE_KEY_HPP

# include <elib/mp/sequence/sequence_fwd.hpp>
# include <elib/mp/sequence/sequence_tag.hpp>

namespace elib
{
  namespace mp
  {
  //-------------------------------- erase_key ------------------------------//
  
    template <class AssocSeq, class Key>
    struct erase_key
      : detail::erase_key_impl<sequence_tag_t<AssocSeq>>
          ::template apply<AssocSeq, Key>
    {};
    
    
    template <class AssocSeq, class Key>
    using erase_key_t = typename erase_key<AssocSeq, Key>::type;
    
    
    namespace detail
    {
    //-------------------------------- erase_key_impl -----------------------// 

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