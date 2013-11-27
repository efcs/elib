#ifndef ELIB_MP_TYPES_SIZE_TYPE_HPP
#define ELIB_MP_TYPES_SIZE_TYPE_HPP

# include <elib/mp/types/integral_c.hpp>
# include <cstddef>

namespace elib
{
  namespace mp
  {
    
    template <std::size_t Val>
    using size_type = integral_c<std::size_t, Val>;

  }                                                         // namespace mp
}                                                           // namespace elib
#endif /* ELIB_MP_TYPES_SIZE_TYPE_HPP */