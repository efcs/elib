#ifndef ELIB_MP_DETAIL_NIL_HPP
#define ELIB_MP_DETAIL_NIL_HPP

# include <elib/mp/integral_constant.hpp>

namespace elib 
{
  namespace mp
  {
    
    struct nil {};
    
    template <class T>
    struct is_nil : false_
    {};
    
    template <>
    struct is_nil<nil> : true_
    {};
    
  }                                                         // namespace mp
}                                                           // namespace elib
#endif /* ELIB_MP_DETAIL_NIL_HPP */