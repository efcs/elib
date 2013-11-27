#ifndef ELIB_MP_TYPES_SHORT_HPP
#define ELIB_MP_TYPES_SHORT_HPP

# include <elib/mp/types/integral_c.hpp>

namespace elib
{
  namespace mp
  {
    
    template <short Val>
    using short_ = integral_c<short, Val>;
    
    
    template <unsigned short Val>
    using ushort_ = integral_c<unsigned short, Val>;

  }                                                         // namespace mp
}                                                           // namespace elib
#endif /* ELIB_MP_TYPES_SHORT_HPP */