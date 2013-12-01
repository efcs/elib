#ifndef ELIB_MP_INTC_CAST_HPP
#define ELIB_MP_INTC_CAST_HPP

# include <elib/mp/integral_constant.hpp>

namespace elib 
{
  namespace mp
  {
    
    template <class IntC, class T>
    struct intc_cast 
      : integral_c<
          T
        , static_cast<T>(IntC::value)
        >
    {};
    
    
    template <class IntC, class T>
    using intc_cast_t = typename intc_cast<IntC, T>::type;
    
    
  }                                                         // namespace mp
}                                                           // namespace elib
#endif /* ELIB_MP_INTC_CAST_HPP */