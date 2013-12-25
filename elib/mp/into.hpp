#ifndef ELIB_MP_INTO_HPP
# define ELIB_MP_INTO_HPP

# include <elib/mp/apply_wrap.hpp>

namespace elib 
{
  namespace mp
  {
    
    template <template <class...> class F>
    struct into
    {
      template <class ...Args>
      using apply = apply_wrap<F, Args...>;
    };
    
  }                                                         // namespace mp
}                                                           // namespace elib
#endif /* ELIB_MP_INTO_HPP */