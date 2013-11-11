#ifndef ELIB_MP_LAMBDA_HPP
# define ELIB_MP_LAMBDA_HPP

# include <elib/mp/config.hpp>
# include <elib/mp/types.hpp>
# include <elib/mp/bind.hpp>
# include <elib/mp/arg.hpp>

# include <cstddef>

namespace elib 
{
  namespace mp
  {
    
    template <class T>
    struct lambda 
    {
      using is_lambda_expr = false_;
      using type = T;
    };
    
    template <std::size_t N>
    struct lambda< arg<N> >
    {
      using is_lambda_expr = true_;
      using type = arg<N>;
    };
    
  }                                                         // namespace mp
}                                                           // namespace elib
#endif /* ELIB_MP_LAMBDA_HPP */