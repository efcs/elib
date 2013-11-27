#ifndef ELIB_MP_METAFUNCTION_INTC_CAST_HPP
#define ELIB_MP_METAFUNCTION_INTC_CAST_HPP

# include <type_traits>

namespace elib 
{
  namespace mp
  {
    
    template <class IntC, class T>
    struct intc_cast 
      : std::integral_constant<
          T
        , static_cast<T>(IntC::value)
        >
    {};
    
    
    template <class IntC, class T>
    using intc_cast_t = typename intc_cast<IntC, T>::type;
    
    
  }                                                         // namespace mp
}                                                           // namespace elib
#endif /* ELIB_MP_METAFUNCTION_INTC_CAST_HPP */