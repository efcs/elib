#ifndef ELIB_MP_CONCEPTS_META_CONCEPT_HPP
#define ELIB_MP_CONCEPTS_META_CONCEPT_HPP

# include <elib/mp/concepts/fwd.hpp>
# include <elib/mp/concepts/concept_list.hpp>
# include <elib/mp/concepts/checking.hpp>
# include <elib/mp/concepts/detection.hpp>
# include <elib/mp/integral_constant.hpp>
# include <elib/mp/apply_wrap.hpp>

namespace elib 
{
  namespace mp
  {
    
    template <class ...Preds>
    struct meta_concept
    {
      using type = meta_concept;
      
      template <class CList>
      using apply =  typename
        detail::check_meta_concept_impl<false, true, CList>::template 
          apply<CList, Preds...>;
    };
    
    
    template <class MC, class CList>
    using check_meta_concept = typename MC::template apply<CList>;
    
    
    template <class MC, class CList>
    using check_meta_concept_t = typename MC::template apply<CList>::type;
    
    
    namespace detail
    {
      
      template <bool Empty, bool Good, class> struct check_meta_concept_impl;
      
      template <bool Good>
      struct check_meta_concept_impl<true, Good>
      {
        template <class CList>
        using apply = bool_<Good>;
      };
      
      template <>
      struct check_meta_concept_impl<false, true>
      {
        template <class CList, class First, class ...Rest>
        using apply = 
          typename check_meta_concept_impl<
              sizeof...(Rest) == 0
            , apply_wrap_t<First, CList>::value
          >::template apply<CList, Rest...>;
      };
      
      template <>
      struct check_meta_concept_impl<false, false>
      {
        template <class CList, class ...Rest>
        using apply = false_;
      };
      
      
    }
  }                                                         // namespace mp
}                                                           // namespace elib
#endif /* ELIB_MP_CONCEPTS_META_CONCEPT_HPP */
