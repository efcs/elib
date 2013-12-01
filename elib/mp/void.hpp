#ifndef ELIB_MP_VOID_HPP
#define ELIB_MP_VOID_HPP

# include <elib/mp/bool.hpp>
# include <elib/pragma.hpp>

ELIB_PRAGMA_DIAG_PUSH()
ELIB_PRAGMA_IGNORE_EFFCXX()

namespace elib
{
  namespace mp
  {
  
  //-------------------------------- void_ ----------------------------------// 
    
    struct void_
    { using type = void_; };
    
  //-------------------------------- is_void --------------------------------// 
    
    template <class T>
    struct is_void : false_
    {};
    
    template <>
    struct is_void< void_ > : true_
    {};
    
  //-------------------------------- is_not_void ----------------------------// 
  
    template <class T>
    struct is_not_void : true_
    {};
    
    template <>
    struct is_not_void< void_ > : false_
    {};
    
  //-------------------------------- if_void --------------------------------// 
    
    template <class T, class U>
    struct if_void 
    {
      using type = T;
    };
    
    template <class U>
    struct if_void<void_, U>
    {
      using type = U;
    };
    
  }                                                         // namespace mp
}                                                           // namespace elib

ELIB_PRAGMA_DIAG_POP()

#endif /* ELIB_MP_VOID_HPP */