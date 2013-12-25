#ifndef ELIB_MP_SEQUENCE_TRAITS_HPP
# define ELIB_MP_SEQUENCE_TRAITS_HPP

# include <elib/mp/detail/integral_constant.hpp>
# include <elib/mp/sequence.hpp>
# include <elib/mp/identity.hpp>
# include <elib/mp/member_type_detector.hpp>
# include <elib/mp/if.hpp>
# include <type_traits>

namespace elib 
{
 namespace mp
 {
    
    template <class T>
    struct sequence_traits
    {
      // required
      using class_type = typename T::class_type;
      using model_type = typename T::model_type;
      
      // optional (should only be accessed indirectly)
      using has_O1_size = bool_< 
        std::is_base_of<model::mpl_sequence, model_type>::type::value 
        >;
      
      using has_O1_unpack = bool_<
        std::is_base_of<model::mpl_variadic, model_type>::type::value
        >;
    };
    
    
    template <class T>
    using class_type = identity< typename sequence_traits<T>::class_type >;
    
    template <class T>
    using class_type_t = typename sequence_traits<T>::class_type;
    
    
    template <class T>
    using model_type = identity< typename sequence_traits<T>::model_type >;
    
    template <class T>
    using model_type_t = typename sequence_traits<T>::model_type;
    
    
    
    template <class T, class Tag>
    using is_model_of = 
      std::is_base_of<
        Tag
      , typename sequence_traits<T>::model_type
      >;
    
    
    template <class T>
    using is_mpl_sequence = is_model_of<T, model::mpl_sequence>;
      
    template <class T>
    using is_mpl_variadic = is_model_of<T, model::mpl_variadic>;
    
    template <class T>
    using is_sequence = is_model_of<T, model::sequence>;
    
    template <class T>
    using is_variadic = is_model_of<T, model::variadic>;
    
    
    namespace detail
    {
      template <class T>
      using has_O1_size_typedef_test = typename T::has_O1_size;
      
      template <class T>
      using has_O1_unpack_typedef_test = typename T::has_O1_unpack;
    }                                                       // namespace detail
    
    
    template <class T>
    using has_O1_size = 
      if_t< 
          has_member_type<sequence_traits<T>, detail::has_O1_size_typedef_test>
        , member_type_t<sequence_traits<T>, detail::has_O1_size_typedef_test>
        , false_
        >;
    
    
    template <class T>
    using has_O1_unpack =
      if_t<
          has_member_type<sequence_traits<T>, detail::has_O1_unpack_typedef_test>
        , member_type_t<sequence_traits<T>, detail::has_O1_unpack_typedef_test>
        , false_
        >;
 }                                                          // namespace mp
}                                                           // namespace elib
#endif /* ELIB_MP_SEQUENCE_TRAITS_HPP */
