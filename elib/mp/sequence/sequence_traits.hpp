#ifndef ELIB_MP_SEQUENCE_SEQUENCE_TRAITS_HPP
#define ELIB_MP_SEQUENCE_SEQUENCE_TRAITS_HPP

# include <elib/mp/detail/integral_constant.hpp>
# include <elib/mp/model_of.hpp>
# include <elib/mp/sequence.hpp>
# include <elib/mp/identity.hpp>
# include <elib/mp/member_type_detector.hpp>
# include <elib/mp/if.hpp>
# include <elib/mp/logical.hpp>
# include <elib/mp/void.hpp>
# include <type_traits>

namespace elib 
{
  namespace mp
  {

    template <class T>
    struct is_sequence : is_model_of_t<T, model::sequence_>
    {};


    template <class T>
    using is_sequence_t = is_model_of_t<T, model::sequence_>;
    
    
    template <class T>
    struct is_variadic : is_model_of_t<T, model::variadic>
    {};


    template <class T>
    using is_variadic_t = is_model_of_t<T, model::variadic>;
    
    
    template <class T>
    struct is_forward_sequence : is_model_of_t<T, model::forward_sequence>
    {};


    template <class T>
    using is_forward_sequence_t = is_model_of_t<T, model::forward_sequence>;
    
    
    template <class T>
    struct is_bidirectional_sequence 
      : is_model_of_t<T, model::bidirectional_sequence>
    {};


    template <class T>
    using is_bidirectional_sequence_t = 
      is_model_of_t<T, model::bidirectional_sequence>;
    
    
    template <class T>
    struct is_random_access_sequence 
      : is_model_of_t<T, model::random_access_sequence>
    {};


    template <class T>
    using is_random_access_sequence_t = 
      is_model_of_t<T, model::random_access_sequence>;
    
    
    template <class T>
    struct is_associative_sequence 
      : is_model_of_t<T, model::associative_sequence>
    {};


    template <class T>
    using is_associative_sequence_t = 
      is_model_of_t<T, model::associative_sequence>;
    
    
    template <class T>
    struct is_back_extensible_sequence 
      : is_model_of_t<T, model::back_extensible_sequence>
    {};


    template <class T>
    using is_back_extensible_sequence_t = 
      is_model_of_t<T, model::back_extensible_sequence>;
    
    
    template <class T>
    struct is_front_extensible_sequence 
      : is_model_of_t<T, model::front_extensible_sequence>
    {};


    template <class T>
    using is_front_extensible_sequence_t = 
      is_model_of_t<T, model::front_extensible_sequence>;
    
    
    template <class T>
    struct is_back_extensible_variadic_sequence 
      : is_model_of_t<T, model::back_extensible_variadic_sequence>
    {};


    template <class T>
    using is_back_extensible_variadic_sequence_t = 
      is_model_of_t<T, model::back_extensible_variadic_sequence>;
    
    
    template <class T>
    struct is_front_extensible_variadic_sequence 
      : is_model_of_t<T, model::front_extensible_variadic_sequence>
    {};


    template <class T>
    using is_front_extensible_variadic_sequence_t = 
      is_model_of_t<T, model::front_extensible_variadic_sequence>;
    
    
    template <class T>
    struct is_associative_extensible_sequence 
      : is_model_of_t<T, model::associative_extensible_sequence>
    {};
    
    
    template <class T>
    using is_associative_extensible_sequence_t = 
      is_model_of_t<T, model::associative_extensible_sequence>;
    
    
    template <class T>
    struct has_O1_size : is_model_of_t<T, model::O1_size>
    {};
    
    template <class T>
    using has_O1_size_t = is_model_of_t<T, model::O1_size>;
    

  }                                                          // namespace mp
}                                                           // namespace elib
#endif /* ELIB_MP_SEQUENCE_SEQUENCE_TRAITS_HPP */
