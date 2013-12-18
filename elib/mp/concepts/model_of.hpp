#ifndef ELIB_MP_CONCEPTS_MODEL_OF_HPP
#define ELIB_MP_CONCEPTS_MODEL_OF_HPP

# include <elib/mp/concepts/fwd.hpp>
# include <elib/mp/concepts/concept_list.hpp>
# include <elib/mp/concepts/detection.hpp>
# include <elib/mp/concepts/meta_concept.hpp>
# include <elib/mp/detail/integral_constant.hpp>
# include <elib/mp/pair.hpp>
# include <elib/mp/if.hpp>

namespace elib 
{
  namespace mp
  {
    template <class T, class ...MetaC>
    struct model_of : true_
    {
      static_assert(sizeof...(MetaC) == 0, "overload resolution check");
    };
    
    template <class T, class First, class ...Rest>
    struct model_of<T, First, Rest...> 
      : if_t< 
              apply_wrap_t<First, T>
            , model_of<T, Rest...>
            , false_
            >
    {};
    
  }                                                         // namespace mp
}                                                           // namespace elib
#endif /* ELIB_MP_CONCEPTS_MODEL_OF_HPP */