#ifndef ELIB_MP_CONCEPTS_CONCEPT_LIST_HPP
#define ELIB_MP_CONCEPTS_CONCEPT_LIST_HPP

# include <elib/mp/concepts/fwd.hpp>
# include <elib/mp/detail/integral_constant.hpp>
# include <elib/mp/identity.hpp>
# include <elib/mp/pair.hpp>
# include <elib/mp/na.hpp>

namespace elib 
{
  namespace mp
  {
    
    template <class ...Concepts>
    struct concept_list
    {
      static pair<false_, na> satisfies_concept(...);
      static pair<false_, na> has_concept(...);
      
      static_assert(sizeof...(Concepts) == 0, 
                    "Overload Resolution check");
    };
    
    
    template <class First, class ...Rest>
    struct concept_list<First, Rest...>
      : concept_list<Rest...>
    {
      using type = concept_list;
      using concept = First;
      
      static pair<true_, First> satisfies_concept(First);
      static pair<true_, First> has_concept(identity<First>);
      
      using concept_list<Rest...>::satisfies_concept;
      using concept_list<Rest...>::has_concept;
    };
    
    
    template <class T>
    struct is_concept_list : false_
    {};
    
    template <class ...Args>
    struct is_concept_list< concept_list<Args...> > : true_
    {};
    
  }                                                         // namespace mp
}                                                           // namespace elib
#endif /* ELIB_MP_CONCEPTS_CONCEPT_LIST_HPP */