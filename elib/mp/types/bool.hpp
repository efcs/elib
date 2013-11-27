#ifndef ELIB_MP_TYPES_BOOL_HPP
#define ELIB_MP_TYPES_BOOL_HPP

# include <type_traits>

namespace elib
{
  namespace mp
  {
  
    template <bool Val>
    using bool_ = std::integral_constant<bool, Val>;
    
    using true_ = bool_<true>;
    using false_ = bool_<false>;
    
  }                                                         // namespace mp
}                                                           // namespace elib
#endif /* ELIB_MP_TYPES_BOOL_HPP */