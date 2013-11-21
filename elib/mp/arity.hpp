#ifndef ELIB_MP_ARITY_HPP
# define ELIB_MP_ARITY_HPP

# include <elib/mp/config.hpp>
# include <elib/mp/types.hpp>


namespace elib 
{
  namespace mp
  {
    
    template <
      template <class ...Args> class F
    >
    struct arity : size_t_<sizeof...(Args)>
    {};
    
    
  }                                                         // namespace mp
}                                                           // namespace elib
#endif /* ELIB_MP_ARITY_HPP */