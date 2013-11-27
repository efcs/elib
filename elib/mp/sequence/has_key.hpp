#ifndef ELIB_MP_SEQUENCE_HAS_KEY_HPP
#define ELIB_MP_SEQUENCE_HAS_KEY_HPP

# include <elib/mp/sequence/sequence_fwd.hpp>
# include <elib/mp/sequence/sequence_tag.hpp>

namespace elib
{
  namespace mp
  {
  //-------------------------------- has_key --------------------------------// 
    
    template <class Seq, class Key>
    struct has_key
      : detail::has_key_impl<sequence_tag_t<Seq>>
          ::template apply<Seq, Key>
    {};
    
    
    template <class Seq, class Key>
    using has_key_t = typename has_key<Seq, Key>::type;
    
    
    namespace detail
    {
    //-------------------------------- has_key_impl -------------------------// 
      
      //No default impl
      template <class Tag>
      struct has_key_impl
      {
        template <class AssocSeq, class Key>
        struct apply;
      };

    }                                                       // namespace detail
  }                                                         // namespace mp
}                                                           // namespace elib
#endif /* ELIB_MP_SEQUENCE_HAS_KEY_HPP */