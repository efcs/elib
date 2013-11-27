#ifndef ELIB_MP_TYPES_INT_HPP
#define ELIB_MP_TYPES_INT_HPP

# include <elib/mp/types/integral_c.hpp>

namespace elib
{
  namespace mp
  {
    
    template <int Val>
    using int_ = integral_c<int, Val>;
    
    
    template <unsigned int Val>
    using uint_ = integral_c<unsigned int, Val>;
    
    
    template <unsigned int Val>
    using unsigned_ = integral_c<unsigned int, Val>;

  }                                                         // namespace mp
}                                                           // namespace elib
#endif /* ELIB_MP_TYPES_INT_HPP */