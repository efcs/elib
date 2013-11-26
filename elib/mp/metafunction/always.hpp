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
    struct always : bind< identity<placeholders::_1>, T > 
    {};
    
  }                                                         // namespace mp
}                                                           // namespace elib
#endif /* ELIB_MP_METAFUNCTION_ALWAYS_HPP */