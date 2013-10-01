#ifndef ELIB_ENUMERATION_ENUM_TRAITS_HPP
#define ELIB_ENUMERATION_ENUM_TRAITS_HPP


# include <elib/config.hpp>
# include <elib/enumeration/v2/basic_enum_traits.hpp>
# include <elib/enumeration/v2/enum_fields.hpp>
# include <elib/enumeration/v2/enum_type_traits.hpp>

# include <elib/CXX14/type_traits.hpp>

# include <string>
# include <map>
# include <iterator>
# include <cstddef>
# include <functional>


namespace elib 
{
  namespace enumeration
  {
    namespace detail
    {
      
      template <typename Ret>
      struct cast_access_wrapper
      {
        cast_access_wrapper(std::function<Ret(void)> fn)
        : m_fn{fn}
        { }

        operator Ret() const noexcept
        {
          return m_fn(); 
        }
        
        //
      private:
        //
        
        std::function<Ret(void)> m_fn{};
        
      };                                          // struct cast_access_wrapper
    
    
      template <typename T, typename=void>
      struct has_basic_enum_traits : public std::true_type
      { };

      template <typename T>
      struct has_basic_enum_traits<T, typename T::m_default_traits>
        : public std::false_type
      { };


      template <typename T, typename Ret=void>
      struct enable_if_has_basic_enum_traits 
        : public std::enable_if<has_basic_enum_traits<T>::value, Ret>
      { };

      template <typename T, typename Ret=void>
      using enable_if_has_basic_enum_traits_t = 
        typename enable_if_has_basic_enum_traits<T, Ret>::type;
      
      
    }                                                       // namespace detail

    template <typename T>
    struct has_basic_enum_traits 
      : public detail::has_basic_enum_traits<T>
    { };
    
    
    template <typename T>
    struct has_constexpr_bounds 
      : public std::integral_constant<bool, first_field_value<T>::has_field && 
          last_field_value<T>::has_field>
    { };

    template <typename T>
    struct has_bounds 
      : public std::integral_constant<bool, has_constexpr_bounds<T>::value ||
          has_basic_enum_traits<T>::value>
    { };

    
    template <typename T>
    struct has_constexpr_range
      : public std::integral_constant<bool, has_constexpr_bounds<T>::value && 
          is_contiguous_field_value<T>::value>

          { };

    template <typename T>
    struct has_range
      : public std::integral_constant<bool, has_constexpr_range<T>::value ||
        has_basic_enum_traits<T>::value>
    { };
    
    
    namespace detail
    {
      
      
      template <typename EnumT, typename=void>
      struct enum_bounds;
      
      
      template <typename EnumT>
      struct enum_bounds<EnumT, 
          std::enable_if_t<has_constexpr_bounds<EnumT>::value>>
      {
        static constexpr EnumT min = first_field_value<EnumT>::value;
        static constexpr EnumT max = last_field_value<EnumT>::value; 
      };
      
      
      template <typename EnumT>
      struct enum_bounds<EnumT, std::enable_if_t<has_bounds<EnumT>::value && 
            !has_constexpr_bounds<EnumT>::value>>
      {
        /*
        static const cast_access_wrapper<EnumT> min = { 
          []() { return basic_enum_traits<EnumT>::name_map.cbegin()->first;}
        };
        
        static const cast_access_wrapper<EnumT> max = {
          [](){ return basic_enum_traits<EnumT>::name_map.crbegin()->first;} 
        };
        */ 
        
        static const EnumT min;
        static const EnumT max;
      };                                                    // struct enum_bounds
      
      template <typename EnumT>
      const EnumT 
      enum_bounds<EnumT, std::enable_if_t<has_bounds<EnumT>::value && 
          !has_constexpr_bounds<EnumT>::value>>::min = 
            (basic_enum_traits<EnumT>::name_map.cbegin())->first;
            
      template <typename EnumT>
      const EnumT 
      enum_bounds<EnumT, std::enable_if_t<has_bounds<EnumT>::value && 
          !has_constexpr_bounds<EnumT>::value>>::max = 
            basic_enum_traits<EnumT>::name_map.crbegin()->first;
          

    }                                                       // namespace detail 
    
    template <typename EnumT>
    struct enum_bounds : public detail::enum_bounds<EnumT>
    { };

    template <typename EnumT>
    constexpr std::size_t size_of_bounds(EnumT min, EnumT max) noexcept
    {
      using utype = std::underlying_type_t<EnumT>;
      return static_cast<std::size_t>(static_cast<utype>(max) - 
        static_cast<utype>(min));
    }

    template <typename EnumT>
    constexpr std::size_t size_of_bounds() noexcept
    {
      using bounds = enum_bounds<EnumT>;
      return size_of_bounds(bounds::min, bounds::max);
    }
    
    
    namespace detail
    {
      
      template <typename EnumT, typename=void>
      struct enum_range;
      
      template <typename EnumT>
      struct enum_range<EnumT, 
          std::enable_if_t<has_constexpr_bounds<EnumT>::value && is_contiguous_field_value<EnumT>::value> >
        : public enum_bounds<EnumT>
      {
        static constexpr auto size = size_of_bounds<EnumT>();
      };
      
      template <typename EnumT>
      struct enum_range<EnumT, std::enable_if_t<has_range<EnumT>::value && 
            !has_constexpr_range<EnumT>::value>>
      {
        static const std::size_t size;
      };
      
      template <typename EnumT>
      const std::size_t 
      enum_range<EnumT, std::enable_if_t<has_range<EnumT>::value && 
        !has_constexpr_range<EnumT>::value>>::size = size_of_bounds<EnumT>();
      
    }                                                       // namespace detail
    
   
    template <typename T>
    struct enum_range : public detail::enum_range<T>
    { };
    
    
    

  }                                                    // namespace enumeration
}                                                           // namespace elib
#endif /* ELIB_ENUMERATION_ENUM_TRAITS_HPP */