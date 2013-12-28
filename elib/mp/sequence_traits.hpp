#ifndef ELIB_MP_SEQUENCE_TRAITS_HPP
# define ELIB_MP_SEQUENCE_TRAITS_HPP

# include <elib/mp/detail/integral_constant.hpp>
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
    namespace detail
    {
      
      template <class T>
      using has_class_type_member_type_test = typename T::class_type;
      
      template <class T>
      using has_model_type_member_type_test = typename T::model_type;
      
      /* default value when not detected is void */
      template <class T>
      using sfinae_attempt_get_class_type_t = 
        member_type_t<T, has_class_type_member_type_test>;
      
          
      template <class T>
      using sfinae_attempt_get_model_type_t = 
        member_type_t<T, has_model_type_member_type_test>;
      
    }                                                       // namespace detail
  
    template <class T>
    struct sequence_traits 
    {
      // required
      using class_type = detail::sfinae_attempt_get_class_type_t<T>;
      using model_type = detail::sfinae_attempt_get_model_type_t<T>;

      // optional (should only be accessed indirectly)
      using has_O1_size = 
        bool_<
          std::is_base_of<
              model::mpl_sequence
            , model_type
          >::type::value
        >;
    };


    template <class T>
    using class_type_t = typename sequence_traits<T>::class_type;

    template <class T>
    struct class_type
    {
      using type = class_type_t<T>;
    };


    template <class T>
    using model_type_t = typename sequence_traits<T>::model_type;

    template <class T>
    struct model_type
    {
      using type = model_type_t<T>;
    };


    template <class T, class Tag>
    using is_model_of_t = 
      bool_<
        std::is_base_of<
            Tag
          , typename sequence_traits<T>::model_type
        >::type::value
      >;

    template <class T, class Tag>
    struct is_model_of 
      : is_model_of_t<T, Tag>
    {};

    
    template <class T>
    using is_sequence_t =
      is_model_of_t<T, model::sequence>;
    
    template <class T>
    struct is_sequence 
      : is_model_of_t<T, model::sequence>
    {};
    
    
    template <class T>
    using is_variadic_t = 
      is_model_of_t<T, model::variadic>;

    template <class T>
    struct is_variadic 
      : is_model_of_t<T, model::variadic>
    {};
    
    
    template <class T>
    using is_forward_sequence_t = 
      is_model_of_t<T, model::forward_sequence>;

    template <class T>
    struct is_forward_sequence 
      : is_model_of_t<T, model::forward_sequence>
    {};
    
    
    template <class T>
    using is_bidirectional_sequence_t = 
      is_model_of_t<T, model::bidirectional_sequence>;

    template <class T>
    struct is_bidirectional_sequence 
      : is_model_of_t<T, model::bidirectional_sequence>
    {};
    
    
    template <class T>
    using is_random_access_sequence_t = 
      is_model_of_t<T, model::random_access_sequence>;

    template <class T>
    struct is_random_access_sequence 
      : is_model_of_t<T, model::random_access_sequence>
    {};
    
    
    template <class T>
    using is_variadic_sequence_t = 
      is_model_of_t<T, model::variadic_sequence>;

    template <class T>
    struct is_variadic_sequence 
      : is_model_of_t<T, model::variadic_sequence>
    {};
    
    
    template <class T>
    using is_variadic_list_t =
      is_model_of_t<T, model::variadic_list>;

    template <class T>
    struct is_variadic_list 
      : is_model_of_t<T, model::variadic_list>
    {};
    
    
    template <class T>
    using is_associative_sequence_t = 
      is_model_of_t<T, model::associative_sequence>;

    template <class T>
    struct is_associative_sequence 
      : is_model_of_t<T, model::associative_sequence>
    {};
    
    
    template <class T>
    using is_extensible_sequence_t = 
      is_model_of_t<T, model::extensible_sequence>;

    template <class T>
    struct is_extensible_sequence 
      : is_model_of_t<T, model::extensible_sequence>
    {};
    
    
    template <class T>
    using is_front_extensible_sequence_t = 
      is_model_of_t<T, model::front_extensible_sequence>;

    template <class T>
    struct is_front_extensible_sequence 
      : is_model_of_t<T, model::front_extensible_sequence>
    {};
    
    
    template <class T>
    using is_back_extensible_sequence_t = 
      is_model_of_t<T, model::back_extensible_sequence>;

    template <class T>
    struct is_back_extensible_sequence 
      : is_model_of_t<T, model::back_extensible_sequence>
    {};
    
    
    template <class T>
    using is_front_extensible_variadic_sequence_t = 
      is_model_of_t<T, model::front_extensible_variadic_sequence>;

    template <class T>
    struct is_front_extensible_variadic_sequence 
      : is_model_of_t<T, model::front_extensible_variadic_sequence>
    {};
    
    
    template <class T>
    using is_back_extensible_variadic_sequence_t = 
      is_model_of_t<T, model::back_extensible_variadic_sequence>;

    template <class T>
    struct is_back_extensible_variadic_sequence 
      : is_model_of_t<T, model::back_extensible_variadic_sequence>
    {};
    
    
    template <class T>
    using is_associative_extensible_sequence_t = 
      is_model_of_t<T, model::associative_extensible_sequence>;

    template <class T>
    struct is_associative_extensible_sequence 
      : is_model_of_t<T, model::associative_extensible_sequence>
    {};
    
    
    template <class T>
    using is_mpl_sequence_t = 
      is_model_of_t<T, model::mpl_sequence>;

    template <class T>
    struct is_mpl_sequence 
      : is_model_of_t<T, model::mpl_sequence>
    {};
    
    
    template <class T>
    using is_mpl_variadic_t = 
      and_t<
          is_mpl_sequence_t<T>
        , is_variadic_t<T>
        >;
        
    template <class T>
    struct is_mpl_variadic : is_mpl_variadic_t<T>
    {};
    


    namespace detail
    {
      template <class T>
      using has_O1_size_typedef_test = typename T::has_O1_size;
    }                                                       // namespace detail

    template <class T>
    using has_O1_size = 
      if_t< 
          has_member_type<sequence_traits<T>, detail::has_O1_size_typedef_test>
        , member_type_t<sequence_traits<T>, detail::has_O1_size_typedef_test>
        , false_
        >;


  }                                                          // namespace mp
}                                                           // namespace elib
#endif /* ELIB_MP_SEQUENCE_TRAITS_HPP */
