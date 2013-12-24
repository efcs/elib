#ifndef ELIB_MP_APPLY_HPP
#define ELIB_MP_APPLY_HPP

# include <elib/mp/apply_wrap.hpp>
# include <elib/mp/lambda.hpp>
# include <elib/mp/identity.hpp>

namespace elib 
{
  namespace mp
  {
    
    template <class F, class ...Args>
    using apply_t = typename lambda_t<F>::template apply<Args...>::type;
    
    
    template <class F, class ...Args>
    using apply = identity< apply_t<F, Args...> >;
    
  }                                                         // namespace mp
}                                                           // namespace elib
#endif /* ELIB_MP_APPLY_HPP */