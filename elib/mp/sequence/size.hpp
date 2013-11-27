#ifndef ELIB_MP_SEQUENCE_SIZE_HPP
#define ELIB_MP_SEQUENCE_SIZE_HPP

# include <elib/mp/sequence/sequence_fwd.hpp>
# include <elib/mp/sequence/sequence_tag.hpp>
# include <elib/mp/sequence/begin_end.hpp>
# include <elib/mp/iterator/distance.hpp>

namespace elib 
{
  namespace mp
  {
  //-------------------------------- size -----------------------------------// 
  
    template <class T>
    struct size
      : detail::size_impl<sequence_tag_t<T>> 
          ::template apply<T>
    {};
    
    
    template <class T>
    using size_t = typename size<T>::type;
    
    
    namespace detail
    {
    //-------------------------------- size_impl ----------------------------// 
      // Default impl
      template <class Tag>
      struct size_impl
      {
        template <class Seq>
        struct apply 
          : distance<begin_t<Seq>, end_t<Seq>>
        {};
      };
     
    }                                                       // namespace detail
  }                                                         // namespace mp
}                                                           // namespace elib
#endif /* ELIB_MP_SEQUENCE_SIZE_HPP */