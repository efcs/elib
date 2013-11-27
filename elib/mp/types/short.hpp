#ifndef ELIB_MP_TYPES_SHORT_HPP
#define ELIB_MP_TYPES_SHORT_HPP

# include <type_traits>

namespace elib
{
  namespace mp
  {
    
    template <short Val>
    using short_ = std::integral_constant<short, Val>;
    
    
    template <unsigned short Val>
    using ushort_ = std::integral_constant<unsigned short, Val>;

  }                                                         // namespace mp
}                                                           // namespace elib
#endif /* ELIB_MP_TYPES_SHORT_HPP */