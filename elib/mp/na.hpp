#ifndef ELIB_MP_NA_HPP
#define ELIB_MP_NA_HPP

# include <elib/mp/integral_constant.hpp>
# include <elib/mp/same_type.hpp>

namespace elib 
{
  namespace mp
  {
   
    struct na {};
    
    template <class T>
    using is_na = same_type<T, na>;
    
    template <class T>
    using is_na_t = typename same_type<T, na>::type;
   
  }                                                         // namespace mp
}                                                           // namespace elib
#endif /* ELIB_MP_NA_HPP */