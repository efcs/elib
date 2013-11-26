#ifndef ELIB_MP_APPLY_HPP
# define ELIB_MP_APPLY_HPP

# include <elib/mp/metafunctions/apply_wrap.hpp>
# include <elib/mp/metafunctions/lambda.hpp>

namespace elib 
{
  namespace mp
  {
    
    template <class F, class ...Args>
    struct apply
    {
      using type = apply_wrap_t<lambda_t<F>, Args...>;
    };
    
    
    template <class F, class ...Args>
    using apply_t = typename apply<F, Args...>::type;
    
  }                                                         // namespace mp
}                                                           // namespace elib
#endif /* ELIB_MP_APPLY_HPP */