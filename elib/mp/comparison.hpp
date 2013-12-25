#ifndef ELIB_MP_COMPARISON_HPP
#define ELIB_MP_COMPARISON_HPP

# include <elib/mp/integral_constant.hpp>

namespace elib 
{
  namespace mp
  {
    
    template <class LHS, class RHS>
    struct equal_to : bool_<LHS::type::value == RHS::type::value>
    {};
    
    template <class LHS, class RHS>
    struct not_equal_to : bool_<LHS::type::value != RHS::type::value>
    {};
    
    
    template <class LHS, class RHS>
    struct less : bool_<(LHS::type::value < RHS::type::value)>
    {};
    
    
    template <class LHS, class RHS>
    struct less_equal : bool_<(LHS::type::value <= RHS::type::value)>
    {};
    
    
    template <class LHS, class RHS>
    struct greater : bool_<(LHS::type::value > RHS::type::value)>
    {};
    
    
    template <class LHS, class RHS>
    struct greater_equal : bool_<(LHS::type::value >= RHS::type::value)>
    {};
    
    
  }                                                         // namespace mp
}                                                           // namespace elib
#endif /* ELIB_MP_COMPARISON_HPP */