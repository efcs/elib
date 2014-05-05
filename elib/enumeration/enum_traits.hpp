#ifndef ELIB_ENUMERATION_ENUM_TRAITS_HPP
#define ELIB_ENUMERATION_ENUM_TRAITS_HPP

# include <elib/enumeration/enum_helper.hpp>
# include <elib/enumeration/basic_enum_traits.hpp>
# include <elib/enumeration/detail/meta_traits.hpp>
# include <elib/aux.hpp>
# include <cstddef>


namespace elib { namespace enumeration
{
    
# define ELIB_ENUM_MERGE_HAS(name) meta_t::has_##name || int_t::has_##name
# define ELIB_ENUM_MERGE(name) meta_t::has_##name ? meta_t::name : int_t::name
    
    template <class T, class=enable_if_enum_t<T>>
    struct enum_traits
    {
    private:
        using meta_t = detail::meta_basic_enum_traits<T>;
        using int_t = detail::meta_intrusive_traits<T>;
        
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
        
        static constexpr bool has_is_logical = ELIB_ENUM_MERGE_HAS(is_logical);
        static constexpr bool is_logical = ELIB_ENUM_MERGE(is_logical);
        
        static constexpr bool has_is_mixed_comparible = 
            ELIB_ENUM_MERGE_HAS(is_mixed_comparible);
        static constexpr bool is_mixed_comparible = 
            ELIB_ENUM_MERGE(is_mixed_comparible);
        
        static constexpr bool has_constexpr_bounds =
            has_first_value && has_last_value;
        
        static constexpr bool has_constexpr_range = 
            has_constexpr_bounds && is_contigious;
    };                                                    // struct enum_traits
    
# undef ELIB_ENUM_MERGE
# undef ELIB_ENUM_MERGE_HAS


    template <class T, bool=std::is_enum<T>::value>
    struct has_range : aux::false_
    {};
    
    template <class T>
    struct has_range<T, true>
      : bool_<
            enum_traits<T>::has_constexpr_range
            || has_name_map<T>::value
        >
    {};
    
    template <class T,  bool=aux::is_enum<T>::value>
    struct has_constexpr_range : aux::false_ {};
    
    template <class T>
    struct has_constexpr_range<T, true>
      : bool_< enum_traits<T>::has_constexpr_range >
    {};

    template <class T, ELIB_ENABLE_IF(enum_traits<T>::has_default_value)>
    constexpr T default_value() noexcept
    {
      return enum_traits<T>::default_value;
    }
    
    template <class T, ELIB_ENABLE_IF(enum_traits<T>::has_error_value)>
    constexpr T error_value() noexcept
    {
      return enum_traits<T>::error_value;
    }
    
    
    template <class T, ELIB_ENABLE_IF(enum_traits<T>::has_first_value)>
    constexpr T first_value() noexcept
    {
      return enum_traits<T>::first_value;
    }
    
    template <class T, ELIB_ENABLE_IF(enum_traits<T>::has_last_value)>
    constexpr T last_value() noexcept
    {
      return enum_traits<T>::last_value;
    }
    
    template <class T>
    aux::enable_if_c_t<
      has_name_map<T>::value
        && !enum_traits<T>::has_first_value
      , T
    >
    first_value()
    {
      return basic_enum_traits<T>::name_map.begin()->first;
    }
    
    
    template <class T>
    aux::enable_if_c_t<
      has_name_map<T>::value
        && !enum_traits<T>::has_last_value
      , T
    >
    last_value()
    {
      return (basic_enum_traits<T>::name_map.end()--)->first;
    }
    
    
    template <class T>
    constexpr aux::enable_if_c_t<
      enum_traits<T>::has_constexpr_range
      , std::size_t
    >
    size() noexcept
    {
      return underlying_cast(last_value<T>()) 
             - underlying_cast(first_value<T>()) + 1;
    }
    
    
    template <class T>
    aux::enable_if_c_t<
      has_name_map<T>::value
        && !enum_traits<T>::has_constexpr_range
      , std::size_t
    >
    size()
    {
      return basic_enum_traits<T>::name_map.size();
    }
    
    
    template <class T>
    constexpr aux::enable_if_c_t<
      enum_traits<T>::has_is_contigious
      , bool
    >
    is_contigious() noexcept
    {
      return enum_traits<T>::is_contigious;
    }
    
    
    template <class T>
    aux::enable_if_c_t<
      has_name_map<T>::value
        && !enum_traits<T>::has_is_contigious
      , bool
    >
    is_contigious()
    {
      return (size<T>() == 0 
        || (static_cast<std::size_t>(
                underlying_cast(last_value<T>()) - underlying_cast(first_value<T>())
          )
             == size<T>()
          ));
    }
    
    
    template <class T>
    constexpr aux::enable_if_c_t<
      enum_traits<T>::has_constexpr_range
      , bool 
    >
    in_range(T v) noexcept
    {
      return (first_value<T>() <= v && v <= last_value<T>());
    }
    
    
    template <class T>
    aux::enable_if_c_t<
      has_name_map<T>::value
        && !enum_traits<T>::has_constexpr_range
      , bool
    >
    in_range(T v)
    {
      if (size<T>() == 0)
        return false;
      if (is_contigious<T>())
        return (first_value<T>() <= v && v <= last_value<T>());
      return basic_enum_traits<T>::name_map.count(v) > 0;
    }
    
      
    
    
    
  }                                                    // namespace enumeration
}                                                           // namespace elib
#endif /* ELIB_ENUMERATION_ENUM_TRAITS_HPP */