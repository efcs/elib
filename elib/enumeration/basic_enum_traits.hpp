#ifndef ELIB_ENUM_BASIC_ENUM_TRAITS_HPP
#define ELIB_ENUM_BASIC_ENUM_TRAITS_HPP

# include <elib/config.hpp>
# include <elib/enumeration/enum_helper.hpp>

# include <elib/CXX14/type_traits.hpp>

# include <string>
# include <map>

namespace elib 
{
  namespace enumeration
  {
    
    
    template <typename T>
    using enum_map_t = const std::map<T, std::string>;
  
  
# ifdef ELIB_ENUM_EXAMPLE

#   error This code is an example and should never be compiled
    
    template <typename T>
    struct basic_enum_traits
    {
      static enum_map_t<T> name_map;
      
      static constexpr T ELIB_ENUM_DEFAULT_VALUE = T::value; 
      static constexpr T ELIB_ENUM_ERROR_VALUE = T::value;
      
      static constexpr T ELIB_ENUM_FIRST_VALUE = T::value;
      static constexpr T ELIB_ENUM_LAST_VALUE = T::value;
      
      static constexpr bool ELIB_ENUM_IS_CONTIGIOUS = false;
      static constexpr bool ELIB_ENUM_IS_BITMASK = false;
      static constexpr bool ELIB_ENUM_IS_ARITHMETIC = false;
      static constexpr bool ELIB_ENUM_IS_LOGICAL = false;
      static constexpr bool ELIB_ENUM_IS_MIXED_COMPARIBLE = false;
      
    };
    
#endif

    /* Actual implementation of basic_enum_traits, 
     * it has no members, except one used to detect if it is the default
     * instantiation
     */
    
    template <class T>
    struct basic_enum_traits
    {
      static constexpr bool ELIB_ENUM_IS_DEFAULT_ENUM_TRAITS = true;
    };
      
      
    namespace detail
    {
     
      template <
        class T
        , template <class _Test> class ApplyTest
      >
      struct traits_detector_impl
      {
      private:
        
        template <class _T>
        static std::true_type test(ApplyTest<_T>*);
        
        template <class _T>
        static std::false_type test(...);
        
      public:
        
        typedef decltype(test<T>(0)) type;
        
      };
      
      
      template <
        class T
        , template <class _Test> class ApplyTest 
      >
      struct traits_detector 
        : traits_detector_impl<T, ApplyTest>::type
      {};
     
     
      template <class T>
      using traits_is_default_detector = 
        decltype(&basic_enum_traits<T>::ELIB_ENUM_IS_DEFAULT_ENUM_TRAITS);
        
      template <class T>
      using traits_name_map_detector = 
        decltype(&basic_enum_traits<T>::name_map);
      
      
    }                                                       // namespace detail
    
    template <class T>
    struct has_basic_enum_traits 
      : std::integral_constant<bool, 
          !detail::traits_detector<
            T, detail::traits_is_default_detector
          >::value
        >
    {};
    
    template <class T, bool=has_basic_enum_traits<T>::value>
    struct has_name_map : std::false_type
    {};
    
    template <class T>
    struct has_name_map<T, true>
      : std::integral_constant<bool, 
          detail::traits_detector<
            T, detail::traits_name_map_detector
          >::value
        >
    {};
    
      
  }                                                    // namespace enumeration
}                                                           // namespace elib
#endif /* ELIB_ENUM_BASIC_ENUM_TRAITS_HPP */
