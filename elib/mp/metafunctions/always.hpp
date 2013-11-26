#ifndef ELIB_MP_ALWAYS_HPP
# define ELIB_MP_ALWAYS_HPP

# include <elib/config.hpp>
# include <elib/mp/metafunctions/arg.hpp>
# include <elib/mp/metafunctions/bind.hpp>
# include <elib/mp/metafunctions/identity.hpp>

namespace elib 
{
  namespace mp
  {
    
    template <class T>
    struct always : bind< identity<placeholders::_1>, T > 
    {};
    
  }                                                         // namespace mp
}                                                           // namespace elib
#endif /* ELIB_MP_ALWAYS_HPP */