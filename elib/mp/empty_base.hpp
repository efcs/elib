#ifndef ELIB_MP_EMPTY_BASE_HPP
#define ELIB_MP_EMPTY_BASE_HPP

# include <elib/aux.hpp>

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
  }                                                         // namespace mp
}                                                           // namespace elib
#endif /* ELIB_MP_EMPTY_BASE_HPP */