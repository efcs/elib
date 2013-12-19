#ifndef ELIB_MP_IDENTITY_HPP
#define ELIB_MP_IDENTITY_HPP

# include <elib/config.hpp>

namespace elib 
{
  namespace mp
  {
    
    template <class T>
    struct identity
    { using type = T; };
    
    
  }                                                         // namespace mp
}                                                           // namespace elib
#endif /* ELIB_MP_IDENTITY_HPP */