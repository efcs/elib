#ifndef ELIB_MP_ITERATOR_ITERATOR_TRAITS_HPP
#define ELIB_MP_ITERATOR_ITERATOR_TRAITS_HPP

# include <elib/mp/iterator/fwd.hpp>
# include <elib/mp/model_of.hpp>
# include <elib/mp/member_type_detector.hpp>
# include <elib/mp/logical.hpp>
# include <elib/mp/void.hpp>
# include <elib/aux.hpp>

namespace elib 
{
  namespace mp
  {
    
    template <class T>
    struct iterator_traits
    {
      using model_type = typename T::model_type;
    };
    
    
    template <class T>
    struct is_iterator : is_model_of_t<T, model::iterator>
    {};


    template <class T>
    using is_iterator_t = is_model_of_t<T, model::iterator>;
    
    
    template <class T>
    struct is_forward_iterator 
      : is_model_of_t<T, model::forward_iterator>
    {};


    template <class T>
    using is_forward_iterator_t = 
      is_model_of_t<T, model::forward_iterator>;
    
    
    template <class T>
    struct is_bidirectional_iterator 
      : is_model_of_t<T, model::bidirectional_iterator>
    {};


    template <class T>
    using is_bidirectional_iterator_t = 
      is_model_of_t<T, model::bidirectional_iterator>;
    
    
    template <class T>
    struct is_random_access_iterator 
      : is_model_of_t<T, model::random_access_iterator>
    {};


    template <class T>
    using is_random_access_iterator_t = 
      is_model_of_t<T, model::random_access_iterator>;
    
    
    template <class T>
    struct is_default_random_access_iterator 
      : is_model_of_t<T, model::default_random_access_iterator>
    {};


    template <class T>
    using is_default_random_access_iterator_t = 
      is_model_of_t<T, model::default_random_access_iterator>;
      
    
    
    template <class T> 
    struct has_nested_item : has_item_member_type<T>
    {};
    
    
    template <class T>
    using has_nested_item_t = typename has_item_member_type<T>::type;
  
  
    template <class T> 
    struct has_nested_next : has_next_member_type<T>
    {};
    
    
    template <class T>
    using has_nested_next_t = typename has_next_member_type<T>::type;
    
    
    template <class T> 
    struct has_nested_prior : has_prior_member_type<T>
    {};
    
    
    template <class T>
    using has_nested_prior_t = typename has_prior_member_type<T>::type;
    
    
  }                                                         // namespace mp
}                                                           // namespace elib
#endif /* ELIB_MP_ITERATOR_ITERATOR_TRAITS_HPP */