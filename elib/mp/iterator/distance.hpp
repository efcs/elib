#ifndef ELIB_MP_ITERATOR_DISTANCE_HPP
#define ELIB_MP_ITERATOR_DISTANCE_HPP

# include <elib/mp/iterator/iterator_fwd.hpp>
# include <elib/mp/sequence/sequence_tag.hpp>

namespace elib
{
  namespace mp
  {
  //-------------------------------- distance -------------------------------// 
  
    template <class First, class Last>
    struct distance :
      detail::distance_impl<sequence_tag_t<First>> 
        ::template apply<First, Last>
    {};
    
    
    template <class First, class Last>
    using distance_t = typename distance<First, Last>::type;
    
    
    namespace detail
    {
    //-------------------------------- distance_impl ------------------------// 
      
      //TODO
      template <class Tag>
      struct distance_impl
      {
        template <class First, class Last>
        struct apply;
      };

    }                                                       // namespace detail
  }                                                         // namespace mp
}                                                           // namespace elib
#endif /* ELIB_MP_ITERATOR_DISTANCE_HPP */