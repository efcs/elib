#ifndef ELIB_MP_NA_HPP
#define ELIB_MP_NA_HPP

# include <elib/mp/integral_constant.hpp>

namespace elib 
{
  namespace mp
  {
   
    struct na {};
    
    template <class T>
    struct is_na : false_
    {};
    
    
    template <>
    struct is_na< na > : true_
    {};
   
  }                                                         // namespace mp
}                                                           // namespace elib
#endif /* ELIB_MP_NA_HPP */
