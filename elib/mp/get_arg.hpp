#ifndef ELIB_MP_GET_ARG_HPP
# define ELIB_MP_GET_ARG_HPP

# include <elib/mp/config.hpp>

# include <cstddef>

namespace elib 
{
  namespace mp
  {
    
    
    template <std::size_t N, class Head, class ...Rest>
    struct get_arg
    {
                    
      typedef typename get_arg<N-1, Rest...>::type type;
      
    private:
      static_assert(N != 0, "N must not be zero");
      
      static_assert(N-1 <= sizeof...(Rest), "not enough parameters for N");
      
      static_assert(sizeof...(Rest) + 2 <= ELIB_MP_PARAM_LIMIT,
                    "too many params");
    };
    
    
    template <class Head, class ...Rest>
    struct get_arg<0, Head, Rest...>
    {
      typedef Head type;
    };
    
    
    template <std::size_t N, class ...Args>
    using get_arg_t = typename get_arg<N, Args...>::type;
    
    
  }                                                         // namespace mp
}                                                           // namespace elib
#endif /* ELIB_MP_GET_ARG_HPP */