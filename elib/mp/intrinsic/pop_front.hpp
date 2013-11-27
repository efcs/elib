#ifndef ELIB_MP_INTRINSIC_POP_FRONT_HPP
#define ELIB_MP_INTRINSIC_POP_FRONT_HPP

# include <elib/mp/intrinsic/intrinsic_fwd.hpp>
# include <elib/mp/intrinsic/sequence_tag.hpp>

namespace elib
{
  namespace mp
  {
  //-------------------------------- pop_front ------------------------------// 
  
    template <class Seq>
    struct pop_front
      : detail::pop_front_impl<sequence_tag_t<Seq>> 
          ::template apply<Seq>
    {};
    
     
    template <class Seq>
    using pop_front_t = typename pop_front<Seq>::type;
  
    
    namespace detail
    {
    //-------------------------------- pop_front_impl -----------------------// 
      
      // No default impl
      template <class Tag>
      struct pop_front_impl
      {
        template <class Seq>
        struct apply;
      };

    }                                                       // namespace detail
  }                                                         // namespace mp
}                                                           // namespace elib
#endif /* ELIB_MP_INTRINSIC_POP_FRONT_HPP */