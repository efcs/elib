#ifndef ELIB_MP_CONCEPTS_CHECKING_HPP
#define ELIB_MP_CONCEPTS_CHECKING_HPP

# include <elib/mp/concepts/fwd.hpp>
# include <elib/mp/concepts/concept_list.hpp>
# include <elib/mp/identity.hpp>
# include <elib/mp/pair.hpp>
# include <utility>

namespace elib 
{
  namespace mp
  {
    
    template <class ConceptList, class Concept>
    using check_concept = decltype(
      ConceptList::satisfies_concept( std::declval<Concept>() )
    );
    
    
    template <class ConceptList, class Concept>
    using contains_concept = decltype(
      ConceptList::has_concept( identity<Concept>() )
    );
    
    
    template <class ConceptList, class Concept>
    using satisfies_concept = 
      typename check_concept<ConceptList, Concept>::first;
      
      
    template <class ConceptList, class Concept>
    using satisfied_by = 
      typename check_concept<ConceptList, Concept>::second;
    
  }                                                         // namespace mp
}                                                           // namespace elib
#endif /* ELIB_MP_CONCEPTS_CHECKING_HPP */