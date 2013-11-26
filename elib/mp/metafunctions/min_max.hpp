#ifndef ELIB_MP_MIN_MAX_HPP
# define ELIB_MP_MIN_MAX_HPP

# include <elib/mp/config.hpp>
# include <elib/mp/metafunctions/if.hpp>
# include <elib/mp/metafunctions/comparison.hpp>

namespace elib 
{
  namespace mp
  {
    
  //-------------------------------- min --------------------------------// 
    
    template <class LHS, class RHS>
    struct min : if_<less<LHS, RHS>, LHS, RHS>
    {};
    
  //-------------------------------- min_t --------------------------------// 
    
    template <class LHS, class RHS>
    using min_t = typename min<LHS, RHS>::type;
    
  //-------------------------------- max --------------------------------// 
    
    template <class LHS, class RHS>
    struct max : if_<greater<LHS, RHS>, LHS, RHS>
    {};
    
  //-------------------------------- max_t --------------------------------// 
    
    template <class LHS, class RHS>
    using max_t = typename max<LHS, RHS>::type;

  }                                                         // namespace mp
}                                                           // namespace elib
#endif /* ELIB_MP_MIN_MAX_HPP */