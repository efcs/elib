#ifndef ELIB_MP_METAFUNCTION_INCREMENT_HPP
#define ELIB_MP_METAFUNCTION_INCREMENT_HPP

# include <elib/CXX14/type_traits.hpp>

namespace elib 
{
  namespace mp
  {
    
  //-------------------------------- increment ------------------------------// 
    
    template <class IntC>
    struct increment
      : std::integral_constant<
            typename IntC::value_type
          , IntC::value + 1
        >
    {};
    
    template <class IntC>
    using increment_t = typename increment<IntC>::type;
    
  }                                                         // namespace mp
}                                                           // namespace elib
#endif /* ELIB_MP_METAFUNCTION_INCREMENT_HPP */