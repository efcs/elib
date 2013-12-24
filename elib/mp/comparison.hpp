#ifndef ELIB_MP_COMPARISON_HPP
#define ELIB_MP_COMPARISON_HPP

# include <elib/mp/integral_constant.hpp>

namespace elib 
{
  namespace mp
  {
    
    template <class LHS, class RHS>
    using equal_to = bool_<LHS::value == RHS::value>;
    
    template <class LHS, class RHS>
    using not_equal_to = bool_<LHS::value != RHS::value>;
    
    
    template <class LHS, class RHS>
    using less = bool_<(LHS::value < RHS::value)>;
    
    
    template <class LHS, class RHS>
    using less_equal = bool_<(LHS::value <= RHS::value)>;
    
    
    template <class LHS, class RHS>
    using greater = bool_<(LHS::value > RHS::value)>;
    
    
    template <class LHS, class RHS>
    using greater_equal = bool_<(LHS::value >= RHS::value)>;
    
    
  }                                                         // namespace mp
}                                                           // namespace elib
#endif /* ELIB_MP_COMPARISON_HPP */