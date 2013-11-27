#ifndef ELIB_MP_METAFUNCTION_ALWAYS_HPP
#define ELIB_MP_METAFUNCTION_ALWAYS_HPP

# include <elib/config.hpp>
# include <elib/mp/metafunction/arg.hpp>
# include <elib/mp/metafunction/bind.hpp>
# include <elib/mp/metafunction/identity.hpp>

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
#endif /* ELIB_MP_METAFUNCTION_ALWAYS_HPP */