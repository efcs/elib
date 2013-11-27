#ifndef ELIB_MP_INTRINSIC_ERASE_HPP
#define ELIB_MP_INTRINSIC_ERASE_HPP

# include <elib/mp/intrinsic/intrinsic_fwd.hpp>
# include <elib/mp/intrinsic/sequence_tag.hpp>

namespace elib
{
  namespace mp
  {
  //-------------------------------- erase ----------------------------------//
  
    template <class Seq, class First, class Last = typename First::next>
    struct erase
      : detail::erase_impl<sequence_tag_t<Seq>> 
          ::template apply<Seq, First, Last>
    {};
    
    
    template <class Seq, class First, class Last>
    using erase_t = typename erase<Seq, First, Last>::type;
    
    
    namespace detail
    {
    //-------------------------------- erase_impl ---------------------------// 
      
      //TODO
      template <class Tag>
      struct erase_impl
      {
        template <class Seq, class First, class Last>
        struct apply;
      };
      
    }                                                       // namespace detail
  }                                                         // namespace mp
}                                                           // namespace elib
#endif /* ELIB_MP_INTRINSIC_ERASE_HPP */