#ifndef ELIB_MP_ALWAYS_HPP
#define ELIB_MP_ALWAYS_HPP

# include <elib/config.hpp>
# include <elib/mp/arg.hpp>
# include <elib/mp/bind.hpp>
# include <elib/mp/identity.hpp>

namespace elib 
{
  namespace mp
  {
    
    template <class T>
    struct always
    {
      // Not sure why apply requires at least 1 param
      // but it does
      template <class U, class ...Args>
      struct apply
      {
        using type = T;
      };
    };
    
  }                                                         // namespace mp
}                                                           // namespace elib
#endif /* ELIB_MP_ALWAYS_HPP */