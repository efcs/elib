#ifndef ELIB_MP_TYPES_HPP
# define ELIB_MP_TYPES_HPP

# include <elib/config.hpp>

# include <elib/CXX14/type_traits.hpp>

# include <cstddef>

namespace elib 
{
  namespace mp
  {
    
    using void_ = void;
    using nullptr_ = std::nullptr_t;
    
    template <bool Val>
    using bool_ = std::integral_constant<bool, Val>;
    
    using true_ = bool_<true>;
    using false_ = bool_<false>;
    
    
    template <char Val>
    using char_ = std::integral_constant<char, Val>;
    
    template <signed char Val>
    using schar_ = std::integral_constant<signed char, Val>;
    
    template <unsigned char Val>
    using uchar_ = std::integral_constant<unsigned char, Val>;
    
    
    template <int Val>
    using int_ = std::integral_constant<int, Val>;
    
    template <unsigned int Val>
    using uint_ = std::integral_constant<unsigned int, Val>;
    
    // I know that this and the above type are the same, 
    // but it is done to provided common names
    template <unsigned Val>
    using unsigned_ = std::integral_constant<unsigned, Val>;
    
    template <long Val>
    using long_ = std::integral_constant<long, Val>;
    
    template <unsigned long Val>
    using ulong_ = std::integral_constant<unsigned long, Val>;
    
    template <long long Val>
    using llong_ = std::integral_constant<long long, Val>;
    
    template <unsigned long long Val>
    using ullong_ = std::integral_constant<unsigned long long, Val>;
    
  }                                                         // namespace mp
}                                                           // namespace elib
#endif /* ELIB_MP_TYPES_HPP */