#ifndef ELIB_MP_METAFUNCTION_PROTECT_HPP
# define ELIB_MP_METAFUNCTION_PROTECT_HPP

# include <elib/mp/config.hpp>
# include <elib/mp/metafunction/apply_wrap.hpp>
# include <elib/mp/metafunction/bind.hpp>


namespace elib 
{
  namespace mp
  {
    
    // Default case: F is not a bind expression
    template <class F>
    struct protect : F
    {};
    
    
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
#endif /* ELIB_MP_METAFUNCTION_PROTECT_HPP */