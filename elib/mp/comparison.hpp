#ifndef ELIB_MP_COMPARISON_HPP
# define ELIB_MP_COMPARISON_HPP

# include <elib/mp/config.hpp>
# include <elib/mp/types.hpp>

# include <elib/CXX14/type_traits.hpp>


namespace elib 
{
  namespace mp
  {
    
    template <class LHS, class RHS>
    struct equal : bool_<LHS::value == RHS::value>
    {};
    
    template <class LHS, class RHS>
    struct not_equal : bool_<LHS::value != RHS::value>
    {};
    
    template <class LHS, class RHS>
    struct less : bool_<(LHS::value < RHS::value)>
    {};
    
    template <class LHS, class RHS>
    struct less_equal : bool_<(LHS::value <= RHS::value)>
    {};
    
    template <class LHS, class RHS>
    struct greater : bool_<(LHS::value > RHS::value)>
    {};
    
    template <class LHS, class RHS>
    struct greater_equal : bool_<(LHS::value >= RHS::value)>
    {};
    
  }                                                         // namespace mp
}                                                           // namespace elib
#endif /* ELIB_MP_COMPARISON_HPP */