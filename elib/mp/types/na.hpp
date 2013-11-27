#ifndef ELIB_MP_TYPES_NA_HPP
#define ELIB_MP_TYPES_NA_HPP

# include <elib/mp/types/bool.hpp>

namespace elib 
{
  namespace mp
  {
    
  //-------------------------------- na -------------------------------------// 
    
    struct na {};
    
  //-------------------------------- is_na ----------------------------------// 
    
    template <class T>
    struct is_na : false_
    {};
    
    template <>
    struct is_na< na > : true_
    {};
    
  //-------------------------------- is_not_na ------------------------------// 
  
    template <class T>
    struct is_not_na : true_
    {};
    
    template <>
    struct is_not_na< na > : false_
    {};
    
  }                                                         // namespace mp
}                                                           // namespace elib
#endif /* ELIB_MP_TYPES_NA_HPP */