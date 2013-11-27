#ifndef ELIB_MP_ITERATOR_DISTANCE_HPP
#define ELIB_MP_ITERATOR_DISTANCE_HPP

# include <elib/mp/config.hpp>
# include <elib/mp/iterator/iterator_fwd.hpp>
# include <elib/mp/iterator/next_prior.hpp>
# include <elib/mp/intrinsic/sequence_tag.hpp>
# include <elib/mp/view/iterator_range.hpp>
# include <elib/mp/metafunction/placeholders.hpp>
# include <elib/mp/algorithm/iter_fold.hpp>
# include <elib/mp/types/long.hpp>

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
     
      template <class Tag>
      struct distance_impl
      {
        template <class First, class Last>
        struct apply 
          : iter_fold<
              iterator_range<First, Last>
            , long_<0>
            , next<_1>
            >
        {};
      };

    }                                                       // namespace detail
  }                                                         // namespace mp
}                                                           // namespace elib
#endif /* ELIB_MP_ITERATOR_DISTANCE_HPP */