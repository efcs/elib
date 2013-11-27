#ifndef ELIB_MP_TYPES_LONG_HPP
#define ELIB_MP_TYPES_LONG_HPP

# include <type_traits>

namespace elib
{
  namespace mp
  {
    
    template <long Val>
    using long_ = std::integral_constant<long, Val>;
    
    
    template <unsigned long Val>
    using ulong_ = std::integral_constant<unsigned long, Val>;
    
  //-------------------------------- long long ------------------------------// 
    
    template <long long Val>
    using llong_ = std::integral_constant<long long, Val>;
    
    
    template <unsigned long long Val>
    using ullong_ = std::integral_constant<unsigned long long, Val>;
    
  }                                                         // namespace mp
}                                                           // namespace elib
#endif /* ELIB_MP_TYPES_LONG_HPP */