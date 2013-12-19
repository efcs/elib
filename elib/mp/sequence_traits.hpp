#ifndef ELIB_MP_SEQUENCE_TRAITS_HPP
#define ELIB_MP_SEQUENCE_TRAITS_HPP

# include <elib/mp/sequence.hpp>
# include <elib/mp/identity.hpp>
# include <elib/mp/if.hpp>
# include <elib/mp/typedef_detector.hpp>
# include <elib/mp/detail/integral_constant.hpp>
# include <type_traits>

namespace elib 
{
  namespace mp
  {
    
    template <class T>
    struct sequence_traits
    {
      /* NOTE: nested class_type and category types are only
       *  are only needed when using the default impl
       *  of sequence_traits
       */
      using class_type = typename T::class_type;
      using category = typename T::category;
        
      // optional
      using O1_size = 
        typename std::is_base_of<
          mpl_sequence_tag, category
        >::type;
        
      using O1_unpack = 
        typename std::is_base_of<
          mpl_variadic_sequence_tag, category
        >::type;
    };
    
    
    template <class T>
    using class_type_t = typename sequence_traits<T>::class_type;
    
    template <class T>
    using class_type = identity< class_type_t<T> >;
    
    
    template <class T>
    using sequence_category_t = typename sequence_traits<T>::sequence_category;
    
    template <class T>
    using sequence_category = identity< sequence_category_t<T> >;
    
    
    namespace detail
    {
      template <class T>
      using O1_size_typedef_test = typename T::has_O1_size;
      
      template <class T>
      using O1_unpack_typedef_test = typename T::has_O1_unpack;
    }                                                       // namespace detail
    
    
    template <class T>
    using has_O1_size = 
      eval_if_t< typedef_detected<T, detail::O1_size_typedef_test>
                , detected_typedef<T, detail::O1_size_typedef_test>
                , false_
              >;
        
        
    template <class T>
    using has_O1_unpack =
      eval_if_t< typedef_detected<T, detail::O1_unpack_typedef_test>
                , detected_typedef<T, detail::O1_unpack_typedef_test>
                , false_
              >;


    

   
  }                                                         // namespace mp
}                                                           // namespace elib
#endif /* ELIB_MP_SEQUENCE_TRAITS_HPP */