#ifndef ELIB_ENUMERATION_ENUM_TRAITS_HPP
# define ELIB_ENUMERATION_ENUM_TRAITS_HPP

# include <elib/config.hpp>
# include <elib/enumeration/v3/enum_helper.hpp>
# include <elib/enumeration/v3/detail/meta_basic_enum_traits.hpp>
# include <elib/enumeration/v3/detail/intrusive_enum_traits.hpp>


namespace elib 
{
  namespace enumeration
  {
    
    
# define ELIB_ENUM_MERGE_HAS(name) meta_t::has_##name || int_t::has_##name
# define ELIB_ENUM_MERGE(name) meta_t::has_##name ? meta_t::name : int_t::name
    
    template <class T, class=enable_if_enum<T>>
    struct enum_traits
    {
    private:
      typedef detail::meta_basic_enum_traits<T> meta_t;
      typedef detail::intrusive_enum_traits<T> int_t;
      
    public:
      
      typedef T enum_type;
      
      static constexpr bool has_default_value = ELIB_ENUM_MERGE_HAS(default_value);
      static constexpr T default_value = ELIB_ENUM_MERGE(default_value);
      
      static constexpr bool has_error_value = ELIB_ENUM_MERGE_HAS(error_value);
      static constexpr T error_value = ELIB_ENUM_MERGE(error_value);
      
      static constexpr bool has_first_value = ELIB_ENUM_MERGE_HAS(first_value);
      static constexpr T first_value = ELIB_ENUM_MERGE(first_value);
      
      static constexpr bool has_last_value = ELIB_ENUM_MERGE_HAS(last_value);
      static constexpr T last_value = ELIB_ENUM_MERGE(last_value);
      
      static constexpr bool has_is_contigious = ELIB_ENUM_MERGE_HAS(is_contigious);
      static constexpr bool is_contigious = ELIB_ENUM_MERGE(is_contigious);
      
      static constexpr bool has_is_bitmask = ELIB_ENUM_MERGE_HAS(is_bitmask);
      static constexpr bool is_bitmask = ELIB_ENUM_MERGE(is_bitmask);
      
      static constexpr bool has_is_arithmetic = ELIB_ENUM_MERGE_HAS(is_arithmetic);
      static constexpr bool is_arithmetic = ELIB_ENUM_MERGE(is_arithmetic);
      
      
      static constexpr bool constexpr_bounds_known = 
        has_first_value && has_last_value;
        
      static constexpr bool bounds_known = 
        constexpr_bounds_known || has_name_map<enum_type>::value;
      
      
      static constexpr bool constexpr_range_known = 
        constexpr_bounds_known && is_contigious;
      
      static constexpr bool range_known = 
        constexpr_range_known || has_name_map<enum_type>::value;
        
    };                                                    // struct enum_traits
    
    
# undef ELIB_ENUM_MERGE
# undef ELIB_ENUM_MERGE_HAS

  template <typename T, bool=std::is_enum<T>::value>
  struct has_bounds : std::false_type
  {};
  
  template <typename T>
  struct has_bounds<T, true>
    : std::integral_constant<bool, enum_traits<T>::has_bounds>
  {};
  
  template <typename T, bool=std::is_enum<T>::value>
  struct has_constexpr_bounds : std::false_type
  {};
  
  template <typename T>
  struct has_constexpr_bounds<T, true>
    : std::integral_constant<bool, enum_traits<T>::has_constexpr_bounds>
  {};
  

  template <typename T, bool=std::is_enum<T>::value>
  struct has_range : std::false_type
  {};
  
  template <typename T>
  struct has_range<T, true>
    : std::integral_constant<bool, enum_traits<T>::has_range>
  {};
  
  template <class T, bool=std::is_enum<T>::value>
  struct has_constexpr_range : std::false_type
  {};
  
  template <class T>
  struct has_constexpr_range<T, true> 
    : std::integral_constant<bool, enum_traits<T>::has_constexpr_range>
  {};
  
  template <typename T>
  constexpr std::enable_if_t<has_constexpr_range<T>::value, bool> 
  in_range(T v) noexcept
  {
    using e_t = enum_traits<T>;
    return (e_t::first_value <= v && e_t::last_value >= v);
  }
  
  template <typename T>
  std::enable_if_t<
    has_range<T>::value 
    && !has_constexpr_range<T>::value
  , bool>
  in_range(T v)
  {
    
  }
  
  
    
  }                                                    // namespace enumeration
}                                                           // namespace elib
#endif /* ELIB_ENUMERATION_ENUM_TRAITS_HPP */