#ifndef ELIB_MP_SIZEOF_HPP
#define ELIB_MP_SIZEOF_HPP

# include <elib/mp/integral_constant.hpp>

namespace elib 
{
  namespace mp
  {
    
    template <class T>
    struct sizeof_ 
      : integral_c<
          decltype(sizeof(T))
          , sizeof(T) 
        >
    {};
    
  }                                                         // namespace mp
}                                                           // namespace elib
#endif /* ELIB_MP_SIZEOF_HPP */