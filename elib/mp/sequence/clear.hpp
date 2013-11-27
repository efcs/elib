#ifndef ELIB_MP_SEQUENCE_CLEAR_HPP
#define ELIB_MP_SEQUENCE_CLEAR_HPP

# include <elib/mp/sequence/sequence_fwd.hpp>
# include <elib/mp/sequence/sequence_tag.hpp>

namespace elib
{
  namespace mp
  {
    
  //-------------------------------- clear ----------------------------------// 
    
    template <class Seq>
    struct clear
      : detail::clear_impl< sequence_tag_t<Seq> > 
          ::template apply<Seq>
    {};
    
    template <class Seq>
    using clear_t = typename clear<Seq>::type;
    
    namespace detail
    {
      
    //-------------------------------- clear_impl ---------------------------// 
      
      // No default Impl
      template <class Tag>
      struct clear_impl
      {
        template <class Seq>
        struct apply;
      };
      
    }                                                       // namespace detail
  }                                                         // namespace mp
}                                                           // namespace elib
#endif /* ELIB_MP_SEQUENCE_CLEAR_HPP */