#ifndef ELIB_MP_APPLY_HPP
#define ELIB_MP_APPLY_HPP

# include <elib/mp/apply_wrap.hpp>
# include <elib/mp/lambda.hpp>

namespace elib 
{
  namespace mp
  {
    
    template <class F, class ...Args>
    struct apply
    {
      using type = typename lambda_t<F>::template apply<Args...>::type;
    };
    
    
    template <class F, class ...Args>
    using apply_t = typename lambda_t<F>::template apply<Args...>::type;
    
  }                                                         // namespace mp
}                                                           // namespace elib
#endif /* ELIB_MP_APPLY_HPP */