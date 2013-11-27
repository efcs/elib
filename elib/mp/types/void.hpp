#ifndef ELIB_MP_TYPES_VOID_HPP
#define ELIB_MP_TYPES_VOID_HPP

# include <elib/mp/types/bool.hpp>

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
    
  }                                                         // namespace mp
}                                                           // namespace elib
#endif /* ELIB_MP_TYPES_VOID_HPP */