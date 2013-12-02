#ifndef ELIB_MP_INTEGRAL_CAST_HPP
#define ELIB_MP_INTEGRAL_CAST_HPP

# include <elib/mp/integral_constant.hpp>

namespace elib 
{
  namespace mp
  {
    
    template <class IntC, class T>
    struct integral_cast 
      : integral_c<
          T
        , static_cast<T>(IntC::value)
        >
    {};
    
    
    template <class IntC, class T>
    using integral_cast_t = integral_c<T, static_cast<T>(IntC::value)>;
    
    
  }                                                         // namespace mp
}                                                           // namespace elib
#endif /* ELIB_MP_INTEGRAL_CAST_HPP */