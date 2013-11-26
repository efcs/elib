#ifndef ELIB_MP_METAFUNCTION_IDENTITY_HPP
#define ELIB_MP_METAFUNCTION_IDENTITY_HPP

# include <elib/config.hpp>

namespace elib 
{
  namespace mp
  {
    
    template <class T>
    struct identity
    { using type = T; };
    
    
    template <class T>
    using identity_t = typename identity<T>::type;
    
  }                                                         // namespace mp
}                                                           // namespace elib
#endif /* ELIB_MP_METAFUNCTION_IDENTITY_HPP */