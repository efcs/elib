#ifndef ELIB_MP_ALWAYS_HPP
#define ELIB_MP_ALWAYS_HPP

# include <elib/mp/identity.hpp>

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
    
  }                                                         // namespace mp
}                                                           // namespace elib
#endif /* ELIB_MP_ALWAYS_HPP */