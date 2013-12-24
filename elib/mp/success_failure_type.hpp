#ifndef ELIB_MP_SUCCESS_FAILURE_TYPE_HPP
#define ELIB_MP_SUCCESS_FAILURE_TYPE_HPP

# include <elib/mp/detail/integral_constant.hpp>

namespace elib 
{
  namespace mp
  {
    
    template <class T>
    struct success_type
    {
      using good = true_;
      using type = T;
    };
    
    
    template <class T>
    struct failure_type
    {
      using good = false_;
      using type = T;
    };
    
  }                                                         // namespace mp
}                                                           // namespace elib
#endif /* ELIB_MP_SUCCESS_FAILURE_TYPE_HPP */
