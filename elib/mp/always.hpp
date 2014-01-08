#ifndef ELIB_MP_ALWAYS_HPP
#define ELIB_MP_ALWAYS_HPP

# include <elib/mp/identity.hpp>
# include <elib/mp/protect.hpp>
# include <elib/mp/integral_constant.hpp>

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
    
    
    using always_true = protect< always<true_> >;
    using always_false = protect< always<false_> >;
    
  }                                                         // namespace mp
}                                                           // namespace elib
#endif /* ELIB_MP_ALWAYS_HPP */