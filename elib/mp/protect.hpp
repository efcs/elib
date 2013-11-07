#ifndef ELIB_MP_PROTECT_HPP
# define ELIB_MP_PROTECT_HPP

# include <elib/mp/config.hpp>
# include <elib/mp/apply_wrap.hpp>
# include <elib/mp/bind.hpp>


namespace elib 
{
  namespace mp
  {
    
    template <class F>
    struct protect : F
    {};
    
    
    template <class ...Args>
    struct protect<bind<Args...>>
    {
      
      template <class ...Args2>
      struct apply : apply_wrap<bind<Args...>, Args2...>
      {};
      
    };
    
    
  }                                                         // namespace mp
}                                                           // namespace elib
#endif /* ELIB_MP_PROTECT_HPP */