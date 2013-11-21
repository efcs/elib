#ifndef ELIB_MP_PROTECT_HPP
# define ELIB_MP_PROTECT_HPP

# include <elib/mp/config.hpp>
# include <elib/mp/apply_wrap.hpp>
# include <elib/mp/bind.hpp>


namespace elib 
{
  namespace mp
  {
    
    // Default case: F is not a bind expression
    template <class F>
    struct protect : F
    {};
    
    // Hide a bind expression. 
    // TODO: The boost implentation does something weird
    template <class F, class ...Args>
    struct protect< bind<F, Args...> >
    {
      
      template <class ...ApplyArgs>
      struct apply 
        : apply_wrap< 
            bind<F, Args...>
            , ApplyArgs...
          >
      {};
      
    };                                                      // struct protect
    
    
  }                                                         // namespace mp
}                                                           // namespace elib
#endif /* ELIB_MP_PROTECT_HPP */