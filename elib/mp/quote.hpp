#ifndef ELIB_MP_QUOTE_HPP
#define ELIB_MP_QUOTE_HPP

# include <elib/mp/config.hpp>
# include <elib/mp/integral_constant.hpp>
# include <elib/mp/typedef_detector.hpp>
# include <elib/mp/identity.hpp>

namespace elib 
{
  namespace mp
  {
    namespace detail
    {

      template <class F>
      auto quote_impl(void*) -> typename F::type;
      
      template <class F>
      auto quote_impl(...) -> F;
      
    }                                                       // namespace detail
   
   template <template <class...> class F>
    struct quote
    {
      template <class ...Args>
      using apply = identity< 
        decltype( detail::quote_impl<F<Args...>>(0) ) 
        >;
    };
    
    
  }                                                         // namespace mp
}                                                           // namespace elib
#endif /* ELIB_MP_QUOTE_HPP */