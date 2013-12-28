#ifndef ELIB_MP_ALWAYS_HPP
#define ELIB_MP_ALWAYS_HPP

# include <elib/mp/identity.hpp>
# include <elib/mp/detail/integral_constant.hpp>

namespace elib 
{
  namespace mp
  {
    
    template <class T>
    struct always
    {
      template <class ...>
      using apply = identity< T >;
    };
    
    
    using always_true = always<true_>;
    using always_false = always<false_>;
    
  }                                                         // namespace mp
}                                                           // namespace elib
#endif /* ELIB_MP_ALWAYS_HPP */