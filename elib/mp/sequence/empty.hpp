#ifndef ELIB_MP_SEQUENCE_EMPTY_HPP
#define ELIB_MP_SEQUENCE_EMPTY_HPP

# include <elib/mp/sequence/sequence_fwd.hpp>
# include <elib/mp/sequence/sequence_tag.hpp>
# include <elib/mp/sequence/begin_end.hpp>
# include <elib/CXX14/type_traits.hpp>

namespace elib
{
  namespace mp
  {
  //-------------------------------- empty ----------------------------------// 
    
    template <class Seq>
    struct empty
      : detail::empty_impl<sequence_tag_t<Seq>> 
          ::template apply<Seq>
    {};
    
     
    template <class Seq>
    using empty_t = typename empty<Seq>::type;
    
    
    namespace detail
    {
    //-------------------------------- empty_impl ---------------------------// 
      
      template <class Tag>
      struct empty_impl
      {
        template <class Seq>
        struct apply 
          : std::is_same< begin_t<Seq>, end_t<Seq> >
        {};
      };
      
    }                                                       // namespace detail
  }                                                         // namespace mp
}                                                           // namespace elib
#endif /* ELIB_MP_SEQUENCE_EMPTY_HPP */