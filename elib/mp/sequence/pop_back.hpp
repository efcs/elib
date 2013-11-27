#ifndef ELIB_MP_SEQUENCE_POP_BACK_HPP
#define ELIB_MP_SEQUENCE_POP_BACK_HPP

# include <elib/mp/sequence/sequence_fwd.hpp>
# include <elib/mp/sequence/sequence_tag.hpp>

namespace elib
{
  namespace mp
  {
  //-------------------------------- pop_back -------------------------------// 
  
    template <class Seq>
    struct pop_back
      : detail::pop_back_impl<sequence_tag_t<Seq>> 
          ::template apply<Seq>
    {};
    
    
    template <class Seq>
    using pop_back_t = typename pop_back<Seq>::type;
  
    
    namespace detail
    {
    //-------------------------------- pop_back_impl ------------------------// 
      
      // No default Impl
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
