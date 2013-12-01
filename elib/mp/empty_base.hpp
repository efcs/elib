#ifndef ELIB_MP_EMPTY_BASE_HPP
#define ELIB_MP_EMPTY_BASE_HPP

# include <elib/mp/bool.hpp>
# include <elib/pragma.hpp>

ELIB_PRAGMA_DIAG_PUSH()
ELIB_PRAGMA_IGNORE_EFFCXX()

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

ELIB_PRAGMA_DIAG_POP()
#endif /* ELIB_MP_EMPTY_BASE_HPP */