#ifndef ELIB_MP_METAFUNCTION_DECREMENT_HPP
#define ELIB_MP_METAFUNCTION_DECREMENT_HPP

# include <elib/CXX14/type_traits.hpp>

namespace elib 
{
  namespace mp
  {
  //-------------------------------- decrement ------------------------------// 
    
    template <class IntC>
    struct decrement
      : std::integral_constant<
            typename IntC::value_type
          , IntC::value - 1
        >
    {};
    
    template <class IntC>
    using decrement_t = typename decrement<IntC>::type;
    
  }                                                         // namespace mp
}                                                           // namespace elib
#endif /* ELIB_MP_METAFUNCTION_DECREMENT_HPP */