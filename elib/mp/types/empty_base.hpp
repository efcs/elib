#ifndef ELIB_MP_TYPES_EMPTY_BASE_HPP
#define ELIB_MP_TYPES_EMPTY_BASE_HPP

# include <elib/mp/types/bool.hpp>

namespace elib
{
  namespace mp
  {
  
  //-------------------------------- empty_base -----------------------------// 
    
    struct empty_base {};
    
  //-------------------------------- is_empty_base --------------------------//
  
    template <class T>
    struct is_empty_base : false_
    {};
    
    template <>
    struct is_empty_base< empty_base > : true_
    {};
  
  //-------------------------------- is_not_empty_base ----------------------// 
    
    template <class T>
    struct is_not_empty_base : true_
    {};
    
    template <>
    struct is_not_empty_base<empty_base> : false_
    {};
    
  }                                                         // namespace mp
}                                                           // namespace elib
#endif /* ELIB_MP_TYPES_EMPTY_BASE_HPP */