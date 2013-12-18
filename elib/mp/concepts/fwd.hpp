#ifndef ELIB_MP_CONCEPTS_FWD_HPP
#define ELIB_MP_CONCEPTS_FWD_HPP

namespace elib 
{
  namespace mp
  {
    /* Concepts are just tags */
    template <class ...Concepts>
    struct concept_list;
    
    template <class T> struct is_concept_list;
    
  //-------------------------------- checking --------------------------------// 
  
    // implemented using aliases
    // template <class List, class T> check_concept
    // template <class List, class T> contains_concept
    // template <class List, class T> satisfies_concept
    // template <class List, class T> satisfied_by
    // template <class List, class OtherList> contains_all_concepts
    // template <class List, class OtherList> satisfies_all_concepts
    
  //-------------------------------- detection --------------------------------// 
  
    // template <class T> detect_nested_concepts
    // template <class T> has_nested_concepts
    // template <class T> get_nested_concepts
    // template <class T> detect_inherited_concepts
    // template <class T> has_inherited_concepts
    // template <class T> get_inherited_concepts
    // template <class T> detect_concepts
    // template <class T> has_concepts
    // template <class T> get_concepts
    
     namespace detail
    {
      template <class T> struct nested_concepts_detector;
      template <class T> struct inherited_concepts_detector;
      
      // checks for both nested and inherited concepts
      // currently throws an error if both are found
      template <class T> struct concepts_detector;
    }                                                       // namespace detail
    
  //-------------------------------- meta concepts ---------------------------// 
    
    // metafunction class: apply< ConceptList > -> Bool
    // -- equiv to operator && (Preds(ConceptList)...)
    // -- including short-circuting
    template <class ...Preds> struct meta_concept;
    
    // template <class MC, class CList> check_meta_concept
    
    namespace detail
    {
      // weird setup allows for minimal instantiations af concrete struct
      // via template aliasing apply
      template <bool Empty, bool Good, class=void> struct check_meta_concept_impl;
    }                                                       // namespace detail
    
  //-------------------------------- model_of -------------------------------// 
  
    template <class T, class ...MetaConcepts> struct model_of;
    //template <class T, class ...MetaConcepts> model_of_t;
  }                                                         // namespace mp
}                                                           // namespace elib
#endif /* ELIB_MP_CONCEPTS_FWD_HPP */