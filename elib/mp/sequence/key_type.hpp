#ifndef ELIB_MP_SEQUENCE_KEY_TYPE_HPP
#define ELIB_MP_SEQUENCE_KEY_TYPE_HPP

# include <elib/mp/sequence/sequence_fwd.hpp>
# include <elib/mp/sequence/sequence_tag.hpp>

namespace elib
{
  namespace mp
  {
  //-------------------------------- key_type -------------------------------// 
    
    template <class Seq, class T>
    struct key_type
      : detail::key_type_impl<sequence_tag_t<Seq>> 
          ::template apply<Seq, T>
    {};
    
    
    template <class Seq, class T>
    using key_type_t = typename key_type<Seq, T>::type;
    
    
    namespace detail
    {
    //-------------------------------- key_type_impl ------------------------// 
      
      //TODO
      template <class Tag>
      struct key_type_impl
      {
        template <class Seq, class T>
        struct apply;
      };

    }                                                       // namespace detail
  }                                                         // namespace mp
}                                                           // namespace elib
#endif /* ELIB_MP_SEQUENCE_KEY_TYPE_HPP */