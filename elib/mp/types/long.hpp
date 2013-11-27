#ifndef ELIB_MP_TYPES_LONG_HPP
#define ELIB_MP_TYPES_LONG_HPP

# include <elib/mp/types/integral_c.hpp>

namespace elib
{
  namespace mp
  {
    
    template <long Val>
    using long_ = integral_c<long, Val>;
    
    
    template <unsigned long Val>
    using ulong_ = integral_c<unsigned long, Val>;
    
  //-------------------------------- long long ------------------------------// 
    
    template <long long Val>
    using llong_ = integral_c<long long, Val>;
    
    
    template <unsigned long long Val>
    using ullong_ = integral_c<unsigned long long, Val>;
    
  }                                                         // namespace mp
}                                                           // namespace elib
#endif /* ELIB_MP_TYPES_LONG_HPP */