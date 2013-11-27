#ifndef ELIB_MP_SEQUENCE_ORDER_HPP
#define ELIB_MP_SEQUENCE_ORDER_HPP

# include <elib/mp/sequence/sequence_fwd.hpp>
# include <elib/mp/sequence/sequence_tag.hpp>

namespace elib
{
  namespace mp
  {
  //-------------------------------- order ----------------------------------// 
  
    template <class Seq, class Key>
    struct order
      : detail::order_impl<sequence_tag_t<Seq>> 
          ::template apply<Seq, Key>
    {};
    
    
    template <class Seq, class Key>
    using order_t = typename order<Seq, Key>::type;
  
    
    namespace detail
    {
    //-------------------------------- order_impl ---------------------------// 
      
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
