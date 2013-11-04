#ifndef ELIB_ENUMERATION_ENUM_TRAITS_HPP
# define ELIB_ENUMERATION_ENUM_TRAITS_HPP

# include <elib/config.hpp>
# include <elib/enumeration/v3/detail/enum_helpers.hpp>
# include <elib/enumeration/v3/basic_enum_traits.hpp>
# include <elib/enumeration/v3/intrusive_enum_traits.hpp>


namespace elib 
{
  namespace enumeration
  {
    
    namespace detail
    {
      
      template <typename T>
      constexpr T merge_traits(bool has_one, T one, bool has_two, T two) noexcept
      {
        return has_one ? one : two;
      }
      
      
    }
    
    
# define ELIB_ENUM_MERGE_HAS(name) meta_t::has_##name || int_t::has_##name
    
# define ELIB_ENUM_MERGE(name)                                       \
  detail::merge_traits(meta_t::has_##name, meta_t::name, \
                       int_t::has_##name, int_t::name)
    
    template <class T, class=enable_if_enum<T>>
    struct enum_traits
    {
    private:
      typedef detail::meta_basic_enum_traits<T> meta_t;
      typedef detail::intrusive_enum_traits<T> int_t;
      
    public:
      
      typedef T enum_type;
      
      static constexpr bool has_basic_enum_traits = meta_t::has_basic_enum_traits;
      static constexpr bool has_name_map = meta_t::has_name_map;
      
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
        constexpr_bounds_known || has_name_map;
      
      
      static constexpr bool constexpr_range_known = 
        constexpr_bounds_known && is_contigious;
      
      static constexpr bool range_known = 
        constexpr_range_known || has_name_map;
        
    };                                                    // struct enum_traits
    
    
# undef ELIB_ENUM_MERGE
# undef ELIB_ENUM_MERGE_HAS
    
  }                                                    // namespace enumeration
}                                                           // namespace elib
#endif /* ELIB_ENUMERATION_ENUM_TRAITS_HPP */