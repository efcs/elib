#ifndef ELIB_MP_PARTIAL_HPP
#define ELIB_MP_PARTIAL_HPP

# include <elib/mp/apply_wrap.hpp>

namespace elib 
{
  namespace mp
  {
    
    template <class F, class ...First>
    struct partial
    {
      template <class ...Rest>
      using apply = apply_wrap<F, First..., Rest...>;
    };
    
  }                                                         // namespace mp
}                                                           // namespace elib
#endif /* ELIB_MP_PARTIAL_HPP */