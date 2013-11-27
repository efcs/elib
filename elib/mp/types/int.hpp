#ifndef ELIB_MP_TYPES_INT_HPP
#define ELIB_MP_TYPES_INT_HPP

# include <type_traits>

namespace elib
{
  namespace mp
  {
    
    template <int Val>
    using int_ = std::integral_constant<int, Val>;
    
    
    template <unsigned int Val>
    using uint_ = std::integral_constant<unsigned int, Val>;
    
    
    template <unsigned int Val>
    using unsigned_ = std::integral_constant<unsigned int, Val>;

  }                                                         // namespace mp
}                                                           // namespace elib
#endif /* ELIB_MP_TYPES_INT_HPP */